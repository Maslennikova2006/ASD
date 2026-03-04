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



void check_input_data(int X, int Y, int N, int M) {
    if (N < 5 || M < 5)
        throw std::invalid_argument("Размер лабиринта должен быть не меньше 5х5!");

    int size = N * M;
    if (X < 1 || X > size)
        throw std::invalid_argument("Некорректный номер ячейки входа!");
    if (Y < 1 || Y > size)
        throw std::invalid_argument("Некорректный номер ячейки выхода!");

    if (X == Y)
        throw std::invalid_argument("Вход и выход не могут совпадать!");

    bool entrance = (X <= M) || (X > M * (N - 1)) ||
        (X % M == 1) || (X % M == 0);
    bool exit = (Y <= M) || (Y > M * (N - 1)) ||
        (Y % M == 1) || (Y % M == 0);

    if (!entrance)
        throw std::invalid_argument("Вход должен быть с краю!");
    if (!exit)
        throw std::invalid_argument("Выход должен быть с краю!");
}
void removing_borders(Matrix<bool>& walls, int cell, int N, int M) {
    int row = (cell - 1) / M;
    int col = (cell - 1) % M;
    if (cell <= M)
        walls[0][col] = false;
    else if (cell > M * (N - 1))
        walls[2 * N][col] = false;
    else if ((cell - 1) % M == 0)
        walls[2 * row + 1][0] = false;
    else
        walls[2 * row + 1][M] = false;
}
void creating_path(Dsu& labyrinth, Matrix<bool>& walls, int X, int Y, int M) {
    int cur = X - 1;
    int exit = Y - 1;

    while (labyrinth.find(cur) != labyrinth.find(exit)) {
        int row = cur / M;
        int col = cur % M;
        int exit_row = exit / M;
        int exit_col = exit % M;

        if (row < exit_row) {
            int next = cur + M;
            labyrinth.union_set(cur, next);
            walls[2 * row + 2][col] = false;
            cur = next;
        }
        else if (row > exit_row) {
            int next = cur - M;
            labyrinth.union_set(cur, next);
            walls[2 * row][col] = false;
            cur = next;
        }
        else if (col < exit_col) {
            int next = cur + 1;
            labyrinth.union_set(cur, next);
            walls[2 * row + 1][col + 1] = false;
            cur = next;
        }
        else if (col > exit_col) {
            int next = cur - 1;
            labyrinth.union_set(cur, next);
            walls[2 * row + 1][col] = false;
            cur = next;
        }
    }
}
Matrix<bool> generate_labyrinth(int X, int Y, int N, int M) {
    check_input_data(X, Y, N, M);

    Matrix<bool> walls(2*N + 1, M + 1);
    for (int i = 0; i < 2*N + 1; i++) {
        for (int j = 0; j < M + 1; j++) {
            walls[i][j] = true;
        }
    }

    removing_borders(walls, X, N, M);
    removing_borders(walls, Y, N, M);

    Dsu labyrinth(N*M);
    for (int i = 1; i < 2 * N; i++) {
        for (int j = 1; j < M; j++) {
            int gen = rand_generation(0, 100);
            if (gen < 60) {
                if (i % 2 == 1) {
                    int left_cell = (i / 2) * M + (j - 1);
                    int right_cell = (i / 2) * M + j;

                    if (labyrinth.find(left_cell) != labyrinth.find(right_cell)) {
                        labyrinth.union_set(left_cell, right_cell);
                        walls[i][j] = false;
                    }
                }
                else {
                    int left_cell = (i / 2 - 1) * M + j;
                    int right_cell = (i / 2) * M + j;

                    if (labyrinth.find(left_cell) != labyrinth.find(right_cell)) {
                        labyrinth.union_set(left_cell, right_cell);
                        walls[i][j] = false;
                    }
                }
            }
        }
    }

    if (labyrinth.find(X - 1) != labyrinth.find(Y - 1)) {
        creating_path(labyrinth, walls, X, Y, M);
    }
    return walls;
}

void print_labyrinth(const Matrix<bool>& walls, int N, int M) {
    for (int i = 0; i < 2 * N + 1; i++) {
        for (int j = 0; j < M + 1; j++) {
            if (i % 2 == 0) {
                if (j < M) {
                    if (walls[i][j])
                        std::cout << "+---";
                    else
                        std::cout << "+   ";
                }
                else {
                    std::cout << "+";
                }
            }
            else {
                if (walls[i][j])
                    std::cout << "|   ";
                else
                    std::cout << "    ";
            }
        }
        std::cout << "\n";
    }
}