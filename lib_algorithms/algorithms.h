// Copyright 2025 Mary Maslennikova

#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

#include "../lib_matrix/matrix.h"

int rand_generation(int min, int max) noexcept;

int find_the_local_minimum(Matrix<int>& matrix) noexcept;

#endif  // LIB_ALGORITHMS_ALGORITHMS_H_