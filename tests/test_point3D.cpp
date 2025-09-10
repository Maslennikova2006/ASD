// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_point3D/point3D.h"

TEST(TestPoint3DLib, can_create_copy_constructor) {
    Point3D point(3, 4, 5);
    ASSERT_NO_THROW(Point3D(point));
}
TEST(TestPoint3DLib, can_create_initialization_constructor) {
    ASSERT_NO_THROW(Point3D(3, 5, 7));
}
TEST(TestPoint3DLib, can_create) {
    ASSERT_NO_THROW(Point3D());
}
TEST(TestPoint3DLib, check_setter_and_getter_x) {
    Point3D point;
    point.set_x(4);
    int actual_result = point.get_x();
    int expected_result = 4;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestPoint3DLib, check_setter_and_getter_y) {
    Point3D point;
    point.set_y(8);
    int actual_result = point.get_y();
    int expected_result = 8;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestPoint3DLib, check_setter_and_getter_z) {
    Point3D point;
    point.set_z(3);
    int actual_result = point.get_z();
    int expected_result = 3;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestPoint3DLib, check_the_equality) {
    Point3D point1(2, 3, 8);
    Point3D point2(2, 3, 8);
    bool actual_result = (point1 == point2);
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestPoint3DLib, check_the_inequality) {
    Point3D point1(2, 3, 4);
    Point3D point2(2, 5, 4);
    bool actual_result = (point1 == point2);
    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}
