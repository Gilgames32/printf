project('printf', 'cpp',
  default_options: ['cpp_std=c++23']
)

# Dependencies
nlohmann_json = dependency('nlohmann_json', required: true)
opencv = dependency('opencv4', required: true)
qt6_dep = dependency('qt6', modules: ['Core'])


incdir = include_directories(
  'src', 
)

# Source files
srcs = files(
  'src/main.cpp',
)

# Executable
executable('printf', srcs,
  include_directories : incdir,
  dependencies: [nlohmann_json, opencv, qt6_dep]
)
