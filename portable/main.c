#include "portable_setup.h"

#include <stdio.h>

int main(void) {
    char path[1024];
    if (portable_get_executable_path(path, sizeof path) != 0) {
        fprintf(stderr, "could not read executable path\n");
        return 1;
    }
    printf("OS:       %s\n", PORTABLE_OS_NAME);
    printf("Compiler: %s\n", PORTABLE_CC_NAME);
    printf("Path:     %s\n", path);
    return 0;
}
