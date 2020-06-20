#! /usr/bin/env python

import os
from py_clib import *

if __name__ == "__main__":
    print('')

    print('Sum is {}'.format(add_2(5, 10)))
    print('')

    print('Sum is {}'.format(add_3(5, 10, 15)))
    print('')

    print('Sum is {}'.format(add_4(5, 10, 15, -20)))
    print('')

    t = Test(10, 1)
    print_struct(t)
    print(t)
    print('')

    u = Test(10, 1)
    print_struct_ptr(u)
    print(u)
    print('')
