#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

struct mapped_file {
    void * ptr;
    size_t size;
};

int map_file(const char * filename, size_t force_size, struct mapped_file * ret) {
    int fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("open");
        return -1;
    }
    size_t file_size = force_size;
    if (!file_size) {
        struct stat file_stat = {};
        if (fstat(fd, &file_stat)) {
            perror("fstat");
            return -1;
        }
        file_size = file_stat.st_size;
    } else {
        ftruncate(fd, file_size);
    }

    uint8_t * buf;
    if (!(buf = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0))) {
        perror("mmap");
        return -1;
    }

    ret->ptr = buf;
    ret->size = file_size;
    return 0;
}

int main() {
    struct mapped_file * f1 = malloc(sizeof(struct mapped_file));
    struct mapped_file * f2 = malloc(sizeof(struct mapped_file));

    if (map_file("./ex1.txt", 0, f1)) {
        perror("map_file");
        return -1;
    }
    if (map_file("./ex1.memcpy.txt", f1->size, f2)) {
        perror("map_file");
        return -1;
    }

    memcpy(f2->ptr, f1->ptr, f1->size);

    if (msync(f1->ptr, f1->size, MS_SYNC)) {
        perror("msync");
        return -1;
    }
    if (msync(f2->ptr, f2->size, MS_SYNC)) {
        perror("msync");
        return -1;
    }
    return 0;
}