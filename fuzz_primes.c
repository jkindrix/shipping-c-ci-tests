#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "primes.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0;
    }
    int n;
    memcpy(&n, data, sizeof(int));
    (void)is_prime(n);
    return 0;
}
