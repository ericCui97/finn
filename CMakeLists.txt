cmake_minimum_required(VERSION 3.6)
project(finn_server)

set(CMAKE_CXX_STANDARD 20)

add_executable(finn_server src/main.cpp src/stdafx.h src/log.cpp)

add_subdirectory(lib/googletest)
include_directories(${PROJECT_SOURCE_DIR}/src/include lib/googletest/include)
link_directories(${PROJECT_SOURCE_DIR}/lib lib/googletest)
target_link_libraries(${PROJECT_NAME} gtest)