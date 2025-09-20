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
    sphere.set_rad(5);
    EXPECT_EQ(5, sphere.get_rad());
}
TEST(TestSphereLib, check_setter_and_getter_point) {
    Sphere sphere;
    Point3D point(4, 4, 6);
    sphere.set_point3D(point);
    EXPECT_EQ(point, sphere.get_point3D());
}
TEST(TestSphereLib, check_calculate_distance) {
    Sphere circle(5, 3, 8, 4);
    Point3D point(2, 3, 8);
    EXPECT_EQ(3.0, circle.calculate_distance(Sphere(point, 9)));
}