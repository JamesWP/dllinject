cmake_minimum_required(VERSION 3.13)

project(dllinject CXX)

find_package(LIEF REQUIRED)


add_executable(patcher patcher.cpp)
target_link_libraries(patcher PRIVATE LIEF::LIEF)

add_library(test_library SHARED live_patcher.cpp)

add_executable(test_executable test_exec.cpp)
target_link_libraries(test_executable PUBLIC test_library)