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

add_executable(polynomial_AST_test)
target_sources(polynomial_AST_test
  PRIVATE
  polynomial_AST_test.cpp
)
target_link_libraries(polynomial_AST_test PRIVATE
  GTest::gtest_main
  ${CMAKE_SOURCE_DIR}/polynomial_AST.cpp
)

include(GoogleTest)
gtest_discover_tests(polynomial_AST_test)
