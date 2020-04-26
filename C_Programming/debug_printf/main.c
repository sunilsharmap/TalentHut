#include "header.h"

extern int call_main();

int main()
{
    printf("This is Printf\n");
    debug_printf("This is debug_printf @ Line: %s : %s\n", __FILE__, __func__);
    printf("This is Printf\n");
    debug_printf("This is debug_printf @ Line: %d\n", __LINE__);
    call_main();
    return 0;
}
