cmake_minimum_required(VERSION 3.26)

project(Lab2 LANGUAGES CXX)

include(FetchContent)

add_subdirectory(src)
add_subdirectory(apps)

option(ENABLE_TESTING "Build the tests" ON)
if (ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif ()
