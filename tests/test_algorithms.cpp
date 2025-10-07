// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"
#include "../lib_matrix/matrix.h"

TEST(TestAlgorithmsLib, check_1) {
    Matrix<int> matr({ {3, 1, 2}, {5, 8, 4}, {7, 6, 9} });
    int ans = find_the_local_minimum(matr);
    EXPECT_TRUE(ans == 1 || ans == 6);
}
TEST(TestAlgorithmsLib, check_2) {
    Matrix<int> matr({ {11, 15, 18}, {6, 9, 8}, {7, 8, 2} });
    int ans = find_the_local_minimum(matr);
    EXPECT_TRUE(ans == 2 || ans == 6);
}
TEST(TestAlgorithmsLib, check_3) {
    Matrix<int> matr({ {11, 15, 10, 9}, {6, 16, 3, 8}, {7, 4, 2, 13}, {14, 12, 1, 5} });
    int ans = find_the_local_minimum(matr);
    EXPECT_TRUE(ans == 1 || ans == 6);
}
