// Copyright 2025 Mary Maslennikova

#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

#include "../lib_matrix/matrix.h"
#include "../lib_dsu/dsu.h"

int rand_generation(int min, int max) noexcept;

int find_the_local_minimum(Matrix<int>& matrix) noexcept;

int count_the_number_of_islands(Matrix<int> matr);

Matrix<bool> generate_labyrinth(int X, int Y, int N, int M);
void print_labyrinth(const Matrix<bool>& walls, int n, int m);
void check_input_data(int X, int Y, int N, int M);
void removing_borders(Matrix<bool>& walls, int cell, int N, int M);
void creating_path(Dsu& labyrinth, Matrix<bool>& walls, int X, int Y, int M);
#endif  // LIB_ALGORITHMS_ALGORITHMS_H_
