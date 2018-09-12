#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

int main()
{
    while (1)
    {
        fork();
        fork();
        fork();
        fork();
        fork();
        sleep(5);
    }
}