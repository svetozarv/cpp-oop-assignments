cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project (
    chemical_element
    VERSION 1
    LANGUAGES CXX
)
add_compile_options(-Wall -Wpedantic -Werror -std=c++23)

add_subdirectory("tests")
# add_subdirectory("src")
add_executable(chemical_element main.cpp src/ChemicalElement.cpp)
