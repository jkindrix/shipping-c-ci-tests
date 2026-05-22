#include <stdio.h>
#include <zlib.h>
#include "primes.h"

int main(void) {
    fprintf(stderr, "primes (using zlib %s)\n", zlibVersion());
    int max;
    printf("Enter an integer (at least 2):\n");
    if (scanf("%d", &max) != 1 || max < 2) {
        printf("Need an integer at least 2.\n");
        return 1;
    }
    print_primes_up_to(max);
    return 0;
}
