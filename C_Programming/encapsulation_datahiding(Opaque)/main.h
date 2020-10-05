#include <stdio.h>

typedef struct test Test;

void set_id(Test *st, int id);
int get_id(Test *st);
Test *create_st();
void free_st(Test * ptr);
