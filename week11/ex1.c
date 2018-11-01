#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>

int main() {
    char * target_str = "This is a nice day";
    int i;

    int fd = open("./ex1.txt", O_RDWR);
    if (fd < 0) {
        perror("open ./ex1.txt");
        return -1;
    }

    struct stat file_stat = {};
    if (fstat(fd, &file_stat)) {
        perror("fstat");
        return -1;
    }
    size_t file_size = file_stat.st_size;

    uint8_t * buf = (uint8_t*) malloc(file_size);
    if (!buf) {
        perror("malloc");
        return -1;
    }

    if (!(buf = mmap(buf, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0))) {
        perror("mmap");
        return -1;
    }

    for (i = 0; target_str[i]; i++) {
        buf[i] = target_str[i];
    }
    for (; i < file_size; i++) {
        buf[i] = ' ';
    }

    if (msync(buf, file_size, MS_SYNC)) {
        perror("msync");
        return -1;
    }
    return 0;
}