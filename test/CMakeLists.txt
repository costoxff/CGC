project("tset")

add_executable(gc_test gc_test.c)
target_link_libraries(gc_test
    PRIVATE
)

add_executable(pool_func_test pool_func_test.c)
target_link_libraries(pool_func_test
    PRIVATE
)