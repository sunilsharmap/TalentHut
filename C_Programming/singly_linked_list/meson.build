project('sll', 'c',
  default_options: ['werror=true', 'buildtype=debugoptimized'],
  version: '0.0.1',
)

incs = include_directories('include')

# Library Creatinon

lib_srcs = files(
  'src/node.c',
)

host = build_machine.system()
if host == 'windows'
  args = ['-DBUILD_SHARED_LIB']
  so_version = ''
else
  args = []
  so_version = 0
endif

libnode = library('node', lib_srcs,
  include_directories: incs,
  c_args: args,
  soversion: so_version,
  version: meson.project_version(),
)

libnode_dep = declare_dependency(
  include_directories: incs,
  link_with: libnode,
)

# Application / Executable creation
srcs = files(
  'src/cli/main.c',
)

executable('sll', srcs,
  dependencies: [libnode_dep],
  install: true,
)
