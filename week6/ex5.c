#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
    pid_t child_pid = fork();
    if (child_pid == 0)
    {
        for (;;)
        {
            printf("I'm alive\n");
            sleep(1);
        }
    }
    else
    {
        sleep(10);
        kill(child_pid, SIGTERM);
    }
}