#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void first_child(int pipe_read_fd)
{
    pid_t sibling_pid;
    read(pipe_read_fd, &sibling_pid, sizeof(pid_t));
    printf("Recieved sibling PID %d\n", sibling_pid);
    sleep(5);
    kill(sibling_pid, SIGSTOP);
}

void idle()
{
    for (;;)
    {
        printf("I'm 2 and i'm alive\n");
        sleep(1);
    }
}

int main()
{
    int pipe_fd[2];

    pipe(pipe_fd);
    printf("Fork 1 ... ");
    pid_t first_child_pid = fork();
    if (first_child_pid == 0)
    {
        first_child(pipe_fd[0]);
        return 0;
    }
    printf("%d\n", first_child_pid);

    printf("Fork 2 ... ");
    pid_t second_child_pid = fork();
    if (second_child_pid == 0)
    {
        idle();
        return 0;
    }
    printf("%d\n", second_child_pid);

    ssize_t bytes = write(pipe_fd[1], &second_child_pid, sizeof(pid_t));
    if (bytes == -1)
    {
        perror("Error writing PID");
        return -1;
    }

    int second_child_status;
    printf("Waiting for second child to exit ... ");
    fflush(stdout);
    waitpid(second_child_pid, &second_child_status, WUNTRACED);

    printf("\n\n\n");
    printf("signal number: %d\n", WSTOPSIG(second_child_status));
    printf("SIGSTOP: %d", SIGSTOP);
    printf("\n\n\n");

    printf("exited with status code %d\n", second_child_status);
}