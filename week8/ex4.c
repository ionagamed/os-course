#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>

int main() {
    size_t sz = 10 * 1024 * 1024;  // 10 MB
    for (int i = 0; i < 10; i++) {
        void * ptr = malloc(sz);
        memset(ptr, 0, sz);

        struct rusage * p = malloc(sizeof(struct rusage));
        getrusage(RUSAGE_SELF, p);
        printf("Memory usage: %d\n", p->ru_maxrss);

        sleep(1);
    }
}