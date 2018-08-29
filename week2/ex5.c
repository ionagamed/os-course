#include <stdio.h>
#include <string.h>

int abs(int v) {
    if (v < 0) {
        return -v;
    } else {
        return v;
    }
}

void output_line_tree(int step, const int width) {
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

void output_line_square(int step, const int width) {
    for (int i = 0; i < width; i++) {
        printf("*");
    }
    printf("\n");
}

void output_line_triangle(int step, const int width) {
    for (int i = 0; i <= step; i++) {
        printf("*");
    }
    printf("\n");
}

void output_line_arrow(int step, const int width) {
    int height = width / 2 + 1;
    int mean = height / 2;
    for (int i = 0; i <= mean - abs(step - mean); i++) {
        printf("*");
    }
    printf("\n");
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <height> <tree | triangle | arrow | square>\n", argv[0]);
        return 255;
    }
    int height;
    sscanf(argv[1], "%d", &height);
    if (strcmp(argv[2], "tree") == 0) {
        for (int i = 0; i < height; i++) {
            output_line_tree(i, height * 2 - 1);
        }
    } else if (strcmp(argv[2], "triangle") == 0) {
        for (int i = 0; i < height; i++) {
            output_line_triangle(i, height * 2 - 1);
        }
    } else if (strcmp(argv[2], "arrow") == 0) {
        for (int i = 0; i < height; i++) {
            output_line_arrow(i, height * 2 - 1);
        }
    } else if (strcmp(argv[2], "square") == 0) {
        for (int i = 0; i < height; i++) {
            output_line_square(i, height * 2 - 1);
        }
    } else {
        printf("Usage: %s <height> <tree | triangle | arrow | square>\n", argv[0]);
        return 255;
    }
}
