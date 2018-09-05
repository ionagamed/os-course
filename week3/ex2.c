#include <stdio.h>
#include <stdlib.h>

void swap(int * a, int * b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void bubble_sort(int * array, size_t size) {
    int swapped = 0;
    do {
        swapped = 0;
        for (int i = 1; i < size; i++) {
            if (array[i - 1] > array[i]) {
                swap(&array[i - 1], &array[i]);
                swapped = 1;
            }
        }
        size--;
    } while (swapped);
}

int main() {
    int n;
    scanf("%d", &n);
    int * a = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    bubble_sort(a, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
}