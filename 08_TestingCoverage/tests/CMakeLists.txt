cmake_minimum_required(VERSION 3.10)

project(Tests)

include_directories("../src")
link_directories("../src")

add_executable(bufs_test tests.c)
target_link_libraries(bufs_test PUBLIC buf)

add_test(simple bufs_test)

