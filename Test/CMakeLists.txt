# CMakeLists.txt for BigMath test program.

set(BIG_MATH_TEST_SOURCES
    Source/BigMathTest.cpp
)

source_group("Source" TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${BIG_MATH_TEST_SOURCES})

add_executable(BigMathTest ${BIG_MATH_TEST_SOURCES})

target_link_libraries(BigMathTest PRIVATE
    BigMathLibrary
)

target_include_directories(BigMathTest PRIVATE
    "Source"
    ${PROJECT_SOURCE_DIR}/Library/Source
)