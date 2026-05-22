#ifndef PORTABLE_SETUP_H
#define PORTABLE_SETUP_H

/*
 * portable_setup.h
 *
 * One header that every translation unit in the project includes
 * first. It detects the host OS and compiler, sets feature-test
 * macros where required, and exposes a small set of portable
 * abstractions over the platform differences.
 */

/* --- OS detection --- */
#if defined(_WIN32)
#  define PORTABLE_OS_WINDOWS 1
#  define PORTABLE_OS_NAME "windows"
#elif defined(__APPLE__) && defined(__MACH__)
#  define PORTABLE_OS_MACOS 1
#  define PORTABLE_OS_NAME "macos"
#elif defined(__linux__)
#  define PORTABLE_OS_LINUX 1
#  define PORTABLE_OS_NAME "linux"
#elif defined(__FreeBSD__)
#  define PORTABLE_OS_FREEBSD 1
#  define PORTABLE_OS_NAME "freebsd"
#else
#  error "Unsupported operating system"
#endif

/* --- Feature-test macros (POSIX-only) --- */
#if !defined(PORTABLE_OS_WINDOWS)
#  ifndef _POSIX_C_SOURCE
#    define _POSIX_C_SOURCE 200809L
#  endif
#endif

/* --- Compiler detection --- */
#if defined(__clang__)
#  define PORTABLE_CC_NAME "clang"
#elif defined(__GNUC__)
#  define PORTABLE_CC_NAME "gcc"
#elif defined(_MSC_VER)
#  define PORTABLE_CC_NAME "msvc"
#else
#  define PORTABLE_CC_NAME "unknown"
#endif

/* --- Public abstractions --- */
#include <stddef.h>

/* Fill `buf` with the absolute path of the running executable.
 * Returns 0 on success, -1 on failure. `size` is the buffer size. */
int portable_get_executable_path(char *buf, size_t size);

#endif
