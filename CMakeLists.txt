# Specify the minimum version for CMake
cmake_minimum_required(VERSION 2.6)

# Project's name
project(test)
message(PROJECT:${PROJECT_NAME})

# cmake top-level dir
message(CMAKE_SOURCE_DIR:${CMAKE_SOURCE_DIR})
# project path
message(PROJECT_SOURCE_DIR:${PROJECT_SOURCE_DIR})

# output path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
message(EXECUTABLE_OUTPUT_PATH:${EXECUTABLE_OUTPUT_PATH})

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
message(LIBRARY_OUTPUT_PATH:${LIBRARY_OUTPUT_PATH})

# ================================================

# add_subdirectory(sub1)
# add_subdirectory(sub2)

# header files path
include_directories("${CMAKE_SOURCE_DIR}/../../include")

# build executable
add_executable(hello ${PROJECT_SOURCE_DIR}/hello.cc)
add_executable(client ${PROJECT_SOURCE_DIR}/client.cc)
add_executable(server ${PROJECT_SOURCE_DIR}/server.cc)
add_executable(lock_step_test ${PROJECT_SOURCE_DIR}/ls_server.cc)

# link library
target_link_libraries(server ${CMAKE_SOURCE_DIR}/../../libs/libenet.a)
target_link_libraries(client ${CMAKE_SOURCE_DIR}/../../libs/libenet.a)
