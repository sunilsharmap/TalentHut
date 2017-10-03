#include "header.h"

int call_main()
{
    printf("This is Printf\n");
    debug_printf("Testing function call........@ Line: %s\n", __FILE__);
    printf("This is Printf\n");
    debug_printf("Line: %d Func: %s File: %s\n", __LINE__, __func__, __FILE__);
    return 0;
}
