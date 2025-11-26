// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_dsu/dsu.h"

TEST(TestDsuLib, can_create_constructor) {
    ASSERT_NO_THROW(Dsu(8));
}
TEST(TestDsuLib, check_find) {
    Dsu dsu(8);

    EXPECT_EQ(dsu.find(2), 2);
    EXPECT_EQ(dsu.find(3), 3);
    EXPECT_EQ(dsu.find(5), 5);

    dsu.union_set(2, 3);
    dsu.union_set(3, 5);
    EXPECT_EQ(dsu.find(2), 2);
    EXPECT_EQ(dsu.find(3), 2);
    EXPECT_EQ(dsu.find(5), 2);
}
TEST(TestDsuLib, check_union_set_when_the_first_rank_is_higher_than_the_second) {
    Dsu dsu(8);

    dsu.union_set(2, 3);
    dsu.union_set(3, 5);
    EXPECT_EQ(dsu.find(2), 2);
    EXPECT_EQ(dsu.find(3), 2);
    EXPECT_EQ(dsu.find(5), 2);
}
TEST(TestDsuLib, check_union_set_when_the_first_rank_is_lower_than_the_second) {
    Dsu dsu(8);

    dsu.union_set(7, 1);

    dsu.union_set(4, 6);
    dsu.union_set(6, 7);
    dsu.union_set(2, 3);
    dsu.union_set(2, 6);

    dsu.union_set(1, 3);
    EXPECT_EQ(dsu.find(7), 2);
    EXPECT_EQ(dsu.find(1), 2);
    EXPECT_EQ(dsu.find(4), 2);
    EXPECT_EQ(dsu.find(3), 2);
    EXPECT_EQ(dsu.find(6), 2);
}
TEST(TestDsuLib, check_union_set_when_the_ranks_are_equal) {
    Dsu dsu(8);

    dsu.union_set(2, 3);

    dsu.union_set(4, 6);

    dsu.union_set(3, 6);
    EXPECT_EQ(dsu.find(3), 2);
    EXPECT_EQ(dsu.find(6), 2);
    EXPECT_EQ(dsu.find(4), 2);
    EXPECT_EQ(dsu.find(2), 2);
}
TEST(TestDsuLib, ñheck_union_with_yourself) {
    Dsu dsu(8);
    dsu.union_set(3, 3);
    EXPECT_EQ(dsu.find(3), 3);
}
TEST(TestDsuLib, check_throw_in_union_when_invalid_value) {
    Dsu dsu(8);

    ASSERT_ANY_THROW(dsu.union_set(2, -5));
    ASSERT_ANY_THROW(dsu.union_set(8, 5));
}
TEST(TestDsuLib, check_throw_in_find_when_invalid_value) {
    Dsu dsu(8);

    ASSERT_ANY_THROW(dsu.find(-5));
    ASSERT_ANY_THROW(dsu.find(9));
}
TEST(TestDsuLib, check_union_different_sets) {
    Dsu dsu(8);

    dsu.union_set(1, 5);
    dsu.union_set(2, 3);
    EXPECT_EQ(dsu.find(5), 1);
    EXPECT_EQ(dsu.find(3), 2);

    dsu.union_set(1, 2);
    EXPECT_EQ(dsu.find(5), dsu.find(2));
}
TEST(TestDsuLib, check_path_compression) {
    Dsu dsu(8);

    dsu.union_set(0, 1);
    dsu.union_set(1, 2);
    dsu.union_set(2, 3);
    dsu.union_set(3, 4);

    EXPECT_EQ(dsu.find(4), 0);
}
TEST(TestDsuLib, check_path_compression_and_rank_reductions) {
    Dsu dsu(8);

    dsu.union_set(1, 2);
    dsu.union_set(3, 4);
    dsu.union_set(1, 4);

    dsu.union_set(5, 6);

    dsu.union_set(6, 2);

    EXPECT_EQ(dsu.find(4), 5);
}
