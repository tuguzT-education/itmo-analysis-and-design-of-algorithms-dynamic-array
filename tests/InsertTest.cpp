#include <gtest/gtest.h>
#include <Lab2/Array.hpp>

#include <string>

GTEST_TEST(InsertTest, InsertOne) {
    lab2::Array<int> array;
    GTEST_ASSERT_EQ(array.size(), 0);

    array.insert(42);
    GTEST_ASSERT_EQ(array.size(), 1);
    GTEST_ASSERT_EQ(array[0], 42);
}

GTEST_TEST(InsertTest, InsertOneStrings) {
    lab2::Array<std::string> array;
    GTEST_ASSERT_EQ(array.size(), 0);

    array.emplace("42");
    GTEST_ASSERT_EQ(array.size(), 1);
    GTEST_ASSERT_EQ(array[0], "42");
}

GTEST_TEST(InsertTest, InsertTwo) {
    lab2::Array<int> array;
    GTEST_ASSERT_EQ(array.size(), 0);

    array.insert(42);
    array.insert(2023);
    GTEST_ASSERT_EQ(array.size(), 2);
    GTEST_ASSERT_EQ(array[0], 42);
    GTEST_ASSERT_EQ(array[1], 2023);
}

GTEST_TEST(InsertTest, InsertTwoStrings) {
    lab2::Array<std::string> array;
    GTEST_ASSERT_EQ(array.size(), 0);

    array.emplace("42");
    array.emplace("2023");
    GTEST_ASSERT_EQ(array.size(), 2);
    GTEST_ASSERT_EQ(array[0], "42");
    GTEST_ASSERT_EQ(array[1], "2023");
}

GTEST_TEST(InsertTest, FillCapacity) {
    lab2::Array<int> array;
    GTEST_ASSERT_EQ(array.size(), 0);

    while (array.size() < array.capacity()) {
        array.insert(42);
    }
    GTEST_ASSERT_EQ(array.size(), array.capacity());
    GTEST_ASSERT_EQ(array[array.size() - 1], 42);
}

GTEST_TEST(InsertTest, FillCapacityStrings) {
    lab2::Array<std::string> array;
    GTEST_ASSERT_EQ(array.size(), 0);

    while (array.size() < array.capacity()) {
        array.emplace("42");
    }
    GTEST_ASSERT_EQ(array.size(), array.capacity());
    GTEST_ASSERT_EQ(array[array.size() - 1], "42");
}

GTEST_TEST(InsertTest, AtTheBeginning) {
    lab2::Array<int> array;
    GTEST_ASSERT_EQ(array.size(), 0);

    array.insert(0, 1);
    GTEST_ASSERT_EQ(array[0], 1);

    array.insert(0, 2);
    GTEST_ASSERT_EQ(array[0], 2);
    GTEST_ASSERT_EQ(array[1], 1);

    array.insert(0, 3);
    GTEST_ASSERT_EQ(array[0], 3);
    GTEST_ASSERT_EQ(array[1], 2);
    GTEST_ASSERT_EQ(array[2], 1);
}

GTEST_TEST(InsertTest, AtTheBeginningStrings) {
    lab2::Array<std::string> array;
    GTEST_ASSERT_EQ(array.size(), 0);

    using Index = decltype(array)::SizeType;
    array.emplace(Index{0}, "1");
    GTEST_ASSERT_EQ(array[0], "1");

    array.emplace(Index{0}, "2");
    GTEST_ASSERT_EQ(array[0], "2");
    GTEST_ASSERT_EQ(array[1], "1");

    array.insert(Index{0}, "3");
    GTEST_ASSERT_EQ(array[0], "3");
    GTEST_ASSERT_EQ(array[1], "2");
    GTEST_ASSERT_EQ(array[2], "1");
}

GTEST_TEST(InsertTest, AtTheMiddle) {
    lab2::Array<int> array;
    array.insert(1);
    array.insert(2);
    array.insert(3);
    GTEST_ASSERT_EQ(array.size(), 3);

    array.insert(1, 0);
    GTEST_ASSERT_EQ(array[0], 1);
    GTEST_ASSERT_EQ(array[1], 0);
    GTEST_ASSERT_EQ(array[2], 2);
    GTEST_ASSERT_EQ(array[3], 3);

    array.insert(2, 0);
    GTEST_ASSERT_EQ(array[0], 1);
    GTEST_ASSERT_EQ(array[1], 0);
    GTEST_ASSERT_EQ(array[2], 0);
    GTEST_ASSERT_EQ(array[3], 2);
    GTEST_ASSERT_EQ(array[4], 3);
}

GTEST_TEST(InsertTest, AtTheMiddleStrings) {
    lab2::Array<std::string> array;
    array.emplace("1");
    array.emplace("2");
    array.emplace("3");
    GTEST_ASSERT_EQ(array.size(), 3);

    using Index = decltype(array)::SizeType;
    array.emplace(Index{1}, "0");
    GTEST_ASSERT_EQ(array[0], "1");
    GTEST_ASSERT_EQ(array[1], "0");
    GTEST_ASSERT_EQ(array[2], "2");
    GTEST_ASSERT_EQ(array[3], "3");

    array.emplace(Index{2}, "0");
    GTEST_ASSERT_EQ(array[0], "1");
    GTEST_ASSERT_EQ(array[1], "0");
    GTEST_ASSERT_EQ(array[2], "0");
    GTEST_ASSERT_EQ(array[3], "2");
    GTEST_ASSERT_EQ(array[4], "3");
}
