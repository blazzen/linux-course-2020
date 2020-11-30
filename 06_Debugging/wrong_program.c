#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum {
    N = 10
};

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int *a = malloc(N * sizeof(*a));
    long sum = 0;
    for (int i = 0; i < N; ++i) {
        a[i] = rand();
        sum += a[i];
    }

    for (int i = 0; i < N; ++i) {
        printf("%d ", a[i]);
    }
    printf("\nSum = %ld\n", sum);

    free(a);
    free(a); // on purpose

    return 0;
}
