#include "main.h"

int main()
{
    Test *st_ptr = NULL;
    st_ptr = create_st();
    if(!st_ptr) {
        return -1;
    }

    // This is the hiding, directly you cannot access the members of ``Test`` structure.
    // Use ``set/get`` api's to access the Structure Test

    // st_ptr->id = 10;  // Error

    set_id(st_ptr, 10);

    // printf("ID = %d\n", st_ptr->id);  // Error

    printf("ID = %d\n", get_id(st_ptr));

    free_st(st_ptr);

    return 0;
}
