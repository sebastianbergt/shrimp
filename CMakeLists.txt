cmake_minimum_required(VERSION 3.10)

project(
  arena
  VERSION 0.1.0
  LANGUAGES CXX)

if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

add_subdirectory(arena)