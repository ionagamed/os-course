#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void signal_handler(int signum)
{
    printf("^C pressed\n");
}

int main()
{
    signal(SIGINT, signal_handler);
    sleep(10);
    return 0;
}