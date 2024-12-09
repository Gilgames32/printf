cmake_minimum_required(VERSION 3.16)
project(printf)

# Includes
include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

# Set CMAKE_PREFIX_PATH
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CMAKE_BINARY_DIR}/vcpkg_installed")

# Dependencies

# JSON
find_package(nlohmann_json CONFIG REQUIRED)

# OpenCV
find_package(OpenCV REQUIRED)

# CUPS
find_package(Cups REQUIRED)

# Create executable
add_executable(printf src/main.cpp)

# link to your dependencies' targets here
target_link_libraries(printf PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(printf PRIVATE Cups::Cups)
target_link_libraries(printf PRIVATE ${OpenCV_LIBS})

# ---- Properties ----
set_target_properties(printf PROPERTIES CXX_STANDARD 23)
