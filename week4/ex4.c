#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void split(const char *s, char **ret)
{
    char buf[64];
    int bp = 0;
    int rp = 0;
    for (int i = 0; s[i]; i++)
    {
        if (s[i] == ' ' && bp != 0)
        {
            for (int j = 0; j < bp; j++)
            {
                ret[rp][j] = buf[j];
            }
            ret[rp][bp] = 0;
            bp = 0;
            rp++;
        }
        else if (s[i] != ' ')
        {
            buf[bp] = s[i];
            bp++;
        }
    }
}

int main()
{
    char cmd[1024];
    while (1)
    {
        printf(">> ");
        fgets(cmd, 1023, stdin);
        if (cmd[0] == '&')
        {
            if (fork() == 0)
            {
                char whatever[8][64];
                split(cmd + 1, whatever);
                printf("%s", whatever[0]);
                execve(whatever[0], whatever, NULL);
                perror("execve");
                return 1;
            }
        }
        else
        {
            system(cmd);
        }
    }
}