// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include <iostream>
#include "../lib_mathvector/mathvector.h"

TEST(TestMathVectorLib, check_the_default_constructor) {
    MathVector<float> vec;
    EXPECT_EQ(static_cast <size_t>(0), vec.get_start_index());
}
TEST(TestMathVectorLib, check_the_initialization_constructor) {
    int array[5] = { 1, 2, 3, 4, 5 };
    MathVector<int> vec(5, array);
    EXPECT_EQ(static_cast <size_t>(5), vec.size());
    EXPECT_EQ(static_cast<size_t>(5), vec.capacity());
    EXPECT_EQ(static_cast<size_t>(0), vec.get_start_index());
}
TEST(TestMathVectorLib, check_the_initialization_constructor_with_start_index) {
    int array[5] = { 1, 2, 3, 4, 5 };
    MathVector<int> vec(5, array, 2);
    EXPECT_EQ(static_cast <size_t>(5), vec.size());
    EXPECT_EQ(static_cast<size_t>(5), vec.capacity());
    EXPECT_EQ(static_cast<size_t>(2), vec.get_start_index());
}
TEST(TestMathVectorLib, check_the_constructor_with_size_and_start_index) {
    MathVector<float> vec(5, 2);
    EXPECT_EQ(static_cast <size_t>(5), vec.size());
    EXPECT_EQ(static_cast <size_t>(2), vec.get_start_index());
}
TEST(TestMathVectorLib, check_the_initialization_list_constructor) {
    MathVector<int> vec(4, { 1, 2, 3, 4 });
    EXPECT_EQ(static_cast <size_t>(4), vec.size());
    EXPECT_EQ(static_cast<size_t>(4), vec.capacity());
    EXPECT_EQ(static_cast<size_t>(0), vec.get_start_index());
}
TEST(TestMathVectorLib, check_the_initialization_list_constructor_with_start_index) {
    MathVector<int> vec(4, { 1, 2, 3, 4 }, 2);
    EXPECT_EQ(static_cast <size_t>(4), vec.size());
    EXPECT_EQ(static_cast<size_t>(4), vec.capacity());
    EXPECT_EQ(static_cast<size_t>(2), vec.get_start_index());
}
TEST(TestMathVectorLib, throw_when_try_copy_vector) {
    MathVector<int>* obj = nullptr;
    ASSERT_ANY_THROW(MathVector<int> copy_obj(*obj));
}
TEST(TestMathVectorLib, check_the_copy_constructor) {
    int array[5] = { 1, 2, 3, 4, 5 };
    MathVector<int> vec1(5, array);
    MathVector<int> vec2(vec1);
    EXPECT_EQ(static_cast <size_t>(5), vec2.size());
    EXPECT_EQ(static_cast<size_t>(5), vec2.capacity());
}
TEST(TestMathVectorLib, check_the_addition) {
    MathVector<int> vec1({ 2, 3, 4, 5 });
    MathVector<int> vec2({ 1, 2, 3, 4 });
    MathVector<int> res({ 3, 5, 7, 9 });
    EXPECT_EQ(res, vec1 + vec2);
}
TEST(TestMathVectorLib, check_the_addition_2) {
    MathVector<int> vec1({ 2, 3, 4, 5 }, 2);
    MathVector<int> vec2({ 1, 2, 3, 4 }, 2);
    MathVector<int> res({ 3, 5, 7, 9 }, 2);
    EXPECT_EQ(res, vec1 + vec2);
}
TEST(TestMathVectorLib, check_the_addition_exception_when_different_size) {
    MathVector<int> vec1({ 2, 3, 4, 5, 6 });
    MathVector<int> vec2({ 1, 2, 3, 4 });

    ASSERT_ANY_THROW(vec1 + vec2);
}
TEST(TestMathVectorLib, check_the_addition_exception_when_different_size_2) {
    MathVector<int> vec1({ 2, 3, 4, 5 }, 1);
    MathVector<int> vec2({ 1, 2, 3, 4 }, 2);

    ASSERT_ANY_THROW(vec1 + vec2);
}
TEST(TestMathVectorLib, check_the_addition_exception_when_empty_vector) {
    MathVector<int> vec1;
    MathVector<int> vec2({ 1, 2, 3, 4 });
    ASSERT_ANY_THROW(vec1 + vec2);
}
TEST(TestMathVectorLib, check_the_subtraction) {
    MathVector<int> vec1({ 2, 3, 4, 5 });
    MathVector<int> vec2({ 1, 2, 3, 4 });
    MathVector<int> res({ 1, 1, 1, 1 });
    EXPECT_EQ(res, vec1 - vec2);
}
TEST(TestMathVectorLib, check_the_subtraction_exception_when_different_size) {
    MathVector<int> vec1({ 2, 3, 4, 5, 6 });
    MathVector<int> vec2({ 1, 2, 3, 4 });
    ASSERT_ANY_THROW(vec1 - vec2);
}
TEST(TestMathVectorLib, check_the_subtraction_exception_when_different_size_2) {
    MathVector<int> vec1({ 2, 3, 4, 5 });
    MathVector<int> vec2({ 1, 2, 3, 4 }, 1);

    ASSERT_ANY_THROW(vec1 - vec2);
}
TEST(TestMathVectorLib, check_the_subtraction_exception_when_empty_vector) {
    MathVector<int> vec1;
    MathVector<int> vec2({ 1, 2, 3, 4 });
    ASSERT_ANY_THROW(vec1 - vec2);
}
TEST(TestMathVectorLib, check_the_multiplication) {
    MathVector<int> vec1({ 2, 3, 4, 5 });
    MathVector<int> vec2({ 1, 2, 3, 4 });
    EXPECT_EQ(40, vec1 * vec2);
}
TEST(TestMathVectorLib, check_the_multiplication_exception_when_different_size) {
    MathVector<int> vec1({ 2, 3, 4, 5, 6 });
    MathVector<int> vec2({ 1, 2, 3, 4 });
    ASSERT_ANY_THROW(vec1 * vec2);
}
TEST(TestMathVectorLib, check_the_multiplication_exception_when_different_size_2) {
    MathVector<int> vec1({ 2, 3, 4, 5}, 2);
    MathVector<int> vec2({ 1, 2, 3, 4 });
    ASSERT_ANY_THROW(vec1 * vec2);
}
TEST(TestMathVectorLib, check_the_multiplication_exception_when_empty_vector) {
    MathVector<int> vec1({ 1, 2, 3, 4 });
    MathVector<int> vec2;
    ASSERT_ANY_THROW(vec1 * vec2);
}
TEST(TestMathVectorLib, check_the_multiplication_by_a_scalar) {
    MathVector<int> vec1({ 2, 3, 4, 5, 6 });
    MathVector<int> res({ 6, 9, 12, 15, 18 });
    EXPECT_EQ(res, vec1 * 3);
}
TEST(TestMathVectorLib, check_the_multiplication_by_a_scalar_exception_when_empty_vector) {
    MathVector<int> vec2;
    ASSERT_ANY_THROW(vec2 * 4);
}
TEST(TestMathVectorLib, check_addition_with_assignment) {
    MathVector<int> vec1({ 2, 3, 4, 5 });
    MathVector<int> vec2({ 1, 2, 3, 4 });
    MathVector<int> res({ 3, 5, 7, 9 });
    EXPECT_EQ(res, vec1 += vec2);
}
TEST(TestMathVectorLib, check_addition_with_assignment_with_different_start_index) {
    MathVector<int> vec1({ 4, 5 }, 2);
    MathVector<int> vec2({ 1, 2, 3, 4 });
    MathVector<int> res({ 1, 2, 7, 9 });
    EXPECT_EQ(res, vec1 += vec2);
}
TEST(TestMathVectorLib, check_addition_with_assignment_with_different_start_index_2) {
    MathVector<int> vec1({ 1, 2, 3, 4 });
    MathVector<int> vec2({ 4, 5, 6 }, 1);
    MathVector<int> res({ 1, 6, 8, 10 });
    EXPECT_EQ(res, vec1 += vec2);
}
TEST(TestMathVectorLib, check_the_addition_with_assignment_exception_when_different_size) {
    MathVector<int> vec1({ 2, 3, 4, 5, 6 });
    MathVector<int> vec2({ 1, 2, 3, 4 });
    ASSERT_ANY_THROW(vec1 += vec2);
}
TEST(TestMathVectorLib, check_the_addition_with_assignment_exception_when_different_size_2) {
    MathVector<int> vec1({ 2, 3, 4, 5 }, 2);
    MathVector<int> vec2({ 1, 2, 3, 4 });
    ASSERT_ANY_THROW(vec1 += vec2);
}
TEST(TestMathVectorLib, check_the_addition_with_assignment_exception_when_empty_vector) {
    MathVector<int> vec1({ 1, 2, 3, 4 });
    MathVector<int> vec2;
    ASSERT_ANY_THROW(vec1 += vec2);
}
TEST(TestMathVectorLib, check_the_subtraction_with_assignment) {
    MathVector<int> vec1({ 2, 3, 4, 5 });
    MathVector<int> vec2({ 1, 2, 3, 4 });
    MathVector<int> res({ 1, 1, 1, 1 });
    EXPECT_EQ(res, vec1 -= vec2);
}
TEST(TestMathVectorLib, check_subtraction_with_assignment_with_different_start_index) {
    MathVector<int> vec1({ 4, 5 }, 2);
    MathVector<int> vec2({ 1, 2, 3, 4 });
    MathVector<int> res({ -1, -2, 1, 1 });
    EXPECT_EQ(res, vec1 -= vec2);
}
TEST(TestMathVectorLib, check_subtraction_with_assignment_with_different_start_index_2) {
    MathVector<int> vec1({ 1, 2, 3, 4 });
    MathVector<int> vec2({ 4, 5, 6 }, 1);
    MathVector<int> res({ 1, -2, -2, -2 });
    EXPECT_EQ(res, vec1 -= vec2);
}
TEST(TestMathVectorLib, check_the_subtraction_with_assignment_exception_when_different_size) {
    MathVector<int> vec1({ 2, 3, 4, 5, 6 });
    MathVector<int> vec2({ 1, 2, 3, 4 });
    ASSERT_ANY_THROW(vec1 -= vec2);
}
TEST(TestMathVectorLib, check_the_subtraction_with_assignment_exception_when_different_size_2) {
    MathVector<int> vec1({ 2, 3, 4, 5 }, 5);
    MathVector<int> vec2({ 1, 2, 3, 4 });
    ASSERT_ANY_THROW(vec1 -= vec2);
}
TEST(TestMathVectorLib, check_the_subtraction_with_assignment_exception_when_empty_vector) {
    MathVector<int> vec1({ 1, 2, 3, 4 });
    MathVector<int> vec2;
    ASSERT_ANY_THROW(vec1 -= vec2);
}
TEST(TestMathVectorLib, check_the_multiplication_by_a_scalar_with_assignment) {
    MathVector<int> vec1({ 2, 3, 4 });
    MathVector<int> res({ 6, 9, 12 });
    EXPECT_EQ(res, vec1 *= 3);
}
TEST(TestMathVectorLib, check_the_multiplication_by_a_scalar_with_assignment_exception_when_empty_vector) {
    MathVector<int> vec1;
    ASSERT_ANY_THROW(vec1 *= 2);
}
TEST(TestMathVectorLib, check_the_assignment) {
    MathVector<int> vec1;
    MathVector<int> vec2({ 1, 2, 3, 4 });
    vec1 = vec2;
    EXPECT_EQ(vec2, vec1);
}
TEST(TestMathVectorLib, check_the_index_conversion_operator) {
    MathVector<int> vec({ 1, 2, 3, 4 });
    vec[2] = 6;
    EXPECT_EQ(6, vec[2]);
}
TEST(TestMathVectorLib, check_the_at) {
    MathVector<int> vec({ 1, 2, 3, 4 });
    EXPECT_EQ(2, vec.at(1));
}
TEST(TestMathVectorLib, check_the_equality_operator) {
    MathVector<int> vec1({ 1, 2, 3, 4 });
    MathVector<int> vec2({ 1, 2, 3, 4 });
    EXPECT_TRUE(vec1 == vec2);
}
TEST(TestMathVectorLib, check_the_equality_operator_2) {
    MathVector<int> vec1({ 1, 2, 3, 4 });
    MathVector<int> vec2({ 1, 4, 3, 4 });
    EXPECT_FALSE(vec1 == vec2);
}
TEST(TestMathVectorLib, check_the_not_equality_operator) {
    MathVector<int> vec1({ 1, 2, 3, 4 });
    MathVector<int> vec2({ 1, 4, 3, 4 });
    EXPECT_TRUE(vec1 != vec2);
}
TEST(TestMathVectorLib, check_the_not_equality_operator_2) {
    MathVector<int> vec1({ 1, 2, 3, 4 });
    MathVector<int> vec2({ 1, 2, 3, 4 });
    EXPECT_FALSE(vec1 != vec2);
}
