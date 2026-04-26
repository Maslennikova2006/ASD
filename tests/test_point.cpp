// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_point/point.h"

TEST(TestPointLib, can_create_copy_constructor) {
    Point point(3, 4);
    ASSERT_NO_THROW(Point(point));
}
TEST(TestPointLib, can_create_initialization_constructor) {
    ASSERT_NO_THROW(Point(3, 5));
}
TEST(TestPointLib, can_create) {
    ASSERT_NO_THROW(Point());
}
TEST(TestPointLib, check_setter_and_getter_x) {
    Point point;
    point.set_x(4);
    EXPECT_EQ(4, point.get_x());
}
TEST(TestPointLib, check_setter_and_getter_y) {
    Point point;
    point.set_y(8);
    EXPECT_EQ(8, point.get_y());
}
TEST(TestPointLib, check_the_equality) {
    Point point1(2, 3);
    Point point2(2, 3);
    EXPECT_TRUE(point1 == point2);
}
TEST(TestPointLib, check_the_inequality) {
    Point point1(2, 3);
    Point point2(2, 5);
    EXPECT_FALSE(point1 == point2);
}