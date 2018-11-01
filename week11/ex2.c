#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char * str = "Hello";
    int i;

    if (setvbuf(stdout, 0, _IOLBF, 0)) {
        perror("setvbuf");
        return -1;
    }

    for (i = 0; str[i]; i++) {
        printf("%c", str[i]);
        sleep(1);
    }
}