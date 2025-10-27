// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"
#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"

TEST(TestAlgorithmsLib, check_inside) {
    Point point1(5, 8);
    Circle c1(point1, 9);
    Circle c2(3, 8, 6);

    EXPECT_EQ(inside, check_position(c1, c2));
}
TEST(TestAlgorithmsLib, check_no_point) {
    Point point2(0, 0);
    Circle c3(point2, 3);
    Circle c4(15, 8, 2);

    EXPECT_EQ(no_point, check_position(c3, c4));
}
TEST(TestAlgorithmsLib, check_touch) {
    Point point3(0, 0);
    Circle c5(point3, 3);
    Circle c6(8, 0, 5);

    EXPECT_EQ(touch, check_position(c5, c6));
}
TEST(TestAlgorithmsLib, check_intersect) {
    Circle c7(0, 0, 5);
    Circle c8(3, 0, 4);

    EXPECT_EQ(intersect, check_position(c7, c8));
}
TEST(TestAlgorithmsLib, check_match) {
    Point point5(-2, 2);
    Circle c9(point5, 3);
    Circle c10(-2, 2, 3);

    EXPECT_EQ(match, check_position(c9, c10));
}
TEST(TestAlgorithmsLib, check_inside_sphere) {
    Point point(0, 0);
    Sphere s7(point, 0, 3);
    Sphere s8(0, 1, 0, 1);

    EXPECT_EQ(inside, check_position(s7, s8));
}
TEST(TestAlgorithmsLib, check_no_point_sphere) {
    Point3D point2(-2, 2, 2);
    Sphere s3(point2, 3);
    Sphere s4(-5, 8, 7, 2);

    EXPECT_EQ(no_point, check_position(s3, s4));
}
TEST(TestAlgorithmsLib, check_touch_sphere) {
    Sphere s9(0, 0, 0, 2);
    Sphere s10(3, 0, 0, 1);

    EXPECT_EQ(touch, check_position(s9, s10));
}
TEST(TestAlgorithmsLib, check_intersect_sphere) {
    Point point3(0, 3);
    Sphere s5(point3, 5, 3);
    Sphere s6(0, 3, 4, 2);

    EXPECT_EQ(intersect, check_position(s5, s6));
}
TEST(TestAlgorithmsLib, check_match_sphere) {
    Point3D point1(-2, 2, 2);
    Sphere s1(point1, 3);
    Sphere s2(-2, 2, 2, 3);

    EXPECT_EQ(match, check_position(s1, s2));
}
TEST(TestAlgorithmsLib, check_brackets_1) {
    EXPECT_TRUE(check_brackets("((){})"));
}
TEST(TestAlgorithmsLib, check_brackets_2) {
    EXPECT_FALSE(check_brackets("()){)"));
}
TEST(TestAlgorithmsLib, check_brackets_3) {
    EXPECT_FALSE(check_brackets("(){)"));
}
TEST(TestAlgorithmsLib, check_brackets_4) {
    EXPECT_FALSE(check_brackets("((){}))"));
}
TEST(TestAlgorithmsLib, check_read_expression_1) {
    ASSERT_NO_THROW(read_expression("3 * (15 + (x + y) * (2*x - 7*y^2))"));
}
TEST(TestAlgorithmsLib, check_read_expression_2) {
    ASSERT_ANY_THROW(read_expression("3 * (15 + (x  y) * (2x - 7*y^2))"));
}
TEST(TestAlgorithmsLib, check_read_expression_3) {
    ASSERT_ANY_THROW(read_expression("3 * (15 + (x + y) * (2*x - 7*y^))"));
}
TEST(TestAlgorithmsLib, check_read_expression_4) {
    ASSERT_ANY_THROW(read_expression("((x + y) * (x - y)"));
}
TEST(TestAlgorithmsLib, check_read_expression_5) {
    ASSERT_ANY_THROW(read_expression("3 * (15 + (x + y) * (2*x - 7*^2))"));
}
TEST(TestAlgorithmsLib, check_read_expression_6) {
    ASSERT_ANY_THROW(read_expression("((x + y) * (x - y)))"));
}
TEST(TestAlgorithmsLib, check_read_expression_7) {
    ASSERT_ANY_THROW(read_expression("3 * (15 (x + y) * (2*x - 7*y^2))"));
}
TEST(TestAlgorithmsLib, check_read_expression_8) {
    ASSERT_ANY_THROW(read_expression("3 * (15 + (x + y)  (2*x - 7*y^2))"));
}
TEST(TestAlgorithmsLib, check_read_expression_9) {
    ASSERT_ANY_THROW(read_expression("(*(x + y) * (x - y))"));
}
TEST(TestAlgorithmsLib, check_read_expression_10) {
    ASSERT_ANY_THROW(read_expression("((x + y) * (x - y *))"));
}