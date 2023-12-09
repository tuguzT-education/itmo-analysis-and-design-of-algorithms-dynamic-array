#include <gtest/gtest.h>
#include <Lab2/Array.hpp>

#include <string>

GTEST_TEST(RemoveTest, RemoveFirst) {
    lab2::Array<int> array;
    array.insert(1);
    GTEST_ASSERT_EQ(array.size(), 1);

    array.remove(0);
    GTEST_ASSERT_EQ(array.size(), 0);
}

GTEST_TEST(RemoveTest, RemoveFirstStrings) {
    lab2::Array<std::string> array;
    array.emplace("1");
    GTEST_ASSERT_EQ(array.size(), 1);

    array.remove(0);
    GTEST_ASSERT_EQ(array.size(), 0);
}

GTEST_TEST(RemoveTest, RemoveLast) {
    lab2::Array<int> array;
    array.insert(1);
    array.insert(2);
    GTEST_ASSERT_EQ(array.size(), 2);

    array.remove(1);
    GTEST_ASSERT_EQ(array.size(), 1);
    GTEST_ASSERT_EQ(array[0], 1);
}

GTEST_TEST(RemoveTest, RemoveLastStrings) {
    lab2::Array<std::string> array;
    array.emplace("1");
    array.emplace("2");
    GTEST_ASSERT_EQ(array.size(), 2);

    array.remove(1);
    GTEST_ASSERT_EQ(array.size(), 1);
    GTEST_ASSERT_EQ(array[0], "1");
}

GTEST_TEST(RemoveTest, RemoveMiddle) {
    lab2::Array<int> array;
    array.insert(1);
    array.insert(2);
    array.insert(3);
    array.insert(4);
    array.insert(5);
    GTEST_ASSERT_EQ(array.size(), 5);

    array.remove(1);
    GTEST_ASSERT_EQ(array.size(), 4);
    GTEST_ASSERT_EQ(array[0], 1);
    GTEST_ASSERT_EQ(array[1], 3);
    GTEST_ASSERT_EQ(array[2], 4);
    GTEST_ASSERT_EQ(array[3], 5);

    array.remove(2);
    GTEST_ASSERT_EQ(array.size(), 3);
    GTEST_ASSERT_EQ(array[0], 1);
    GTEST_ASSERT_EQ(array[1], 3);
    GTEST_ASSERT_EQ(array[2], 5);
}

GTEST_TEST(RemoveTest, RemoveMiddleStrings) {
    lab2::Array<std::string> array;
    array.emplace("1");
    array.emplace("2");
    array.emplace("3");
    array.emplace("4");
    array.emplace("5");
    GTEST_ASSERT_EQ(array.size(), 5);

    array.remove(1);
    GTEST_ASSERT_EQ(array.size(), 4);
    GTEST_ASSERT_EQ(array[0], "1");
    GTEST_ASSERT_EQ(array[1], "3");
    GTEST_ASSERT_EQ(array[2], "4");
    GTEST_ASSERT_EQ(array[3], "5");

    array.remove(2);
    GTEST_ASSERT_EQ(array.size(), 3);
    GTEST_ASSERT_EQ(array[0], "1");
    GTEST_ASSERT_EQ(array[1], "3");
    GTEST_ASSERT_EQ(array[2], "5");
}
