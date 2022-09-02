project('application', ['c'],
  default_options: ['werror=true', 'buildtype=debugoptimized'],
  version: '0.0.1',
)

dependency_dep = dependency('meson_dependency',
  fallback: ['meson_dependency', 'libdependency_dep']
)

srcs = files(
  'src/main.c',
)

executable('application', sources: 'src/main.c',
  dependencies: [dependency_dep],
  install: true,
)
