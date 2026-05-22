#include <stdio.h>
#include "primes.h"

int is_prime(int n) {
    if (n < 2) {
        return 0;
    }
    for (int i = 2; i < n; i = i + 1) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void print_primes_up_to(int max) {
    for (int n = 2; n <= max; n = n + 1) {
        if (is_prime(n)) {
            printf("%d\n", n);
        }
    }
}
