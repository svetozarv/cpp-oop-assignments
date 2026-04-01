cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project (
    polynomial
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

add_executable(polynomial_test)
target_sources(polynomial_test
  PRIVATE
  polynomial_tests.cpp
)
target_link_libraries(polynomial_test PRIVATE
  GTest::gtest_main
  ${CMAKE_SOURCE_DIR}/polynomial.cpp
)

include(GoogleTest)
gtest_discover_tests(polynomial_test)
