add_library(libcgc SHARED)
#add_library(libcgc OBJECT)

target_sources(libcgc
    PRIVATE
        "gc.c"
)

target_include_directories(libcgc
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)