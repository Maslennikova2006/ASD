// Copyright 2025 Mary Maslennikova

#include "../lib_algorithms/algorithms.h"

int rand_generation(int min, int max) noexcept {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(min, max);
    return dist(gen);
}

int find_the_local_minimum(Matrix<int>& matrix) noexcept {
    int randI = rand_generation(0, matrix.get_m() - 1);
    int randJ = rand_generation(0, matrix.get_n() - 1);
    int currentMin = matrix[randI][randJ];
    int newI, newJ;


    int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

    while (1) {
        bool isUpdate = false;
        for (int i = 0; i < 4; i++) {
            newI = randI + dir[i][0];
            newJ = randJ + dir[i][1];
            if (newI >= 0 && newI < matrix.get_m() && newJ >= 0 && newJ < matrix.get_n()) {
                if (matrix[newI][newJ] < matrix[randI][randJ]) {
                    currentMin = matrix[newI][newJ];
                    isUpdate = true;
                    randI = newI;
                    randJ = newJ;
                }
            }
        }
        if (!isUpdate)
            break;
    }
    return currentMin;
}

int count_the_number_of_islands(Matrix<int> matr) {
    int m = matr.get_m();
    int n = matr.get_n();
    int count = 0;

    Dsu dsu(m * n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matr[i][j] == 1) {
                if (i > 0 && matr[i - 1][j] == -1) {
                    int cur = i * n + j;
                    int neighbour = (i - 1) * n + j;
                    dsu.union_set(cur, neighbour);
                }
                if (j > 0 && matr[i][j - 1] == -1) {
                    int cur = i * n + j;
                    int neighbour = i * n + (j - 1);
                    dsu.union_set(cur, neighbour);
                }
                matr[i][j] = -1;
            }
        }
    }

    int ind = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matr[i][j] == -1) {
                ind = i * n + j;
                if (dsu.find(ind) == ind)
                    count++;
            }
        }
    }
    return count;
}