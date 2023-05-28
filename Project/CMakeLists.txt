cmake_minimum_required(VERSION 3.24)
project(Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Tables_run Main.cpp)

include_directories(Tables_lib)
add_subdirectory(Tables_lib)

target_link_libraries(Tables_run Tables_lib)

add_subdirectory(Tables_tests)