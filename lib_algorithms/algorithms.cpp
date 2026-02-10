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

Matrix<bool> generate_labyrinth(int X, int Y, int N, int M) {
    if (N < 5 || M < 5)
        throw std::invalid_argument("Размер лабиринта должен быть не меньше 5х5!");

    int size = N * M;
    if (X < 1 || X > size)
        throw std::invalid_argument("Некорректный номер ячейки входа!");
    if (Y < 1 || Y > size)
        throw std::invalid_argument("Некорректный номер ячейки выхода!");

    if (X == Y)
        throw std::invalid_argument("Вход и выход не могут совпадать!");  // ?

    bool entrance = (X <= M) || (X > M * (N - 1)) ||
        (X % M == 1) || (X % M == 0);
    bool exit = (Y <= M) || (Y > M * (N - 1)) ||
        (Y % M == 1) || (Y % M == 0);

    if (!entrance)
        throw std::invalid_argument("Вход должен быть с краю!");
    if (!exit)
        throw std::invalid_argument("Выход должен быть с краю!");

    Matrix<bool> walls(N + 1, M + 1);
    for (int i = 0; i < N + 1; i++) {
        for (int j = 0; j < M + 1; j++) {
            walls[i][j] = true;
        }
    }

    int entrance_row = (X - 1) / M;
    int entrance_col = (X - 1) % M;
    int exit_row = (Y - 1) / M;
    int exit_col = (Y - 1) % M;

    if (X <= M)
        walls[0][entrance_col + 1] = false;
    else if (X > M * (N - 1))
        walls[N][entrance_col + 1] = false;
    else if (X % M == 1)
        walls[entrance_row + 1][0] = false;
    else
        walls[entrance_row + 1][M] = false;

    if (Y <= M)
        walls[0][exit_col + 1] = false;
    else if (Y > M * (N - 1))
        walls[N][exit_col + 1] = false;
    else if (Y % M == 1)
        walls[exit_row + 1][0] = false;
    else
        walls[exit_row + 1][M] = false;

    Dsu labyrinth(size);
    for (int i = 0; i < size; i++) {
        int gen = rand_generation(0, 100);
        int row = i / M;
        int col = i % M;

        if (gen < 25 && col < M - 1) {
            labyrinth.union_set(i, i + 1);
            walls[row + 1][col + 1] = false;
        }
        else if (gen < 50 && row < N - 1) {
            labyrinth.union_set(i, i + M);
            walls[row + 1][col + 1] = false;
        }
    }

    if (labyrinth.find(X - 1) != labyrinth.find(Y - 1)) {
        labyrinth.union_set(X - 1, Y - 1);
    }

    return walls;
}


// __________________
// 1 | 2 | 3 | 4 | 5 |
// __________________
//|6 | 7 | 8 | 9 | 10|
// __________________
//|11| 12| 13| 14| 15
// __________________
//|16| 17| 18| 19| 20|
// __________________
//|21| 22| 23| 24| 25
// __________________