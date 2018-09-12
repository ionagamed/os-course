#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>

int main()
{
    int n;
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("Hello from child [%d - %d]\n", getpid(), n);
    }
    else
    {
        printf("Hello from parent [%d - %d]\n", getpid(), n);
    }
}