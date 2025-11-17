// Copyright 2025 Mary Maslennikova

#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

#include "../lib_matrix/matrix.h"
#include "../lib_dsu/dsu.h"

int rand_generation(int min, int max) noexcept;

int find_the_local_minimum(Matrix<int>& matrix) noexcept;

int count_the_number_of_islands(Matrix<int> matr);

#endif  // LIB_ALGORITHMS_ALGORITHMS_H_