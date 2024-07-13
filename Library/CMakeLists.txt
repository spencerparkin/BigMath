# CMakeLists.txt for BigMath library.

set(BIG_MATH_LIB_SOURCES
    Source/BigInteger.cpp
    Source/BigInteger.h
    Source/BigMath.h
)

source_group("Source" TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${BIG_MATH_LIB_SOURCES})

add_library(BigMathLibrary SHARED
    ${BIG_MATH_LIB_SOURCES}
)

target_compile_definitions(BigMathLibrary PRIVATE
    BIG_MATH_EXPORT
    _USE_MATH_DEFINES
)

target_include_directories(BigMathLibrary PUBLIC
    "Source"
)