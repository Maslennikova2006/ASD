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

//Matrix<bool> generate_labyrinth(int X, int Y, int N, int M) {
//    if (N < 5 || M < 5)
//        throw std::invalid_argument("Размер лабиринта должен быть не меньше 5х5!");
//    if (X < 1 || X > M*N)
//        throw std::invalid_argument("Некорректный номер ячейки!");
//    if (Y < 1 || Y > M*N)
//        throw std::invalid_argument("Некорректный номер ячейки!");
//    bool entrance_on_border = false;
//    bool exit_on_border = false;
//
//    if (X <= M)
//        entrance_on_border = true;
//    else if (X > M * (N - 1))
//        entrance_on_border = true;
//    else if (X % M == 1)  // первый столбец
//        entrance_on_border = true;
//    else if (X % M == 0)  // последний столбец
//        entrance_on_border = true;
//
//     Проверка для выхода
//    if (Y <= M)  // первая строка
//        exit_on_border = true;
//    else if (Y > M * (N - 1))  // последняя строка
//        exit_on_border = true;
//    else if (Y % M == 1)  // первый столбец
//        exit_on_border = true;
//    else if (Y % M == 0)  // последний столбец
//        exit_on_border = true;
//
//    if (!entrance_on_border)
//        throw std::invalid_argument("Вход должен быть с краю!");
//    if (!exit_on_border)
//        throw std::invalid_argument("Выход должен быть с краю!");
//
//    Matrix<bool> walls(N + 1, M + 1);
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < M; j++) {
//            walls[i][j] = true;
//        }
//    }
//    int entrance_row = (X - 1) / M;    // ПРАВИЛЬНО: деление на M
//    int entrance_col = (X - 1) % M;    // ПРАВИЛЬНО: остаток от M
//    int exit_row = (Y - 1) / M;
//    int exit_col = (Y - 1) % M;
//
//    walls[entrance_row][entrance_col] = false;  // false = проход
//    walls[exit_row][exit_col] = false;
//    int size = N * M;
//    Dsu labyrinth(size);
//    for (int i = 0; i < size; i++) {
//        int gen = rand_generation(0, 100);
//        if (gen < 25) {
//            labyrinth.union_set(i, i + 1);
//            walls[i / M][i % M] = false;
//        }
//        else if (gen > 25 && gen < 50) {
//            labyrinth.union_set(i, i + M);
//            walls[i / M][i % M] = false;
//        }
//    }
//    return walls;
//}
//Matrix<bool> generate_labyrinth(int X, int Y, int N, int M) {
//     Проверка размеров
//    if (N < 5 || M < 5)
//        throw std::invalid_argument("Размер лабиринта должен быть не меньше 5х5!");
//
//     Проверка номеров ячеек
//    int total_cells = N * M;
//    if (X < 1 || X > total_cells)
//        throw std::invalid_argument("Некорректный номер ячейки входа!");
//    if (Y < 1 || Y > total_cells)
//        throw std::invalid_argument("Некорректный номер ячейки выхода!");
//
//     Проверка, что вход и выход не совпадают
//    if (X == Y)
//        throw std::invalid_argument("Вход и выход не могут совпадать!");
//
//     Проверка границ
//    bool entrance_on_border = false;
//    bool exit_on_border = false;
//
//     Проверка для входа
//    if (X <= M) {  // первая строка
//        entrance_on_border = true;
//    }
//    else if (X > M * (N - 1)) {  // последняя строка
//        entrance_on_border = true;
//    }
//    else if (X % M == 1) {  // первый столбец
//        entrance_on_border = true;
//    }
//    else if (X % M == 0) {  // последний столбец
//        entrance_on_border = true;
//    }
//
//     Проверка для выхода
//    if (Y <= M) {  // первая строка
//        exit_on_border = true;
//    }
//    else if (Y > M * (N - 1)) {  // последняя строка
//        exit_on_border = true;
//    }
//    else if (Y % M == 1) {  // первый столбец
//        exit_on_border = true;
//    }
//    else if (Y % M == 0) {  // последний столбец
//        exit_on_border = true;
//    }
//
//    if (!entrance_on_border)
//        throw std::invalid_argument("Вход должен быть с краю!");
//    if (!exit_on_border)
//        throw std::invalid_argument("Выход должен быть с краю!");
//
//     Создаем матрицу стен размером (N+1) x (M+1)
//     true = стена есть, false = стены нет (проход)
//    Matrix<bool> walls(N + 1, M + 1);
//
//     Инициализируем все стены
//    for (int i = 0; i <= N; i++) {
//        for (int j = 0; j <= M; j++) {
//            walls[i][j] = true;  // все стены установлены
//        }
//    }
//
//     Вычисляем координаты входа и выхода
//    int entrance_row = (X - 1) / M;    // строка ячейки (0..N-1)
//    int entrance_col = (X - 1) % M;    // столбец ячейки (0..M-1)
//    int exit_row = (Y - 1) / M;
//    int exit_col = (Y - 1) % M;
//
//     Открываем вход (убираем внешнюю стену)
//    if (X <= M) {  // верхняя граница
//        walls[0][entrance_col] = false;      // верхняя стенка над ячейкой
//        walls[0][entrance_col + 1] = false;  // и следующая
//    }
//    else if (X > M * (N - 1)) {  // нижняя граница
//        walls[N][entrance_col] = false;      // нижняя стенка под ячейкой
//        walls[N][entrance_col + 1] = false;
//    }
//    else if (X % M == 1) {  // левая граница
//        walls[entrance_row][0] = false;      // левая стенка
//        walls[entrance_row + 1][0] = false;
//    }
//    else if (X % M == 0) {  // правая граница
//        walls[entrance_row][M] = false;      // правая стенка
//        walls[entrance_row + 1][M] = false;
//    }
//
//     Открываем выход
//    if (Y <= M) {  // верхняя граница
//        walls[0][exit_col] = false;
//        walls[0][exit_col + 1] = false;
//    }
//    else if (Y > M * (N - 1)) {  // нижняя граница
//        walls[N][exit_col] = false;
//        walls[N][exit_col + 1] = false;
//    }
//    else if (Y % M == 1) {  // левая граница
//        walls[exit_row][0] = false;
//        walls[exit_row + 1][0] = false;
//    }
//    else if (Y % M == 0) {  // правая граница
//        walls[exit_row][M] = false;
//        walls[exit_row + 1][M] = false;
//    }
//
//     Генерация лабиринта
//    int size = N * M;
//    Dsu labyrinth(size);
//
//    for (int i = 0; i < size; i++) {
//        int gen = rand_generation(0, 100);
//        int row = i / M;    // строка ячейки (0..N-1)
//        int col = i % M;    // столбец ячейки (0..M-1)
//
//        if (gen < 25) {
//             Вертикальное соединение (убираем стену справа)
//            if (col < M - 1) {
//                int neighbor = i + 1;
//
//                if (labyrinth.find(i) != labyrinth.find(neighbor)) {
//                    labyrinth.union_set(i, neighbor);
//
//                     Убираем вертикальную стену между ячейками
//                     Стена находится справа от текущей ячейки
//                    walls[row + 1][col + 1] = false;  // внутренняя вертикальная стена
//                }
//            }
//        }
//        else if (gen < 50) {  // упрощенное условие
//             Горизонтальное соединение (убираем стену снизу)
//            if (row < N - 1) {
//                int neighbor = i + M;
//
//                if (labyrinth.find(i) != labyrinth.find(neighbor)) {
//                    labyrinth.union_set(i, neighbor);
//
//                     Убираем горизонтальную стену между ячейками
//                     Стена находится снизу от текущей ячейки
//                    walls[row + 1][col + 1] = false;  // внутренняя горизонтальная стена
//                }
//            }
//        }
//    }
//
//     Гарантируем связность входа и выхода
//    if (labyrinth.find(X - 1) != labyrinth.find(Y - 1)) {
//         Создаем прямой путь, убирая стены
//        int current_row = entrance_row;
//        int current_col = entrance_col;
//
//         Горизонтальная часть
//        while (current_col != exit_col) {
//             Убираем вертикальные стены между ячейками
//            walls[current_row + 1][current_col + 1] = false;
//
//            if (current_col < exit_col) {
//                current_col++;
//            }
//            else {
//                current_col--;
//            }
//        }
//
//         Вертикальная часть
//        while (current_row != exit_row) {
//             Убираем горизонтальные стены между ячейками
//            walls[current_row + 1][current_col + 1] = false;
//
//            if (current_row < exit_row) {
//                current_row++;
//            }
//            else {
//                current_row--;
//            }
//        }
//    }
//
//    return walls;
//}
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