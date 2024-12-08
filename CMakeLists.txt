# Build and run by calling:
# cmake -S. -Bbuild && cmake --build build && ./build/printf

cmake_minimum_required(VERSION 3.16)

# ---- Project ----
project(printf)


# ---- Include vcpkg ----
include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)


# ---- Set CMAKE_PREFIX_PATH ----
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CMAKE_BINARY_DIR}/vcpkg_installed")


# ---- Dependencies ----
find_package(nlohmann_json CONFIG REQUIRED)


# ---- Create executable ----
# add your source files here
add_executable(printf src/main.cpp)

# link to your dependencies' targets here
target_link_libraries(printf PRIVATE nlohmann_json::nlohmann_json)

# ---- Properties ----
set_target_properties(printf PROPERTIES CXX_STANDARD 23)
