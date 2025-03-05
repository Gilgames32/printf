project('printf', 'cpp',
  default_options: ['cpp_std=c++23']
)

# Dependencies
nlohmann_json = dependency('nlohmann_json', required: true)
opencv = dependency('opencv4', required: true)
qt6_dep = dependency('qt6', modules: ['Core'])


incdir = include_directories(
  'src',
  'src/interfaces',
  'src/img',
  'src/img/filters',
  'src/img/tiling',
  'src/settings',
  'src/util'
)

# Source files
srcs = files(
  'src/img/filters/mask.cpp',
  'src/img/filters/rotate.cpp',
  'src/img/filters/size.cpp',
  'src/img/filters/padding.cpp',
  'src/img/tiling/grid_tiling.cpp',
  'src/img/cached_image.cpp',
  'src/img/image_source.cpp',
  'src/settings/document_preset.cpp',
  'src/main.cpp'
)

# Executable
executable('printf', srcs,
  include_directories : incdir,
  dependencies: [nlohmann_json, opencv, qt6_dep]
)
