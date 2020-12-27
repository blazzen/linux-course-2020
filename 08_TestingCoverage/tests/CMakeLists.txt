cmake_minimum_required(VERSION 3.10)

project(Tests)

include_directories("../src")
link_directories("../src")

add_executable(bufs_test tests.c)
target_link_libraries(bufs_test PUBLIC buf)

add_test(capacity-init bufs_test capacity-init)
add_test(size-init bufs_test size-init)
add_test(size-1 bufs_test size-1)
add_test(value bufs_test value)
add_test(clear bufs_test size-init)
add_test(clear-not-free bufs_test clear-not-free)
add_test(free bufs_test free)
add_test(clear-empty bufs_test clear-empty)
add_test(clear-no-op bufs_test clear-no-op)
add_test(size-10000 bufs_test size-10000)
add_test(match-10000 bufs_test match-10000)
add_test(grow-1000 bufs_test grow-1000)
add_test(size-0-grow bufs_test size-0-grow)
add_test(trunc-100 bufs_test trunc-100)
add_test(pop bufs_test pop)

