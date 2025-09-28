// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include <iostream>
#include <initializer_list>
#include "../lib_matrix/matrix.h"

TEST(TestMatrixLib, check_the_default_constructor) {
    Matrix<float> matrix;

    EXPECT_EQ(static_cast <size_t>(0), matrix.get_start_index());
}
TEST(TestMatrixLib, check_the_size_constructor) {
    Matrix<int> matrix(5, 3);

    EXPECT_EQ(static_cast <size_t>(5), matrix.get_m());
    EXPECT_EQ(static_cast <size_t>(3), matrix.get_n());
    for (size_t i = 0; i < 5; i++) {
        EXPECT_EQ(matrix[i].size(), 3);
    }
}
TEST(TestMatrixLib, check_the_initializer_lists_constructor) {
    Matrix<int> matrix({ { 2, 3, 4, 5 }, {3, 4, 5, 6} });

    EXPECT_EQ(static_cast <size_t>(2), matrix.get_m());
    EXPECT_EQ(static_cast <size_t>(4), matrix.get_n());
    for (size_t i = 0; i < 2; i++) {
        EXPECT_EQ(matrix[i].size(), 4);
    }
}
TEST(TestMatrixLib, check_the_type_conversion_constructor) {
    MathVector<MathVector<int>> vectors(2);
    vectors[0] = MathVector<int>({ 1, 2, 3 });
    vectors[1] = MathVector<int>({ 4, 5, 6 });
    Matrix<int> matrix(vectors);

    EXPECT_EQ(matrix.get_m(), 2);
    EXPECT_EQ(matrix.get_n(), 3);
    EXPECT_EQ(matrix[0][0], 1);
    EXPECT_EQ(matrix[0][1], 2);
    EXPECT_EQ(matrix[0][2], 3);
    EXPECT_EQ(matrix[1][0], 4);
    EXPECT_EQ(matrix[1][1], 5);
    EXPECT_EQ(matrix[1][2], 6);
}
TEST(TestMatrixLib, throw_when_try_copy_vector) {
    Matrix<int>* obj = nullptr;
    ASSERT_ANY_THROW(Matrix<int> copy_obj(*obj));
}
TEST(TestMatrixLib, check_the_copy_constructor) {
    Matrix<int> matrix1({{2, 4, 5}, {4, 5, 6}, {5, 6, 7}});
    Matrix<int> matrix2(matrix1);
    EXPECT_EQ(static_cast <size_t>(3), matrix2.get_m());
    EXPECT_EQ(static_cast <size_t>(3), matrix2.get_n());
}
TEST(TestMatrixLib, check_index_access) {
    Matrix<int> matrix(2, 2);
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[1][0] = 3;
    matrix[1][1] = 4;

    EXPECT_EQ(matrix[0][0], 1);
    EXPECT_EQ(matrix[0][1], 2);
    EXPECT_EQ(matrix[1][0], 3);
    EXPECT_EQ(matrix[1][1], 4);
}
TEST(TestMatrixLib, check_equality_operator) {
    Matrix<int> m1({ {1, 2}, {3, 4} });
    Matrix<int> m2({ {1, 2}, {3, 4} });
    Matrix<int> m3({ {1, 2}, {3, 5} });

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);
}
TEST(TestMatrixLib, check_not_equality_operator) {
    Matrix<int> m1({ {1, 2}, {3, 4} });
    Matrix<int> m2({ {1, 2}, {3, 4} });
    Matrix<int> m3({ {1, 2}, {3, 5} });

    EXPECT_FALSE(m1 != m2);
    EXPECT_TRUE(m1 != m3);
}
TEST(TestMatrixLib, check_the_assignment) {
    Matrix<int> matrix1;
    Matrix<int> matrix2({ {1, 4, 7}, {7, 8, 9}, {2, 3, 5} });
    matrix1 = matrix2;

    EXPECT_EQ(matrix2, matrix1);
}
TEST(TestMatrixLib, check_the_addition) {
    Matrix<int> matrix1({ { 2, 3, 4, 5 }, {3, 4, 5, 6}, {4, 5, 6, 7} });
    Matrix<int> matrix2({ { 1, 2, 3, 4 }, {2, 3, 4, 5}, {3, 4, 5, 6} });
    Matrix<int> res({ { 3, 5, 7, 9 }, {5, 7, 9, 11}, {7, 9, 11, 13} });

    EXPECT_EQ(res, matrix1 + matrix2);
}
TEST(TestMatrixLib, check_the_addition_exception_when_different_size) {
    Matrix<int> matrix1({ { 2, 3, 4, 5 }, {3, 4, 5, 6} });
    Matrix<int> matrix2({ { 1, 2, 3, 4 }, {2, 3, 4, 5}, {3, 4, 5, 6} });

    ASSERT_ANY_THROW(matrix1 + matrix2);
}
TEST(TestMatrixLib, check_the_addition_exception_when_empty_matrix) {
    Matrix<int> matrix1;
    Matrix<int> matrix2({ { 1, 2, 3, 4 }, {2, 3, 4, 5}, {3, 4, 5, 6} });

    ASSERT_ANY_THROW(matrix1 + matrix2);
}
TEST(TestMatrixLib, check_the_subtraction) {
    Matrix<int> matrix1({ { 2, 5, 4, 9 }, {3, 4, 8, 6}, {4, 8, 15, 7} });
    Matrix<int> matrix2({ { 1, 2, 3, 4 }, {2, 3, 4, 5}, {3, 4, 5, 6} });
    Matrix<int> res({ { 1, 3, 1, 5 }, {1, 1, 4, 1}, {1, 4, 10, 1} });

    EXPECT_EQ(res, matrix1 - matrix2);
}
TEST(TestMatrixLib, check_the_subtraction_exception_when_different_size) {
    Matrix<int> matrix1({ { 2, 3, 4, 5 }, {3, 4, 5, 6} });
    Matrix<int> matrix2({ { 1, 2, 3, 4 }, {2, 3, 4, 5}, {3, 4, 5, 6} });

    ASSERT_ANY_THROW(matrix1 - matrix2);
}
TEST(TestMatrixLib, check_the_subtraction_exception_when_empty_matrix) {
    Matrix<int> matrix1;
    Matrix<int> matrix2({ { 1, 2, 3, 4 }, {2, 3, 4, 5}, {3, 4, 5, 6} });

    ASSERT_ANY_THROW(matrix1 - matrix2);
}
TEST(TestMatrixLib, check_the_multiplication) {
    Matrix<int> matrix1({ { 1, 2, 3 }, {4, 5, 6} });
    Matrix<int> matrix2({ { 7, 8 }, {9, 10}, {11, 12} });
    Matrix<int> res({ { 58, 64 }, {139, 154} });

    EXPECT_EQ(res, matrix1 * matrix2);
}
TEST(TestMatrixLib, check_the_multiplication_exception_when_different_size) {
    Matrix<int> matrix1({ { 2, 3, 4, 5 }, {3, 4, 5, 6} });
    Matrix<int> matrix2({ { 1, 2, 3, 4 }, {2, 3, 4, 5}, {3, 4, 5, 6} });

    ASSERT_ANY_THROW(matrix1 * matrix2);
}
TEST(TestMatrixLib, check_the_multiplication_exception_when_empty_matrix) {
    Matrix<int> matrix1;
    Matrix<int> matrix2({ { 1, 2, 3, 4 }, {2, 3, 4, 5}, {3, 4, 5, 6} });

    ASSERT_ANY_THROW(matrix1 * matrix2);
}
TEST(TestMatrixLib, check_the_multiplication_by_a_scalar) {
    Matrix<int> matrix({ { 1, 2, 3, 4 }, {2, 3, 4, 5}, {3, 4, 5, 6} });
    Matrix<int> res({ {3, 6, 9, 12}, {6, 9, 12, 15}, {9, 12, 15, 18} });

    EXPECT_EQ(res, matrix * 3);
}
TEST(TestMatrixLib, check_the_multiplication_by_a_scalar_exception_when_empty_matrix) {
    Matrix<int> matrix;

    ASSERT_ANY_THROW(matrix * 4);
}