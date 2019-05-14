#include <stdio.h>
#include <stdlib.h>

// Assume we need 32-byte alignment for AVX instructions
#define ALIGN 32

void *aligned_malloc(int size)
{
    // We require whatever user asked for PLUS space for a pointer
    // PLUS space to align pointer as per alignment requirement
    void *mem = malloc(size + sizeof(void*) + (ALIGN - 1));
    printf("malloc %p\n", mem);

    // Location that we will return to user
    // This has space *behind* it for a pointer and is aligned
    // as per requirement
    void *ptr = (void**)((int)(mem + (ALIGN - 1) + sizeof(void*)) & ~(ALIGN - 1));
    printf("((int)(mem + (ALIGN - 1) + sizeof(void*)) & ~(ALIGN - 1)) %p\n", ((int)(mem + (ALIGN - 1) + sizeof(void*)) & ~(ALIGN - 1)));
    printf("allign %p\n", ptr);

    // Sneakily store address returned by malloc *behind* user pointer
    // void** cast is cause void* pointer cannot be decremented, cause
    // compiler has no idea "how many" bytes to decrement by
    ((void **) ptr)[-1] = mem;

    // Return user pointer
    return ptr;
}

void aligned_free(void *ptr)
{
    // Sneak *behind* user pointer to find address returned by malloc
    // Use that address to free
    printf("free  %p\n", (((void**) ptr)[-1]));
    free(((void**) ptr)[-1]);
}

int main()
{
    int *ptr = (int *)aligned_malloc(10);
    aligned_free((void *)ptr);
    printf("%lu\n", sizeof(void*));
    return 0;
}
