#include "main.h"

int main()
{
    Test *st_ptr = NULL;
    st_ptr = create_st();
    if(!st_ptr)
        return -1;

    set_id(st_ptr, 10);
          
    printf("ID = %d\n", get_id(st_ptr));

    free_st(st_ptr);
          
    return 0;
}
