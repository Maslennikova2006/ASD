// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_sphere/sphere.h"

TEST(TestSphereLib, can_create_constructor) {
    ASSERT_NO_THROW(Sphere(4, 2, 3, 8));
}
TEST(TestSphereLib, can_create_copy_constructor) {
    Sphere sphere(1, 2, 3, 4);
    ASSERT_NO_THROW(Sphere(sphere));
}
TEST(TestSphereLib, throw_when_the_radius_is_less_than_zero) {
    ASSERT_ANY_THROW(Sphere(5, 2, 3, -4));
}
TEST(TestSphereLib, can_create_initiazation_constructor) {
    Point3D point(2, 3, 1);
    ASSERT_NO_THROW(Sphere(point, 5));
}
TEST(TestSphereLib, can_create) {
    ASSERT_NO_THROW(Sphere());
}
TEST(TestSphereLib, check_setter_and_getter_rad) {
    Sphere sphere;
    sphere.set_rad(4.76);
    float actual_result = sphere.get_rad();
    float expected_result = 4.76;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestSphereLib, check_setter_and_getter_point) {
    Sphere sphere;
    Point3D point(4, 4, 6);
    sphere.set_point3D(point);
    Point3D actual_result = sphere.get_point3D();
    Point3D expected_result(4, 4, 6);
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestSphereLib, check_calculate_distance) {
    Sphere circle(5, 3, 8, 4);
    Point3D point(2, 3, 8);
    float actual_result = circle.calculate_distance(Sphere(point, 9));
    float expected_result = 3.0;
    EXPECT_EQ(expected_result, actual_result);
}