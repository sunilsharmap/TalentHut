#include <stdlib.h>
#include "lib.h"
#include "main.h"

void set_id(Test *st, int id)
{
    st->id = id;
}

int get_id(Test *st)
{
    return st->id;
}

Test *create_st()
{
    Test *ptr = (Test*)malloc(sizeof(Test));
    return ptr;        
}

void free_st(Test * ptr)
{
    free(ptr);
}
