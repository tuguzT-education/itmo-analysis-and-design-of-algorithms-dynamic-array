#include <gtest/gtest.h>
#include <Lab2/Array.hpp>

#include <string>

GTEST_TEST(ReserveTest, ReserveNothing) {
    lab2::Array<int> array;
    array.insert(1);
    array.insert(2);
    array.insert(3);
    array.insert(4);
    array.insert(5);
    GTEST_ASSERT_EQ(array.size(), 5);

    const auto old_capacity = array.capacity();
    array.reserve(old_capacity - 1);
    GTEST_ASSERT_EQ(array.size(), 5);
    GTEST_ASSERT_EQ(array.capacity(), old_capacity);
    GTEST_ASSERT_EQ(array[0], 1);
    GTEST_ASSERT_EQ(array[1], 2);
    GTEST_ASSERT_EQ(array[2], 3);
    GTEST_ASSERT_EQ(array[3], 4);
    GTEST_ASSERT_EQ(array[4], 5);
}

GTEST_TEST(ReserveTest, ReserveNothingStrings) {
    lab2::Array<std::string> array;
    array.emplace("1");
    array.emplace("2");
    array.emplace("3");
    array.emplace("4");
    array.emplace("5");
    GTEST_ASSERT_EQ(array.size(), 5);

    const auto old_capacity = array.capacity();
    array.reserve(old_capacity - 1);
    GTEST_ASSERT_EQ(array.size(), 5);
    GTEST_ASSERT_EQ(array.capacity(), old_capacity);
    GTEST_ASSERT_EQ(array[0], "1");
    GTEST_ASSERT_EQ(array[1], "2");
    GTEST_ASSERT_EQ(array[2], "3");
    GTEST_ASSERT_EQ(array[3], "4");
    GTEST_ASSERT_EQ(array[4], "5");
}

GTEST_TEST(ReserveTest, ReserveMore) {
    lab2::Array<int> array;
    array.insert(1);
    array.insert(2);
    array.insert(3);
    array.insert(4);
    array.insert(5);
    GTEST_ASSERT_EQ(array.size(), 5);

    const auto old_capacity = array.capacity();
    array.reserve(old_capacity + 1);
    GTEST_ASSERT_EQ(array.size(), 5);
    GTEST_ASSERT_EQ(array.capacity(), old_capacity + 1);
    GTEST_ASSERT_EQ(array[0], 1);
    GTEST_ASSERT_EQ(array[1], 2);
    GTEST_ASSERT_EQ(array[2], 3);
    GTEST_ASSERT_EQ(array[3], 4);
    GTEST_ASSERT_EQ(array[4], 5);
}

GTEST_TEST(ReserveTest, ReserveMoreStrings) {
    lab2::Array<std::string> array;
    array.emplace("1");
    array.emplace("2");
    array.emplace("3");
    array.emplace("4");
    array.emplace("5");
    GTEST_ASSERT_EQ(array.size(), 5);

    const auto old_capacity = array.capacity();
    array.reserve(old_capacity + 1);
    GTEST_ASSERT_EQ(array.size(), 5);
    GTEST_ASSERT_EQ(array.capacity(), old_capacity + 1);
    GTEST_ASSERT_EQ(array[0], "1");
    GTEST_ASSERT_EQ(array[1], "2");
    GTEST_ASSERT_EQ(array[2], "3");
    GTEST_ASSERT_EQ(array[3], "4");
    GTEST_ASSERT_EQ(array[4], "5");
}
