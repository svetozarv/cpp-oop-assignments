cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project (
    polynomial_AST
    VERSION 1
    LANGUAGES CXX
)
add_compile_options(-Wall -Wpedantic -Werror -std=c++23)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY      https://github.com/google/googletest.git
  GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

add_library(polynomial_core
    src/lexer.cpp
    src/parser.cpp
    src/polynomial_AST.cpp
)
target_include_directories(polynomial_core PUBLIC include)

add_executable(lexer_test tests/lexer_test.cpp)
target_link_libraries(lexer_test PRIVATE polynomial_core GTest::gtest_main)

add_executable(parser_test tests/parser_test.cpp)
target_link_libraries(parser_test PRIVATE polynomial_core GTest::gtest_main)

add_executable(polynomial_AST_test tests/polynomial_AST_test.cpp)
target_link_libraries(polynomial_AST_test PRIVATE polynomial_core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lexer_test)
gtest_discover_tests(parser_test)
gtest_discover_tests(polynomial_AST_test)
