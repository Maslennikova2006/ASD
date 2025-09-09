// Copyright 2024 Mary Maslennikova

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
    int actual_result = point.get_x();
    int expected_result = 4;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestPointLib, check_setter_and_getter_y) {
    Point point;
    point.set_y(8);
    int actual_result = point.get_y();
    int expected_result = 8;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestPointLib, check_the_equality) {
    Point point1(2, 3);
    Point point2(2, 3);
    bool actual_result = (point1 == point2);
    EXPECT_EQ(true, actual_result);
}
TEST(TestPointLib, check_the_inequality) {
    Point point1(2, 3);
    Point point2(2, 5);
    bool actual_result = (point1 == point2);
    EXPECT_EQ(false, actual_result);
}