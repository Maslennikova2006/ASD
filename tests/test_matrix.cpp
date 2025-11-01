// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include <iostream>
#include <initializer_list>
#include "../lib_matrix/matrix.h"

TEST(TestMatrixLib, check_the_default_constructor) {
    Matrix<float> matrix;

    EXPECT_EQ(static_cast <size_t>(0), matrix.size());
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
    EXPECT_EQ(matrix[1][2], 6);
}
TEST(TestMatrixLib, throw_when_try_copy_matrix) {
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
TEST(TestMatrixLib, check_the_transposition) {
    Matrix<int> matrix({ { 2, 3, 4, 5 }, {3, 4, 5, 6}, {4, 5, 6, 7} });
    Matrix<int> res({ { 2, 3, 4 }, {3, 4, 5}, {4, 5, 6}, {5, 6, 7} });

    EXPECT_EQ(res, matrix.Trans());
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
TEST(TestMatrixLib, check_the_multiplication_by_a_vector) {
    Matrix<int> matrix({ { 1, 2, 3, 4 }, {2, 3, 4, 5}, {3, 4, 5, 6} });
    MathVector<int> vec({ 4, 5, 6, 7 });
    MathVector<int> res({ 60, 82, 104 });

    EXPECT_EQ(res, matrix * vec);
}
TEST(TestMatrixLib, check_the_multiplication_by_a_vector_exception_when_different_size) {
    Matrix<int> matrix({ { 1, 2, 3, 4 }, {2, 3, 4, 5}, {3, 4, 5, 6} });
    MathVector<int> vec({ 4, 5, 6 });

    ASSERT_ANY_THROW(matrix * vec);
}
TEST(TestMatrixLib, check_the_multiplication_by_a_vector_exception_when_empty_matrix) {
    Matrix<int> matrix;
    MathVector<int> vector({ 2, 3, 4 });

    ASSERT_ANY_THROW(matrix * vector);
}
TEST(TestMatrixLib, check_the_multiplication_by_a_vector_leftward) {
    Matrix<int> matrix({ { 4, 5, 6 }, {7, 8, 4}, {1, 2, 3}, {4, 8, 2} });
    MathVector<int> vec({ 4, 5, 1, 8 });
    MathVector<int> res({ 84, 126, 63 });

    EXPECT_EQ(res, vec * matrix);
}
TEST(TestMatrixLib, check_the_multiplication_by_a_vector_leftward_exception_when_different_size) {
    Matrix<int> matrix({ { 1, 2, 3, 4 }, {2, 3, 4, 5} });
    MathVector<int> vec({ 4, 5, 6 });

    ASSERT_ANY_THROW(vec * matrix);
}
TEST(TestMatrixLib, check_the_multiplication_by_a_vector_leftward_exception_when_empty_vector) {
    Matrix<int> matrix({ { 4, 5, 6 }, {7, 8, 4}, {1, 2, 3}, {4, 8, 2} });
    MathVector<int> vector;

    ASSERT_ANY_THROW(vector * matrix);
}
TEST(TestMatrixLib, check_addition_with_assignment) {
    Matrix<int> matrix1({ { 2, 3, 4, 5 }, {1, 2, 3, 4}, {3, 2, 1, 2} });
    Matrix<int> matrix2({ { 2, 1, 4, 3 }, {1, 3, 3, 8}, {1, 2, 1, 3} });
    Matrix<int> res({ { 4, 4, 8, 8 }, {2, 5, 6, 12}, {4, 4, 2, 5} });
    
    EXPECT_EQ(res, matrix1 += matrix2);
}
TEST(TestMatrixLib, check_the_addition_with_assignment_exception_when_different_size) {
    Matrix<int> matrix1({ { 2, 3, 4, 5 }, {1, 2, 3, 4}, {3, 2, 1, 2} });
    Matrix<int> matrix2({ { 2, 1, 4, 3 }, {1, 3, 3, 8} });

    ASSERT_ANY_THROW(matrix1 += matrix2);
}
TEST(TestMatrixLib, check_the_addition_with_assignment_exception_when_empty_matrix) {
    Matrix<int> matrix1;
    Matrix<int> matrix2({ { 1, 2, 3, 4 }, {2, 3, 4, 5}, {3, 4, 5, 6} });

    ASSERT_ANY_THROW(matrix1 += matrix2);
}
TEST(TestMatrixLib, check_subtraction_with_assignment) {
    Matrix<int> matrix1({ { 2, 3, 4, 5 }, {1, 2, 3, 4}, {3, 2, 1, 2} });
    Matrix<int> matrix2({ { 2, 1, 4, 3 }, {1, 3, 3, 8}, {1, 2, 1, 3} });
    Matrix<int> res({ { 0, 2, 0, 2 }, {0, -1, 0, -4}, {2, 0, 0, -1} });

    EXPECT_EQ(res, matrix1 -= matrix2);
}
TEST(TestMatrixLib, check_the_subtraction_with_assignment_exception_when_different_size) {
    Matrix<int> matrix1({ { 2, 3, 4, 5 }, {1, 2, 3, 4}, {3, 2, 1, 2} });
    Matrix<int> matrix2({ { 2, 1, 4, 3 }, {1, 3, 3, 8} });

    ASSERT_ANY_THROW(matrix1 -= matrix2);
}
TEST(TestMatrixLib, check_the_subtraction_with_assignment_exception_when_empty_matrix) {
    Matrix<int> matrix1;
    Matrix<int> matrix2({ { 1, 2, 3, 4 }, {2, 3, 4, 5}, {3, 4, 5, 6} });

    ASSERT_ANY_THROW(matrix1 -= matrix2);
}
TEST(TestMatrixLib, check_multiplication_with_assignment) {
    Matrix<int> matrix1({ { 2, 3, 4 }, {1, 2, 4}, {3, 2, 1} });
    Matrix<int> matrix2({ { 2, 1, 4 }, {1, 3, 3}, {1, 2, 1} });
    Matrix<int> res({ { 11, 19, 21 }, {8, 15, 14}, {9, 11, 19} });

    EXPECT_EQ(res, matrix1 *= matrix2);
}
TEST(TestMatrixLib, check_the_multiplication_with_assignment_exception_when_different_size) {
    Matrix<int> matrix1({ { 2, 3, 4, 5 }, {1, 2, 3, 4}, {3, 2, 1, 2} });
    Matrix<int> matrix2({ { 2, 1, 4, 3 }, {1, 3, 3, 8} });

    ASSERT_ANY_THROW(matrix1 *= matrix2);
}
TEST(TestMatrixLib, check_the_multiplication_with_assignment_exception_when_empty_matrix) {
    Matrix<int> matrix1;
    Matrix<int> matrix2({ { 1, 2, 3, 4 }, {2, 3, 4, 5}, {3, 4, 5, 6} });

    ASSERT_ANY_THROW(matrix1 *= matrix2);
}
TEST(TestMatrixLib, check_multiplication_by_a_scalar_with_assignment) {
    Matrix<int> matrix1({ { 2, 3, 4 }, {1, 2, 4}, {3, 2, 1} });
    Matrix<int> res({ { 8, 12, 16 }, {4, 8, 16}, {12, 8, 4} });

    EXPECT_EQ(res, matrix1 *= 4);
}
TEST(TestMatrixLib, check_the_multiplication_by_a_scalar_with_assignment_exception_when_empty_matrix) {
    Matrix<int> matrix1;

    ASSERT_ANY_THROW(matrix1 *= 2);
}