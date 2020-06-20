#include <stdio.h>
#include <stdint.h>

struct test {
    int age;
    int id;
};

void print_struct(struct test st)
{
    printf("Inside C     : age: %d, id: %d\n", st.age, st.id);
    st.age = 20;
    st.id = 2;
}

void print_struct_ptr(struct test *st)
{
    printf("Inside C Ptr : age: %d, id: %d\n", st->age, st->id);
    st->age = 20;
    st->id = 2;
}

uint32_t add_2(uint32_t x, uint32_t y)
{
    return (x + y);
}

uint32_t add_3(uint32_t a, uint32_t b, uint32_t c)
{
    return (a + b +c);
}

uint32_t add_4(uint32_t p, uint32_t q, uint32_t r, int32_t s)
{
    return (p + q + r + s);
}
