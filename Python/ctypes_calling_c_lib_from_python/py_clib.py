'''
 Clib wrapper API's to use it in python
'''

from ctypes import CDLL, Structure, c_int, c_uint, POINTER
import os

# C Structure equivalent class
class Test(Structure):
    _fields_ = [('age', c_int), ('id', c_int)]
    
    def __repr__(self):
        return 'Inside Python: age: {0}, id: {1}'.format(self.age, self.id)

# Function to get the referece to clib API's
def TYPE(func, res_t, args_t):
    func.argtypes = args_t
    func.restype = res_t
    return func

# load the shared library into c types.
libname = os.path.abspath(os.path.join(os.path.dirname(__file__), "libclib.so"))
LIBC = CDLL(libname)

# Python wrapper to clib API"s
add_2 = TYPE(LIBC.add_2, c_uint, (c_uint,))

add_3 = TYPE(LIBC.add_3, c_uint, (c_uint, c_uint, c_uint,))

add_4 = TYPE(LIBC.add_4, c_uint, (c_uint, c_uint, c_uint, c_int,))

print_struct = TYPE(LIBC.print_struct, None, (Test,))

print_struct_ptr = TYPE(LIBC.print_struct_ptr, None, (POINTER(Test),))
