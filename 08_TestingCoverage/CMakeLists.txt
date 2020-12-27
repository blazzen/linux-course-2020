cmake_minimum_required(VERSION 3.10)

project(GrowableBufs)

add_custom_target(allclean COMMAND rm -rf build CMakeCache.txt CMakeFiles cmake_install.cmake Makefile libbuf.so GrowableBufs)

add_library(buf SHARED buf.c)
add_executable(GrowableBufs tests.c)
target_link_libraries(GrowableBufs PUBLIC buf)

