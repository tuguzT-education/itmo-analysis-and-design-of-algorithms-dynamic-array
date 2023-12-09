#include <gtest/gtest.h>
#include <Lab2/Array.hpp>

#include <string>

static inline lab2::Array<int> Make5() {
    lab2::Array<int> array;
    array.insert(1);
    array.insert(2);
    array.insert(3);
    array.insert(4);
    array.insert(5);
    return array;
}

static inline lab2::Array<std::string> Make5_Strings() {
    lab2::Array<std::string> array;
    array.emplace("1");
    array.emplace("2");
    array.emplace("3");
    array.emplace("4");
    array.emplace("5");
    return array;
}

GTEST_TEST(IterationTest, Begin) {
    lab2::Array array = Make5();
    GTEST_ASSERT_EQ(array.size(), 5);

    using Iterator = decltype(array)::Iterator;

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

GTEST_TEST(IterationTest, BeginStrings) {
    lab2::Array array = Make5_Strings();
    GTEST_ASSERT_EQ(array.size(), 5);

    using Iterator = decltype(array)::Iterator;

    Iterator iterator = array.begin();
    GTEST_ASSERT_FALSE(iterator.isReversed());
    GTEST_ASSERT_EQ(*iterator, "1");
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator++;
    GTEST_ASSERT_EQ(*iterator, "2");
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(*iterator, "3");
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(*iterator, "4");
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(*iterator, "5");
    GTEST_ASSERT_FALSE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(iterator, array.end());
}

GTEST_TEST(IterationTest, End) {
    lab2::Array array = Make5();
    GTEST_ASSERT_EQ(array.size(), 5);

    using Iterator = decltype(array)::Iterator;

    Iterator iterator = array.end();
    GTEST_ASSERT_FALSE(iterator.hasNext());
    GTEST_ASSERT_NE(iterator, array.begin());
    GTEST_ASSERT_EQ(iterator, ++(++(++(++(++array.begin())))));
}

GTEST_TEST(IterationTest, EndStrings) {
    lab2::Array array = Make5_Strings();
    GTEST_ASSERT_EQ(array.size(), 5);

    using Iterator = decltype(array)::Iterator;

    Iterator iterator = array.end();
    GTEST_ASSERT_FALSE(iterator.hasNext());
    GTEST_ASSERT_NE(iterator, array.begin());
    GTEST_ASSERT_EQ(iterator, ++(++(++(++(++array.begin())))));
}

GTEST_TEST(IterationTest, RBegin) {
    lab2::Array array = Make5();
    GTEST_ASSERT_EQ(array.size(), 5);

    using Iterator = decltype(array)::Iterator;

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

GTEST_TEST(IterationTest, RBeginStrings) {
    lab2::Array array = Make5_Strings();
    GTEST_ASSERT_EQ(array.size(), 5);

    using Iterator = decltype(array)::Iterator;

    Iterator iterator = array.rbegin();
    GTEST_ASSERT_TRUE(iterator.isReversed());
    GTEST_ASSERT_EQ(*iterator, "5");
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator++;
    GTEST_ASSERT_EQ(*iterator, "4");
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(*iterator, "3");
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(*iterator, "2");
    GTEST_ASSERT_TRUE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(*iterator, "1");
    GTEST_ASSERT_FALSE(iterator.hasNext());

    iterator.next();
    GTEST_ASSERT_EQ(iterator, array.rend());
}

GTEST_TEST(IterationTest, REnd) {
    lab2::Array array = Make5();
    GTEST_ASSERT_EQ(array.size(), 5);

    using Iterator = decltype(array)::Iterator;

    Iterator iterator = array.rend();
    GTEST_ASSERT_FALSE(iterator.hasNext());
    GTEST_ASSERT_NE(iterator, array.rbegin());
    GTEST_ASSERT_EQ(iterator, ++(++(++(++(++array.rbegin())))));
}

GTEST_TEST(IterationTest, REndStrings) {
    lab2::Array array = Make5_Strings();
    GTEST_ASSERT_EQ(array.size(), 5);

    using Iterator = decltype(array)::Iterator;

    Iterator iterator = array.rend();
    GTEST_ASSERT_FALSE(iterator.hasNext());
    GTEST_ASSERT_NE(iterator, array.rbegin());
    GTEST_ASSERT_EQ(iterator, ++(++(++(++(++array.rbegin())))));
}
