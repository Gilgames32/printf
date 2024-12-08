# Build and run by calling:
# cmake -S. -Bbuild && cmake --build build && ./build/printf

cmake_minimum_required(VERSION 3.16)

# ---- Project ----

project(printf)

# ---- Fetch CPM ----

file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.39.0/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
  EXPECTED_HASH SHA256=66639BCAC9DD2907B2918DE466783554C1334446B9874E90D38E3778D404C2EF
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

# ---- Add dependencies via CPM ----

# JSON parsing
CPMAddPackage("gh:nlohmann/json#3.11.3")

# Image manipulation
# from: openCV

# CUPS API
# from: https://github.com/apple/cups

# ---- Create executable ----

# add your source files here
add_executable(printf main.cpp)

# link to your dependencies' targets here
# target_link_libraries(printf JSON::JSON) # TODO: idk man

# setup your target's properties
set_target_properties(printf PROPERTIES CXX_STANDARD 23)
