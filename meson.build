project('printf', 'cpp',
  default_options: ['cpp_std=c++23']
)

# Dependencies
nlohmann_json = dependency('nlohmann_json', required: true)
opencv = dependency('opencv4', required: true)
qt6_dep = dependency('qt6', modules: ['Core', 'Widgets', 'Gui', 'Qml'])




# Qt6 preprocessing
qt6 = import('qt6')

ui_files = files()

moc_headers = files(
  'src/ui/source_entry_view.hpp',
  'src/ui/image_source_view.hpp',
  'src/ui/preset_view.hpp',
  'src/ui/mask_filter_view.hpp',
)

qresources = files('src/qml/resources.qrc')

prep = qt6.preprocess(
  moc_headers : moc_headers,
  ui_files : ui_files,
  qresources : qresources,
)


# Include directories
inc = include_directories(
  'src',
  'src/interfaces',
  'src/img',
  'src/img/filters',
  'src/img/tiling',
  'src/settings',
  'src/util',
  'src/ui',
  'src/qml',
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
  'src/ui/source_entry_view.cpp',
  'src/ui/image_source_view.cpp',
  'src/ui/mask_filter_view.cpp',
  'src/ui/preset_view.cpp',
  'src/util/jsonprobe.cpp',
  'src/main.cpp',
)

# Executable
executable('printf', [srcs, prep],
  include_directories: inc,
  dependencies: [nlohmann_json, opencv, qt6_dep]
)
