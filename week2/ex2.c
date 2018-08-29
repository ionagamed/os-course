#include <stdio.h>
#include <string.h>

int main() {
    char buf[100];
    fgets(buf, 99, stdin);

    size_t len = strlen(buf);
    for (int i = len - 1; i >= 0; i--) {
        printf("%c", buf[i]);
    }

    printf("\n");
}
