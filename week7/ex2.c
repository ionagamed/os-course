#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main() {
    printf("How many array entries to create: ");
    int n; 
    scanf("%d", &n);
    int *a = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    printf("Here are your numbers: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    free(a);
    return 0;
}