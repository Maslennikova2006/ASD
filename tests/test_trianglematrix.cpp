// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include <iostream>
#include <initializer_list>
#include "../lib_trianglematrix/trianglematrix.h"

TEST(TestTriangleMatrixLib, check_the_default_constructor) {
    TriangleMatrix<float> matrix;

    EXPECT_EQ(static_cast <size_t>(0), matrix.size());
}
TEST(TestTriangleMatrixLib, check_the_size_constructor) {
    TriangleMatrix<int> matrix(5);

    EXPECT_EQ(static_cast <size_t>(5), matrix.size());
    size_t size = 5;
    for (size_t i = 0; i < 5; i++) {
        EXPECT_EQ(matrix[i].size(), size--);
    }
}
TEST(TestTriangleMatrixLib, throw_when_try_initializer_lists_constructor) {
    ASSERT_ANY_THROW(TriangleMatrix<int> matrix({ { 2, 3, 4, 5 }, {3, 4, 5}, {1, 2} }););
}
TEST(TestTriangleMatrixLib, check_the_initializer_lists_constructor) {
    TriangleMatrix<int> matrix({ { 2, 3, 4, 5 }, {3, 4, 5}, {1, 2}, {1} });

    EXPECT_EQ(static_cast <size_t>(4), matrix.get_m());
    size_t size = 4;
    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(matrix[i].size(), size--);
    }
}
TEST(TestTriangleMatrixLib, check_the_type_conversion_constructor) {
    Matrix<int> matrix({{2, 3, 4}, {2, 3}, {4}});
    TriangleMatrix<int> trigMatrix(matrix);

    EXPECT_EQ(static_cast <size_t>(3), matrix.size());
    size_t size = 3;
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(matrix[i].size(), size--);
    }
}
TEST(TestTriangleMatrixLib, throw_when_try_type_conversion_constructor) {
    Matrix<int> matrix({ {2, 3, 4}, {2, 3, 8}, {4} });

    ASSERT_ANY_THROW(TriangleMatrix<int> trigMatrix(matrix));
}
TEST(TestTriangleMatrixLib, check_the_copy_constructor) {
    TriangleMatrix<int> matrix1({ {2, 4, 5}, {4, 5}, {5} });
    TriangleMatrix<int> matrix2(matrix1);
    EXPECT_EQ(static_cast <size_t>(3), matrix2.get_m());
    size_t size = 3;
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(matrix2[i].size(), size--);
    }
}
TEST(TestTriangleMatrixLib, throw_when_try_copy_matrix) {
    TriangleMatrix<int>* obj = nullptr;
    ASSERT_ANY_THROW(TriangleMatrix<int> copy_obj(*obj));
}
TEST(TestTriangleMatrixLib, check_equality_operator) {
    TriangleMatrix<int> m1({ {1, 2, 2}, {3, 4}, {5} });
    TriangleMatrix<int> m2({ {1, 2, 2}, {3, 4}, {5} });
    TriangleMatrix<int> m3({ {1, 2, 3}, {3, 5}, {7} });

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);
}
TEST(TestTriangleMatrixLib, check_not_equality_operator) {
    TriangleMatrix<int> m1({ {1, 2, 2}, {3, 4}, {5} });
    TriangleMatrix<int> m2({ {1, 2, 2}, {3, 4}, {5} });
    TriangleMatrix<int> m3({ {1, 2, 3}, {3, 5}, {7} });

    EXPECT_FALSE(m1 != m2);
    EXPECT_TRUE(m1 != m3);
}
TEST(TestTriangleMatrixLib, check_the_assignment) {
    Matrix<int> matrix1;
    Matrix<int> matrix2({ {1, 4, 7}, {7, 8, 9}, {2, 3, 5} });
    matrix1 = matrix2;

    EXPECT_EQ(matrix2, matrix1);
}
TEST(TestTriangleMatrixLib, check_the_addition) {
    TriangleMatrix<int> matrix1({ { 2, 3, 4, 5 }, {3, 4, 5}, {4, 5}, {5} });
    TriangleMatrix<int> matrix2({ { 1, 2, 3, 4 }, {2, 3, 4}, {3, 4}, {1} });
    TriangleMatrix<int> res({ { 3, 5, 7, 9 }, {5, 7, 9}, {7, 9}, {6} });

    EXPECT_EQ(res, matrix1 + matrix2);
}
TEST(TestTriangleMatrixLib, check_the_addition_exception_when_different_size) {
    TriangleMatrix<int> matrix1({ { 2, 3, 4, 5 }, {3, 4, 5}, {4, 5}, {5} });
    TriangleMatrix<int> matrix2({ { 1, 2, 3 }, {2, 3}, {3} });

    ASSERT_ANY_THROW(matrix1 + matrix2);
}
TEST(TestTriangleMatrixLib, check_the_addition_exception_when_empty_matrix) {
    Matrix<int> matrix1;
    Matrix<int> matrix2({ { 1, 2, 3 }, {2, 3}, {3} });

    ASSERT_ANY_THROW(matrix1 + matrix2);
}
TEST(TestTriangleMatrixLib, check_the_subtraction) {
    TriangleMatrix<int> matrix1({ { 2, 3, 4, 5 }, {3, 4, 5}, {4, 5}, {5} });
    TriangleMatrix<int> matrix2({ { 1, 2, 3, 4 }, {2, 3, 4}, {3, 4}, {1} });
    TriangleMatrix<int> res({ { 1, 1, 1, 1 }, {1, 1, 1}, {1, 1}, {4} });

    EXPECT_EQ(res, matrix1 - matrix2);
}
TEST(TestTriangleMatrixLib, check_the_subtraction_exception_when_different_size) {
    TriangleMatrix<int> matrix1({ { 2, 3, 5 }, {3, 5}, {5} });
    TriangleMatrix<int> matrix2({ { 1, 2}, {1} });

    ASSERT_ANY_THROW(matrix1 - matrix2);
}
TEST(TestTriangleMatrixLib, check_the_subtraction_exception_when_empty_matrix) {
    TriangleMatrix<int> matrix1;
    TriangleMatrix<int> matrix2({ { 1, 2, 3 }, {2, 3}, {6} });

    ASSERT_ANY_THROW(matrix1 - matrix2);
}
TEST(TestTriangleMatrixLib, check_the_multiplication) {
    TriangleMatrix<int> matrix1({ { 2, 3, 4}, {3, 4}, {4} });
    TriangleMatrix<int> matrix2({ { 1, 2, 3}, {2, 3}, {1} });
    TriangleMatrix<int> res({ { 2, 10, 19 }, {6, 13}, {4} });

    EXPECT_EQ(res, matrix1 * matrix2);
}
TEST(TestTriangleMatrixLib, check_the_multiplication_exception_when_different_size) {
    TriangleMatrix<int> matrix1({ { 2, 3, 4 }, {3, 6}, {4} });
    TriangleMatrix<int> matrix2({ { 1, 2, 3, 4 }, {2, 3, 4}, {3, 6}, {1} });

    ASSERT_ANY_THROW(matrix1 * matrix2);
}
TEST(TestTriangleMatrixLib, check_the_multiplication_exception_when_empty_matrix) {
    Matrix<int> matrix1;
    Matrix<int> matrix2({ { 1, 2, 4 }, {2, 3}, {3} });

    ASSERT_ANY_THROW(matrix1 * matrix2);
}
TEST(TestTriangleMatrixLib, check_the_multiplication_by_a_scalar) {
    TriangleMatrix<int> matrix({ { 1, 2, 4, 5 }, {4, 5, 6}, {6, 4}, {3} });
    TriangleMatrix<int> res({ {3, 6, 12, 15}, {12, 15, 18}, {18, 12}, {9} });

    EXPECT_EQ(res, matrix * 3);
}
TEST(TestTriangleMatrixLib, check_the_multiplication_by_a_scalar_exception_when_empty_matrix) {
    TriangleMatrix<int> matrix;

    ASSERT_ANY_THROW(matrix * 4);
}
TEST(TestTriangleMatrixLib, check_the_multiplication_by_a_vector) {
    TriangleMatrix<int> matrix({ { 1, 3, 4 }, {4, 5}, {3} });
    MathVector<int> vec({ 4, 5, 6 });
    MathVector<int> res({ 43, 50, 18 });

    EXPECT_EQ(res, matrix * vec);
}
TEST(TestTriangleMatrixLib, check_the_multiplication_by_a_vector_exception_when_different_size) {
    TriangleMatrix<int> matrix({ { 1, 2, 4 }, {4, 5}, {6} });
    MathVector<int> vec({ 4, 5, 6, 6 });

    ASSERT_ANY_THROW(matrix * vec);
}
TEST(TestTriangleMatrixLib, check_the_multiplication_by_a_vector_exception_when_empty_matrix) {
    TriangleMatrix<int> matrix;
    MathVector<int> vec({ 4, 5, 6, 6 });

    ASSERT_ANY_THROW(matrix * vec);
}
//TEST(TestTriangleMatrixLib, check_the_multiplication_by_a_vector_leftward) {
//    TriangleMatrix<int> matrix({ { 4, 5, 6 }, {7, 8}, {1} });
//    MathVector<int> vec({ 4, 5, 1 });
//    MathVector<int> res({ 16, 55, 65 });
//
//    EXPECT_EQ(res, vec * matrix);
//}
//TEST(TestTriangleMatrixLib, check_the_multiplication_by_a_vector_leftward_exception_when_empty_vector) {
//    TriangleMatrix<int> matrix({ { 4, 5, 6 }, {7, 8}, {1} });
//    MathVector<int> vec;
//
//    ASSERT_ANY_THROW(vec * matrix);
//}
//TEST(TestTriangleMatrixLib, check_the_multiplication_by_a_vector_leftward_exception_when_different_size) {
//    TriangleMatrix<int> matrix({ { 4, 5, 6 }, {7, 8}, {1} });
//    MathVector<int> vec({ 4, 5 });
//
//    ASSERT_ANY_THROW(vec * matrix);
//}
TEST(TestTriangleMatrixLib, check_addition_with_assignment) {
    TriangleMatrix<int> matrix1({ { 2, 3, 4, 5 }, {2, 3, 4}, {1, 2}, {5} });
    TriangleMatrix<int> matrix2({ { 2, 1, 4, 3 }, {3, 3, 8}, {1, 3}, {7} });
    TriangleMatrix<int> res({ { 4, 4, 8, 8 }, {5, 6, 12}, {2, 5}, {12} });

    EXPECT_EQ(res, matrix1 += matrix2);
}
TEST(TestTriangleMatrixLib, check_the_addition_with_assignment_exception_when_different_size) {
    TriangleMatrix<int> matrix1({ { 2, 3, 4, 5 }, {2, 3, 4}, {1, 2}, {5} });
    TriangleMatrix<int> matrix2({ { 2, 1, 4 }, {3, 8}, {4} });

    ASSERT_ANY_THROW(matrix1 += matrix2);
}
TEST(TestTriangleMatrixLib, check_the_addition_with_assignment_exception_when_empty_matrix) {
    TriangleMatrix<int> matrix1;
    TriangleMatrix<int> matrix2({ { 1, 2, 3 }, {4, 5}, {3} });

    ASSERT_ANY_THROW(matrix1 += matrix2);
}
TEST(TestTriangleMatrixLib, check_subtraction_with_assignment) {
    TriangleMatrix<int> matrix1({ { 2, 3, 4, 5 }, {2, 3, 8}, {9, 7}, {5} });
    TriangleMatrix<int> matrix2({ { 2, 1, 4, 3 }, {1, 3, 4}, {4, 2}, {2} });
    TriangleMatrix<int> res({ { 0, 2, 0, 2 }, {1, 0, 4}, {5, 5}, {3} });

    EXPECT_EQ(res, matrix1 -= matrix2);
}
TEST(TestTriangleMatrixLib, check_the_subtraction_with_assignment_exception_when_different_size) {
    TriangleMatrix<int> matrix1({ { 2, 3, 4, 5 }, {1, 3, 4}, {1, 2}, {9} });
    TriangleMatrix<int> matrix2({ { 2, 1, 4 }, {3, 8}, {7} });

    ASSERT_ANY_THROW(matrix1 -= matrix2);
}
TEST(TestTriangleMatrixLib, check_the_subtraction_with_assignment_exception_when_empty_matrix) {
    TriangleMatrix<int> matrix1;
    TriangleMatrix<int> matrix2({ { 1, 2, 3 }, {3, 4}, {3} });

    ASSERT_ANY_THROW(matrix1 -= matrix2);
}
TEST(TestTriangleMatrixLib, check_multiplication_with_assignment) {
    TriangleMatrix<int> matrix1({ { 2, 3, 4}, {3, 4}, {4} });
    TriangleMatrix<int> matrix2({ { 1, 2, 3}, {2, 3}, {1} });
    TriangleMatrix<int> res({ { 2, 10, 19 }, {6, 13}, {4} });

    EXPECT_EQ(res, matrix1 *= matrix2);
}
TEST(TestTriangleMatrixLib, check_the_multiplication_with_assignment_exception_when_different_size) {
    TriangleMatrix<int> matrix1({ { 2, 3, 4, 5 }, {1, 2, 3}, {1, 2}, {8} });
    TriangleMatrix<int> matrix2({ { 2, 1, 4 }, {1, 8}, {8} });

    ASSERT_ANY_THROW(matrix1 *= matrix2);
}
TEST(TestTriangleMatrixLib, check_the_multiplication_with_assignment_exception_when_empty_matrix) {
    TriangleMatrix<int> matrix1;
    TriangleMatrix<int> matrix2({ { 1, 2, 2 }, {4, 5}, {3} });

    ASSERT_ANY_THROW(matrix1 *= matrix2);
}
TEST(TestTriangleMatrixLib, check_multiplication_by_a_scalar_with_assignment) {
    TriangleMatrix<int> matrix1({ { 2, 3, 4}, {3, 4}, {4} });
    TriangleMatrix<int> res({ { 8, 12, 16 }, {12, 16}, {16} });

    EXPECT_EQ(res, matrix1 *= 4);
}
TEST(TestTriangleMatrixLib, check_the_multiplication_by_a_scalar_with_assignment_exception_when_empty_matrix) {
    TriangleMatrix<int> matrix1;

    ASSERT_ANY_THROW(matrix1 *= 2);
}
