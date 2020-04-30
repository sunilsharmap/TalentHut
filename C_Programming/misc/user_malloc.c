/*
 * user_malloc.c
 *
 * Description:
 *
 *  Created on: 30-Apr-2020
 *      Author: Sunil Sharma P <sunilsharma.pv@gmail.com>
 *
 *     Version: 1.0v
 */

#include <stdio.h>

typedef struct free_list {
    int available;
    int size;
} f_list;

enum {
    FREE,
    USING
};

enum {
    NEW_MEM,
    NO_MEM,
    REUSE_MEM
};

char *heap_start;
char *heap_end;
int max_memory;
int alloc_memory;
int st_count;

void init_memory(char *ptr, int size_bytes)
{
    max_memory = size_bytes;
    heap_start = ptr;
    heap_end = heap_start + size_bytes;
    alloc_memory = 0;
    st_count = 0;
}

void* test_malloc(int element_size)
{
    f_list *f_ptr;
    int flag = NO_MEM;
    int size;

    f_ptr = (f_list*) heap_start;
    size = sizeof(f_list);
    if((element_size + size) > max_memory - (alloc_memory + st_count * size)) {
        return NULL;
    }

    while(heap_end > ((char*) f_ptr + element_size + size)) {
        if(f_ptr->available == 0) {
            if(f_ptr->size == 0) {
                flag = NEW_MEM;
                break;
            }
            if(f_ptr->size >= (element_size + size)) {
                flag = REUSE_MEM;
                break;
            }
        }
        f_ptr = (f_list*) ((char*) f_ptr + f_ptr->size);
    }

    if(flag != NO_MEM) {
        f_ptr->available = 1;
        if(flag == NEW_MEM) {
            f_ptr->size = element_size + sizeof(f_list);
        }
        else if(flag == 2) {
            element_size = f_ptr->size - sizeof(f_list);
        }
        st_count++;
        alloc_memory = alloc_memory + element_size;
        return ((void*) f_ptr + size);
    }

    return NULL;
}

void test_free(void* ptr)
{
    f_list *p = (f_list*) ptr;
    p--;
    if(p->available == USING) {
        st_count--;
        p->available = FREE;
        alloc_memory = alloc_memory - (p->size - sizeof(f_list));
    }
}

int main(int argc, char *argv[])
{
    /* This is the total memory available */
    char heap[1024] = {0};

    char *c_ptr1, *c_ptr2, *c_ptr3, *c_ptr4;

    printf("     Start address of heap  : %p\n", &heap[0]);

    init_memory(heap, 1024);

    c_ptr1 = (char*) test_malloc(400);
    printf("%d   c_ptr1 holds address   : %p\tAvailable Memory: %d bytes\n", __LINE__, c_ptr1, (max_memory - (alloc_memory + st_count * 8)));

    c_ptr2 = (char*) test_malloc(200);
    printf("%d   c_ptr2 holds address   : %p\tAvailable Memory: %d bytes\n", __LINE__, c_ptr2, (max_memory - (alloc_memory + st_count * 8)));

    c_ptr3 = (char*) test_malloc(500);
    printf("%d   c_ptr3 holds address   : %p\t\tAvailable Memory: %d bytes\n", __LINE__, c_ptr3, (max_memory - (alloc_memory + st_count * 8)));

    test_free(c_ptr2);

    c_ptr4 = (char*) test_malloc(450);
    printf("%d   c_ptr4 holds address   : %p\t\tAvailable Memory: %d bytes\n", __LINE__, c_ptr4, (max_memory - (alloc_memory + st_count * 8)));

    c_ptr1 = (char*) test_malloc(300);
    printf("%d   c_ptr1 holds address   : %p\tAvailable Memory: %d bytes\n", __LINE__, c_ptr1, (max_memory - (alloc_memory + st_count * 8)));

    test_free(c_ptr1);

    c_ptr2 = (char*) test_malloc(400);
    printf("%d   c_ptr2 holds address   : %p\t\tAvailable Memory: %d bytes\n", __LINE__, c_ptr2, (max_memory - (alloc_memory + st_count * 8)));

    return 0;
}
