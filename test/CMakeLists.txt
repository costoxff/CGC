project("unit tset")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_executable(gc_test gc_test.c)
target_link_libraries(gc_test
    PRIVATE
        libcgc
)

add_executable(pool_func_test pool_func_test.c)
target_link_libraries(pool_func_test
    PRIVATE
        libcgc
)
