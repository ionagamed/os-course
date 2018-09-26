#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void common_signal_hanlder(int signum)
{
    switch (signum)
    {
    case SIGKILL:
        printf("SIGKILL\n");
        break;
    case SIGSTOP:
        printf("SIGSTOP\n");
        break;
    case SIGUSR1:
        printf("SIGUSR1\n");
        break;
    }
}

int main()
{
    // these two are useless, because we can't override SIGKILL nor SIGSTOP
    signal(SIGKILL, common_signal_hanlder);
    signal(SIGSTOP, common_signal_hanlder);

    signal(SIGUSR1, common_signal_hanlder);

    sleep(60);
    // first sleep is not restored after return from the interrupt by SIGUSR1
    sleep(60);

    return 0;
}