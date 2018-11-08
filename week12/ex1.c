#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd = open("/dev/random");
    char s[21];
    read(fd, s, 20);
    s[20] = 0;
    printf("%s", s);

    return 0;
}