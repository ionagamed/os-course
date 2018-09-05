#include <stdio.h>
#include <stdlib.h>

void swap(int * a, int * b) {
    // *a ^= *b;
    // *b ^= *a;
    // *a ^= *b;
    int t = *a;
    *a = *b;
    *b = t;
}

void qsort_(int * a, int l, int r) {
    if (l > r) return;
    int pivot_value = a[r];
    int m = l;
    for (int i = l; i < r; i++) {
        if (a[i] <= pivot_value) {
            swap(&a[m], &a[i]);
            m++;
        }
    }
    swap(&a[m], &a[r]);
    qsort_(a, l, m - 1);
    qsort_(a, m + 1, r);
}

int main() {
    int n;
    scanf("%d", &n);
    int * a = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    qsort_(a, 0, n - 1);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
}