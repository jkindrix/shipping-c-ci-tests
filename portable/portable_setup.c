#include "portable_setup.h"

#include <string.h>

#if PORTABLE_OS_LINUX
#  include <unistd.h>

int portable_get_executable_path(char *buf, size_t size) {
    ssize_t n = readlink("/proc/self/exe", buf, size - 1);
    if (n < 0) {
        return -1;
    }
    buf[n] = '\0';
    return 0;
}

#elif PORTABLE_OS_MACOS
#  include <mach-o/dyld.h>

int portable_get_executable_path(char *buf, size_t size) {
    uint32_t bufsize = (uint32_t)size;
    if (_NSGetExecutablePath(buf, &bufsize) != 0) {
        return -1;
    }
    return 0;
}

#elif PORTABLE_OS_WINDOWS
#  include <windows.h>

int portable_get_executable_path(char *buf, size_t size) {
    DWORD n = GetModuleFileNameA(NULL, buf, (DWORD)size);
    if (n == 0 || n == size) {
        return -1;
    }
    return 0;
}

#elif PORTABLE_OS_FREEBSD
#  include <sys/types.h>
#  include <sys/sysctl.h>

int portable_get_executable_path(char *buf, size_t size) {
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1};
    if (sysctl(mib, 4, buf, &size, NULL, 0) != 0) {
        return -1;
    }
    return 0;
}

#else
#  error "portable_get_executable_path: no implementation for this OS"
#endif
