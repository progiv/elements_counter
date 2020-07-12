cmake_minimum_required(VERSION 3.16)
project(elements_counter)

set(CMAKE_CXX_STANDARD 17)

add_executable(elements_counter elements_counter.cpp)

add_subdirectory(downloader)

target_link_libraries(elements_counter downloader)
