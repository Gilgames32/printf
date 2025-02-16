project('printf', 'cpp',
  default_options: ['cpp_std=c++17']
)

# Dependencies
nlohmann_json = dependency('nlohmann_json', required: true)
opencv = dependency('opencv4', required: true)
qt6_dep = dependency('qt6', modules: ['Core'])


# Source files
srcs = files(
  'src/img/filters/filter.hpp',
  'src/img/filters/filter_store.hpp',
  'src/img/filters/filter_store.cpp',
  'src/img/filters/mask.hpp',
  'src/img/filters/mask.cpp',
  'src/img/filters/size.hpp',
  'src/img/filters/size.cpp',
  'src/img/source.hpp',
  'src/img/source.cpp',
  'src/img/tiling/tiling.hpp',
  'src/img/tiling/grid_tiling.hpp',
  'src/util/convert.cpp',
  'src/main.cpp',
  'src/settings/document_presets.hpp',
)

# Executable
executable('printf', srcs,
  dependencies: [nlohmann_json, opencv, qt6_dep]
)
