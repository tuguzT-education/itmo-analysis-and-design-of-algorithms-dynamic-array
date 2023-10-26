FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
if (WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif ()
FetchContent_MakeAvailable(googletest)

include(GoogleTest)


macro(add_google_test TEST_NAME TEST_ARGS)
    add_executable(${TEST_NAME} ${TEST_ARGS})
    target_link_libraries(${TEST_NAME} GTest::gtest_main lab2)
    gtest_discover_tests(${TEST_NAME})
endmacro()

add_google_test(empty_array_test EmptyArrayTest.cpp)
add_google_test(insert_test InsertTest.cpp)
add_google_test(remove_test RemoveTest.cpp)
add_google_test(reserve_test ReserveTest.cpp)
add_google_test(iteration_test IterationTest.cpp)
add_google_test(copy_move_semantics_test CopyMoveSemanticsTest.cpp)
