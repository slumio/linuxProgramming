#include <iostream>
#include <gnu/libc-version.h> // For gnu_get_libc_version()

int main() {
    const char* version = gnu_get_libc_version();
    std::cout << "GNU C Library version: " << version << std::endl;
    return 0;
}
