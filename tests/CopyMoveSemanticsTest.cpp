#include <gtest/gtest.h>
#include <Lab2/Array.hpp>

GTEST_TEST(CopyMoveSemanticsTest, CopyableOnly) {
    struct CopyableOnly {
        int value;

        explicit CopyableOnly(int value) : value{value} {}

        CopyableOnly(const CopyableOnly &other) = default;
        CopyableOnly &operator=(const CopyableOnly &other) = default;

        CopyableOnly(CopyableOnly &&other) = delete;
        CopyableOnly &operator=(CopyableOnly &&other) = delete;

        bool operator==(const CopyableOnly &other) const = default;
    };

    lab2::Array<CopyableOnly> array;
    array.emplace(1);
    GTEST_ASSERT_EQ(array[0], CopyableOnly{1});
    array.insert(0, CopyableOnly{2});
    GTEST_ASSERT_EQ(array[0], CopyableOnly{2});

    array.remove(0);
    array.remove(0);
    GTEST_ASSERT_EQ(array.size(), 0);
}

GTEST_TEST(CopyMoveSemanticsTest, MovableOnly) {
    struct MovableOnly {
        int value;

        explicit MovableOnly(int value) : value{value} {}

        MovableOnly(const MovableOnly &other) = delete;
        MovableOnly &operator=(const MovableOnly &other) = delete;

        MovableOnly(MovableOnly &&other) = default;
        MovableOnly &operator=(MovableOnly &&other) = default;

        bool operator==(const MovableOnly &other) const = default;
    };

    lab2::Array<MovableOnly> array;
    array.emplace(MovableOnly{1});
    GTEST_ASSERT_EQ(array[0], MovableOnly{1});
    array.emplace(decltype(array)::SizeType{0}, MovableOnly{2});
    GTEST_ASSERT_EQ(array[0], MovableOnly{2});

    array.remove(0);
    array.remove(0);
    GTEST_ASSERT_EQ(array.size(), 0);
}
