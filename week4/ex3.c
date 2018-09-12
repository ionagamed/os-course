#include <stdio.h>
#include <stdlib.h>

int main()
{
    char cmd[1024];
    while (1)
    {
        printf(">> ");
        scanf("%s", cmd);
        system(cmd);
    }
}