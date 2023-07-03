project('math', 'c',
  default_options: ['werror=false', 'buildtype=debugoptimized'],
  version: '1.0.0',
)

libglib_dep = dependency('glib-2.0', required: true,
                         fallback: ['glib', 'libglib_dep'])

incs = include_directories('include')

# Library Creation

lib_srcs = files(
  'src/mathematics.c',
)

host = build_machine.system()
if host == 'windows'
  args = ['-DBUILD_SHARED_LIB']
  so_version = ''
else
  args = []
  so_version = 0
endif

libmath = library('math', lib_srcs,
  include_directories: incs,
  c_args: args,
  soversion: so_version,
  install: true,
  version: meson.project_version(),
)

libmath_dep = declare_dependency(
  include_directories: incs,
  link_with: libmath,
)

# Application / Executable creation
srcs = files(
  'src/cli/main.c',
)

executable('client', srcs,
  dependencies: [libmath_dep, libglib_dep],
  install: true,
)

# Unit Tests creation

test_env = [
  'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
  'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir())
]

addition_tests = executable('addition',
  'tests/addition_tests.c',
  dependencies: [libmath_dep, libglib_dep],
  include_directories: incs,
  install: true,
)

test(
  'addition_tests',
  addition_tests,
  env: test_env,
)

subtraction_tests = executable('subtraction',
  'tests/subtraction_tests.c',
  dependencies: [libmath_dep, libglib_dep],
  include_directories: incs,
  install: true,
)

test(
  'subtraction_tests',
  subtraction_tests,
  env: test_env,
)

multiplication_tests = executable('multiplication',
  'tests/multiplication_tests.c',
  dependencies: [libmath_dep, libglib_dep],
  include_directories: incs,
  install: true,
)

test(
  'multiplication_tests',
  multiplication_tests,
  env: test_env,
)

division_tests = executable('division',
  'tests/division_tests.c',
  dependencies: [libmath_dep, libglib_dep],
  include_directories: incs,
  install: true,
)

test(
  'division_tests',
  division_tests,
  env: test_env,
)
