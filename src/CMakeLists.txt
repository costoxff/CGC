add_library(libcgc SHARED)

target_sources(libcgc
    PRIVATE
        "gc.c"
)

target_include_directories(libcgc
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)