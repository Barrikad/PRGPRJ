#include <assert.h>
#include <stdio.h>

// Configures the assertion handler to write to UART.
// Requires that UART is setup.
// If you want to disable assertions, define NDEBUG as pr. the ANSI standard
void __assert_func(const char * file, int line, const char * func, const char * expr) {
    printf("assertion \"%s\" failed in %s: file \"%s\", line %i\n", expr, func, file, line);
    while(1) {}
}
