// Copyright 2024 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_point/point.h"

#define EPSILON 0.000001

TEST(TestPointLib, can_create_copy_constructor) {
    Point point(3, 4);
    ASSERT_NO_THROW(Point(point));
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