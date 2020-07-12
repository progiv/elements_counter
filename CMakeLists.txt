cmake_minimum_required(VERSION 3.16)
project(elements_counter)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third-party)
add_subdirectory(downloader)
add_subdirectory(counter)

add_executable(elements_counter elements_counter.cpp)
target_link_libraries(elements_counter downloader counter)
