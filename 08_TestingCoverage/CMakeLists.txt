cmake_minimum_required(VERSION 3.10)

project(UnitTests)
include(CTest)

set(CMAKE_C_FLAGS "-O0 -fprofile-arcs -ftest-coverage")

add_custom_target(
    allclean COMMAND rm -rf
    CMakeCache.txt CMakeFiles cmake_install.cmake Makefile CTestTestfile.cmake Testing DartConfiguration.tcl
    src/CMakeCache.txt src/CMakeFiles src/cmake_install.cmake src/Makefile src/CTestTestfile.cmake
    tests/CMakeCache.txt tests/CMakeFiles tests/cmake_install.cmake tests/Makefile tests/CTestTestfile.cmake
    src/libbuf.so tests/bufs_test
)

enable_testing()

add_subdirectory(src src)
add_subdirectory(tests tests)

