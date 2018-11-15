#include <stdio.h>
#include <stdlib.h>

#define PROCESS_CNT 5
#define RESOURCE_CNT 3

struct memory_status
{
    int existing[RESOURCE_CNT];
    int available[RESOURCE_CNT];
    int allocation[PROCESS_CNT][RESOURCE_CNT];
    int request[PROCESS_CNT][RESOURCE_CNT];
};

void usage(char **argv)
{
    printf("Usage:\n");
    printf("  %s <input_file>\n", argv[0]);
}

int open_input_file(int argc, char **argv, FILE **input_fd)
{
    if (argc < 2)
    {
        usage(argv);
        return -1;
    }
    *input_fd = fopen(argv[1], "r");
    return 0;
}

void input_data(FILE *input_fd, struct memory_status *data)
{
    int i, j;
    for (i = 0; i < RESOURCE_CNT; i++)
    {
        fscanf(input_fd, "%d", &data->existing[i]);
    }
    for (i = 0; i < RESOURCE_CNT; i++)
    {
        fscanf(input_fd, "%d", &data->available[i]);
    }
    for (i = 0; i < PROCESS_CNT; i++)
    {
        for (j = 0; j < RESOURCE_CNT; j++)
        {
            fscanf(input_fd, "%d", &data->allocation[i][j]);
        }
    }
    for (i = 0; i < PROCESS_CNT; i++)
    {
        for (j = 0; j < RESOURCE_CNT; j++)
        {
            fscanf(input_fd, "%d", &data->request[i][j]);
        }
    }
}

int can_finish(int process, struct memory_status *data)
{
    int process_can_finish = 1, i;
    for (i = 0; i < RESOURCE_CNT; i++)
    {
        if (data->request[process][i] > data->available[i])
        {
            process_can_finish = 0;
        }
    }
    return process_can_finish;
}

void finish(int process, struct memory_status *data)
{
    int i;
    for (i = 0; i < RESOURCE_CNT; i++)
    {
        data->available[i] += data->allocation[process][i];
    }
}

int check_for_deadlock(struct memory_status *data, int *deadlocked)
{
    int i, j;
    int finished_processes = 0;
    int finish_algorithm = 0;
    for (i = 0; i < PROCESS_CNT; i++)
    {
        deadlocked[i] = 1;
    }
    while (!finish_algorithm)
    {
        finish_algorithm = 1;
        for (i = 0; i < PROCESS_CNT; i++)
        {
            if (can_finish(i, data) && deadlocked[i])
            {
                finish(i, data);
                deadlocked[i] = 0;
                finished_processes += 1;
                finish_algorithm = 0;
            }
        }
    }
    return finished_processes != PROCESS_CNT;
}

int main(int argc, char **argv)
{
    FILE *input_fd;
    int i, j;
    if (open_input_file(argc, argv, &input_fd))
        return -1;

    struct memory_status data = {};
    input_data(input_fd, &data);

    int deadlocked[PROCESS_CNT];
    int has_deadlock = check_for_deadlock(&data, deadlocked);
    if (!has_deadlock)
    {
        printf("no deadlock is detected\n");
    }
    else
    {
        printf("deadlock is detected, processes are\n");
        for (i = 0; i < PROCESS_CNT; i++)
        {
            if (deadlocked[i])
            {
                printf("%d\n", i);
            }
        }
    }
}
