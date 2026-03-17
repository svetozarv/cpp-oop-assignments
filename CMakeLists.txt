cmake_minimum_required(VERSION 3.28.3)

project (
    chemical_element
    VERSION 1
    LANGUAGES CXX
)

include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY      https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

add_executable(chemical_element main.cpp src/ChemicalElement.cpp)
add_executable(chemical_element_test tests/ChemicalElementUnitTest.cpp src/ChemicalElement.cpp)
target_link_libraries(chemical_element_test GTest::gtest_main)
