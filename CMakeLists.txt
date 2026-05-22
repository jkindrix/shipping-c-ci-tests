cmake_minimum_required(VERSION 3.15)
project(primes C)

find_package(ZLIB REQUIRED)

add_library(primes_warnings INTERFACE)
target_compile_options(primes_warnings INTERFACE
    -Wall -Wextra -Wpedantic
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>)
target_link_options(primes_warnings INTERFACE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>)

add_library(primes_lib primes.c)
target_include_directories(primes_lib PUBLIC .)
target_link_libraries(primes_lib PRIVATE primes_warnings)

add_executable(primes main.c)
target_link_libraries(primes PRIVATE
    primes_lib
    primes_warnings
    ZLIB::ZLIB)

install(TARGETS primes RUNTIME DESTINATION bin)
install(TARGETS primes_lib ARCHIVE DESTINATION lib)
install(FILES primes.h DESTINATION include)

option(BUILD_FUZZER "Build the libFuzzer harness (requires clang)" OFF)
if(BUILD_FUZZER)
    add_executable(fuzz_primes fuzz_primes.c)
    target_link_libraries(fuzz_primes PRIVATE primes_lib)
    target_compile_options(fuzz_primes PRIVATE
        -fsanitize=fuzzer,address,undefined)
    target_link_options(fuzz_primes PRIVATE
        -fsanitize=fuzzer,address,undefined)
endif()
