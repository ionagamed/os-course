#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    argv++;
    argc--;
    char *filenames[10];
    int filenames_p = 0;
    char *append_filenames[10];
    int append_filenames_p = 0;
    while (argc)
    {
        if (strcmp(argv[0], "-a") == 0)
        {
            argv++;
            argc--;
            append_filenames[append_filenames_p++] = argv[0];
            argv++;
            argc--;
        }
        else
        {
            filenames[filenames_p++] = argv[0];
            argv++;
            argc--;
        }
    }

    int incoming_fd = open("/dev/stdin", O_RDONLY);
    int fds[21];
    fds[0] = open("/dev/stdout", O_WRONLY);
    int fds_p = 1;
    for (int i = 0; i < filenames_p; i++)
    {
        fds[fds_p++] = open(filenames[i], O_WRONLY | O_CREAT, 0666);
    }
    for (int i = 0; i < append_filenames_p; i++)
    {
        fds[fds_p++] = open(append_filenames[i], O_APPEND | O_WRONLY | O_CREAT, 0666);
    }

    uint8_t buf[512];
    uint32_t bytes = 0;

    while ((bytes = read(incoming_fd, buf, sizeof(buf))))
    {
        for (int i = 0; i < fds_p; i++)
        {
            write(fds[i], buf, bytes);
        }
    }

    return 0;
}