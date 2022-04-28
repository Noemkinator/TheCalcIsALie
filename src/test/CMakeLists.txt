cmake_minimum_required(VERSION 3.5)

project(CALC_TEST)
set(CMAKE_BUILD_TYPE Release)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/a1cc8c55195661a58ad60c3bb062a0b9c302710d.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
     calc_test
    ../tdd_tests.cpp
    ../calc.cpp
)
target_link_libraries(
    calc_test
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(calc_test)
