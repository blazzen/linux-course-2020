cmake_minimum_required(VERSION 3.10)

project(LocalizedProg)

add_custom_target(allclean COMMAND rm -rf CMakeCache.txt CMakeFiles cmake_install.cmake Makefile LocalizedProg)

add_executable(LocalizedProg prog.c)

