cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project (
    warehouse_analyzer
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

add_executable(warehouse_analyzer_test)
target_sources(warehouse_analyzer_test
  PRIVATE
  ${CMAKE_SOURCE_DIR}/warehouse_analyzer_test.cpp
  ${CMAKE_SOURCE_DIR}/src/warehouse_analyzer.cpp
  ${CMAKE_SOURCE_DIR}/src/warehouse.cpp
  ${CMAKE_SOURCE_DIR}/src/product.cpp
)
target_link_libraries(warehouse_analyzer_test PRIVATE
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(warehouse_analyzer_test)
