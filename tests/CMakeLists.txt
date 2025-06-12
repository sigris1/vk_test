cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 23)
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        tests
        tests.cpp
        AuxiliaryFunctions.cpp
        AuxiliaryFunctions.h
)

target_link_libraries(
        tests
        metrics_controller
        GTest::gtest_main
)

target_include_directories(tests PUBLIC "${PROJECT_SOURCE_DIR}/lib")

include(GoogleTest)

gtest_discover_tests(tests)