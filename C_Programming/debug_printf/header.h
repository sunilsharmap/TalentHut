#include <stdio.h>

/*
 * This is the code which can be used for debugging pupose.
 * If you compile with DEBUG,i.e. say "gcc testing.c -o testing.out -D DEBUG"
 * then debug_printf() will be printed otherwise skipped.*
 */
#ifndef DEBUG
    #define debug_printf(...)
#else
    #define debug_printf(...) printf (__VA_ARGS__)
#endif
