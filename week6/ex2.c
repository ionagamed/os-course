#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pfd[2];
    pipe(pfd);

    char *s1 = "Hello, world!";
    char s2[100];

    pid_t pid = fork();

    if (pid == 0)
    {
        read(pfd[0], s2, 100);
        printf("%s\n", s2);
    }
    else
    {
        write(pfd[1], s1, strlen(s1) + 1);
    }

    return 0;
}