#include <gtest/gtest.h>
#include <Lab2/Array.hpp>

static inline lab2::Array<int> Make5() {
    lab2::Array<int> array;
    array.insert(1);
    array.insert(2);
    array.insert(3);
    array.insert(4);
    array.insert(5);
    return array;
}

using Iterator = lab2::Array<int>::Iterator;

GTEST_TEST(IterationTest, Begin) {
    lab2::Array array = Make5();
    GTEST_ASSERT_EQ(array.size(), 5);

    Iterator iterator = array.begin();
    GTEST_ASSERT_FALSE(iterator.isReversed());
    GTEST_ASSERT_EQ(*iterator, 1);
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator++;
    GTEST_ASSERT_EQ(*iterator, 2);
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(*iterator, 3);
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(*iterator, 4);
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(*iterator, 5);
    GTEST_ASSERT_FALSE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(iterator, array.end());
}

GTEST_TEST(IterationTest, End) {
    lab2::Array array = Make5();
    GTEST_ASSERT_EQ(array.size(), 5);

    Iterator iterator = array.end();
    GTEST_ASSERT_FALSE(iterator.hasNext());
    GTEST_ASSERT_NE(iterator, array.begin());
    GTEST_ASSERT_EQ(iterator, ++(++(++(++(++array.begin())))));
}

GTEST_TEST(IterationTest, RBegin) {
    lab2::Array array = Make5();
    GTEST_ASSERT_EQ(array.size(), 5);

    Iterator iterator = array.rbegin();
    GTEST_ASSERT_TRUE(iterator.isReversed());
    GTEST_ASSERT_EQ(*iterator, 5);
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator++;
    GTEST_ASSERT_EQ(*iterator, 4);
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(*iterator, 3);
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(*iterator, 2);
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(*iterator, 1);
    GTEST_ASSERT_FALSE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(iterator, array.rend());
}

GTEST_TEST(IterationTest, REnd) {
    lab2::Array array = Make5();
    GTEST_ASSERT_EQ(array.size(), 5);

    Iterator iterator = array.rend();
    GTEST_ASSERT_FALSE(iterator.hasNext());
    GTEST_ASSERT_NE(iterator, array.rbegin());
    GTEST_ASSERT_EQ(iterator, ++(++(++(++(++array.rbegin())))));
}
