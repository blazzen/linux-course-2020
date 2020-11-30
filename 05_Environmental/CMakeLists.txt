cmake_minimum_required(VERSION 3.10)

project(RegexWindow)

find_library(NCURSES_LIB ncursesw)
if (NOT NCURSES_LIB)
    message(FATAL_ERROR "ncursesw library not found")
endif()

find_library(PCRE_LIB pcre2-8)
if (NOT PCRE_LIB)
    message(FATAL_ERROR "pcre2-8 library not found")
endif()

add_custom_target(allclean COMMAND rm -rf build CMakeCache.txt CMakeFiles cmake_install.cmake Makefile RegexWindow)

option(without-UTF "Don't use UTF" OFF)
if(without-UTF)
    add_definitions(-DWITHOUT_UTF=1)
else()
    add_definitions(-DWITHOUT_UTF=0)
endif()

add_executable(RegexWindow Window.c)

target_link_libraries(RegexWindow PUBLIC ncursesw)
target_link_libraries(RegexWindow PUBLIC pcre2-8)

