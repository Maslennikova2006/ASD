// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_circle/circle.h"

TEST(TestCircleLib, can_create_constructor) {
    ASSERT_NO_THROW(Circle(2, 3, 8));
}
TEST(TestCircleLib, can_create_copy_constructor) {
    Circle circle( 2, 3, 4);
    ASSERT_NO_THROW(Circle(circle));
}
TEST(TestCircleLib, throw_when_the_radius_is_less_than_zero) {
    ASSERT_ANY_THROW(Circle(2, 3, -4));
}
TEST(TestCircleLib, can_create_initiazation_constructor) {
    Point point(2, 3);
    ASSERT_NO_THROW(Circle(point, 5));
}
TEST(TestCircleLib, can_create) {
    ASSERT_NO_THROW(Circle());
}
TEST(TestCircleLib, check_setter_and_getter_rad) {
    Circle circle(1, 2, 3);
    circle.set_rad(4);
    EXPECT_EQ(4, circle.get_rad());
}
TEST(TestCircleLib, check_setter_and_getter_point) {
    Circle circle;
    Point point(4, 4);
    circle.set_point(point);
    EXPECT_EQ(point, circle.get_point());
}
TEST(TestCircleLib, check_calculate_distance) {
    Circle circle(5, 3, 8);
    EXPECT_EQ(3.0, circle.calculate_distance(Circle(2, 3, 9)));
}