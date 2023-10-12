#include <gtest/gtest.h>
#include <Lab2/Array.hpp>

GTEST_TEST(EmptyArrayTest, NullData) {
    lab2::Array<int> array{nullptr};
    GTEST_ASSERT_EQ(array.data(), nullptr);
}

GTEST_TEST(EmptyArrayTest, ZeroSize) {
    lab2::Array<int> array{nullptr};
    GTEST_ASSERT_EQ(array.size(), 0);
}

GTEST_TEST(EmptyArrayTest, ZeroCapacity) {
    lab2::Array<int> array{nullptr};
    GTEST_ASSERT_EQ(array.capacity(), 0);
}
