Data Hiding in C
--------------------

lib variables are protected, use always `setter/getter` api's

`struct test` is not known to `main.c` and `main.h`

`main.c/h` knows only `Test`. main.h declares Test as `typedef struct test Test`, but not aware of `struct test`.

But `lib.c` aware of both `Test` and `struct test`, hence struct variables can be accessed inside `lib.c`.
Hence `main.c` cannot access members of Test.
