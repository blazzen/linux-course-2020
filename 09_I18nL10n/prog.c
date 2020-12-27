#include <stdio.h>
#include <string.h>

int main(void) {
    printf("Please, think of a number from 1 to 100\n");

    char ans;
    unsigned char min = 1;
    unsigned char max = 100;
    do {
        unsigned char half = (min + max) / 2;
        printf("Is your number greater than %hhu? (y - yes, n - no)\n", half);
        while ((ans = getchar()) != 'y' && (ans != 'n'));
        if (ans == 'y') {
            min = half + 1;
        } else {
            max = half;
        }
    } while (min != max);

    printf("Your number is %hhu\n", max);

    return 0;
}
