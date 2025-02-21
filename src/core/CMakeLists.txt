file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.h)

add_library(CoreLib
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(CoreLib PUBLIC .)
