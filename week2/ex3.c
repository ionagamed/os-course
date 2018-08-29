#include <stdio.h>

int abs(int v) {
    if (v < 0) {
        return -v;
    } else {
        return v;
    }
}

void output_line(int step, const int width) {
    int mean = width / 2 + 1;
    for (int i = 1; i <= width; i++) { 
        if (abs(i - mean) <= step) {
            printf("*");
        } else {
            printf(" ");
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <height of the tree>\n", argv[0]);
        return 255;
    }
    int height;
    sscanf(argv[1], "%d", &height);

    for (int i = 0; i < height; i++) {
        output_line(i, height * 2 - 1);
    }
}
