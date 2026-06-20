# printf

printf is a work in progress tiling program for plotters built in c++ using opencv and qt6

a more detailed description will be added later

im on arch (btw) and i had to install these packages:
- pkg-config
- gcc
- cmake
- ninja
- meson
- opencv
- qt6-base qt6-tools qt6-declarative qt6-wayland
- nlohmann-json
- libspng
- exiv2
- poppler-qt6

## how to build on windows

- get meson
    - `winget install -e --id mesonbuild.meson`
- get msys2
    - `winget install -e --id MSYS2.MSYS2`
- in the msys2 shell install the required packages
    - `pacman -S mingw-w64-ucrt-x86_64-opencv mingw-w64-ucrt-x86_64-qt6-base mingw-w64-ucrt-x86_64-qt6-declarative mingw-w64-ucrt-x86_64-exiv2 mingw-w64-ucrt-x86_64-libspng mingw-w64-ucrt-x86_64-poppler-qt6`
