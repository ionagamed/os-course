#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resources.h>

int main() {
    size_t sz = 10 * 1024 * 1024;  // 10 MB
    for (int i = 0; i < 10; i++) {
        void * ptr = malloc(sz);
        memset(ptr, 0, sz);
        sleep(1);
    }
}