#include <stdint.h>
#include <stdio.h>
#include <float.h>
#include <limits.h>

int main() {
    int i = INT_MAX;
    float f = FLT_MAX;
    double d = DBL_MAX;

    printf("%d %lu\n", i, sizeof(i));
    printf("%f %lu\n", f, sizeof(f));
    printf("%lf %lu\n", d, sizeof(d));

    return 0;
}
