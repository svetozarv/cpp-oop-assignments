include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY      https://github.com/google/googletest.git
  GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

add_executable(chemical_element_test)
target_sources(chemical_element_test
  PRIVATE
  ChemicalElementUnitTest.cpp
)
target_link_libraries(chemical_element_test PRIVATE
  GTest::gtest_main
  ${CMAKE_SOURCE_DIR}/src/ChemicalElement.cpp
)

include(GoogleTest)
gtest_discover_tests(chemical_element_test)
