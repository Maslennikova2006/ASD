// Copyright 2025 Mary Maslennikova

#include <iostream>
#include <clocale>
#include <string>
#include <sstream>
#include <algorithm>
#include "../lib_algorithms/algorithms.h"
#include "../lib_stack/stack.h"
#include "../lib_tvector/tvector.h"
#include "../lib_bstree/bstree.h"
#include "../lib_queue/queue.h"
#include "../lib_queue_priority/queue_priority.h"
#include "../lib_matrix/matrix.h"
#include "../lib_dsu/dsu.h"

void show_position(Position pos) {
    switch (pos)
    {
    case intersect:
        std::cout << "Œ·˙ÂÍÚ˚ ÔÂÂÒÂÍ‡˛ÚÒˇ\n";
        break;
    case inside:
        std::cout << "Œ‰ËÌ Ó·˙ÂÍÚ ‚ÌÛÚË ‰Û„Ó„Ó\n";
        break;
    case no_point:
        std::cout << "Œ·˙ÂÍÚ˚ ÌÂ ËÏÂ˛Ú Ó·˘Ëı ÚÓ˜ÂÍ\n";
        break;
    case match:
        std::cout << "Œ·˙ÂÍÚ˚ ÒÓ‚Ô‡‰‡˛Ú\n";
        break;
    case touch:
        std::cout << "Œ·˙ÂÍÚ˚ Í‡Ò‡˛ÚÒˇ ‚ Ó‰ÌÓÈ ÚÓ˜ÍÂ\n";
        break;
    default:
        break;
    }
}

bool check_brackets(const std::string& str) {
    Stack<char> stack(str.length());

    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == '[' || str[i] == '(' || str[i] == '{') {
            stack.push(str[i]);
        }
        else if (str[i] == ']' || str[i] == ')' || str[i] == '}') {
            if (stack.is_empty())
                return false;

            switch (str[i]) {
            case ')':
                if (stack.top() == '(')
                    stack.pop();
                else
                    return false;
                break;
            case '}':
                if (stack.top() == '{')
                    stack.pop();
                else
                    return false;
                break;
            case ']':
                if (stack.top() == '[')
                    stack.pop();
                else
                    return false;
                break;
            }
        }
    }
    if (!stack.is_empty())
        return false;
    return true;
}

// (, ), +, -, *, /, ^, ˜ËÒÎ‡, ÔÂÂÏÂÌÌ˚Â
// +, -, *, /, ^ ‰‚‡ ‡„ÛÏÂÌÚ‡
// - ÛÌ‡Ì˚È ÏËÌÛÒ
// ÔÓ‚ÂÍ‡ ÒÍÓ·ÓÍ

void read_expression(const std::string& expression) {
    Stack<char> brackets(expression.length());
    char prev = '\0';
    size_t i = 0;
    while (i < expression.length()) {
        while (i < expression.length() && expression[i] == ' ') {
            i++;
        }
        if (i >= expression.length()) break;

        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            if ((prev >= 'a' && prev <= 'z') || (prev >= 'A' && prev <= 'Z') || (prev >= '0' && prev <= '9') || 
                prev == ')' || prev == ']' || prev == '}')
                throw std::invalid_argument("An operation is missing between the opening bracket and the number, variable or closing bracket!\n");
            brackets.push(expression[i]);
            size_t next_index = i + 1;
            while (next_index < expression.length() && expression[next_index] == ' ') {
                next_index++;
            }
            if (next_index < expression.length()) {
                if (expression[next_index] == '+' || expression[next_index] == '*' ||
                    expression[next_index] == '/' || expression[next_index] == '^' ||
                    expression[next_index] == ')' || expression[next_index] == ']' || expression[next_index] == '}')
                    throw std::invalid_argument("An operation or a closing bracket cannot follow an opening bracket!\n");
            }
        }
        else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (brackets.is_empty())
                throw std::invalid_argument("Missing opened bracket!\n");
            switch (expression[i]) {
            case ')':
                if (brackets.top() == '(')
                    brackets.pop();
                else
                    throw std::invalid_argument("An incorrect bracket was used, and ')' was expected!");
                break;
            case '}':
                if (brackets.top() == '{')
                    brackets.pop();
                else
                    throw std::invalid_argument("An incorrect bracket was used, and '}' was expected!");
                break;
            case ']':
                if (brackets.top() == '[')
                    brackets.pop();
                else
                    throw std::invalid_argument("An incorrect bracket was used, and ']' was expected!");
                break;
            }
            if (prev == '+' || prev == '-' || prev == '*' ||
                prev == '/' || prev == '^')
                throw std::invalid_argument("The operation cannot be performed before the closing bracket!\n");
        }
        else if (expression[i] == '+' || expression[i] == '*' || expression[i] == '/' || expression[i] == '^') {
            if (prev == '\0' || prev == '(' || prev == '[' || prev == '{' ||
                prev == '+' || prev == '-' || prev == '*' || prev == '/' || prev == '^') {
                throw std::invalid_argument("Missing first operand in operation '" + std::string(1, expression[i]) + "'!\n");
            }
            bool isRightOperand = false;
            size_t next_index = i + 1;
            while (next_index < expression.length() && expression[next_index] == ' ') {
                next_index++;
            }
            if (next_index < expression.length()) {
                if ((expression[next_index] >= '0' && expression[next_index] <= '9') ||
                    (expression[next_index] >= 'a' && expression[next_index] <= 'z') ||
                    (expression[next_index] >= 'A' && expression[next_index] <= 'Z') ||
                    expression[next_index] == '(' || expression[next_index] == '[' || expression[next_index] == '{') {
                    isRightOperand = true;
                }
            }
            if (!isRightOperand)
                throw std::invalid_argument("Missing second operand in operation '" + std::string(1, expression[i]) + "'!\n");
        }
        else if (expression[i] == '-') {
            if (prev == '\0' || prev == '(' || prev == '[' || prev == '{' ||
                prev == '+' || prev == '-' || prev == '*' || prev == '/' || prev == '^') {
                size_t next_index = i + 1;
                while (next_index < expression.length() && expression[next_index] == ' ') {
                    next_index++;
                }
                if (next_index >= expression.length() ||
                    !((expression[next_index] >= '0' && expression[next_index] <= '9') ||
                        (expression[next_index] >= 'a' && expression[next_index] <= 'z') ||
                        (expression[next_index] >= 'A' && expression[next_index] <= 'Z') ||
                        expression[next_index] == '(' || expression[next_index] == '[' || expression[next_index] == '{')) {
                    throw std::invalid_argument("Missing operand for unary minus!\n");
                }
            }
            else {
                bool isRightOperand = false;
                size_t next_index = i + 1;
                while (next_index < expression.length() && expression[next_index] == ' ') {
                    next_index++;
                }
                if (next_index < expression.length()) {
                    if ((expression[next_index] >= '0' && expression[next_index] <= '9') ||
                        (expression[next_index] >= 'a' && expression[next_index] <= 'z') ||
                        (expression[next_index] >= 'A' && expression[next_index] <= 'Z') ||
                        expression[next_index] == '(' || expression[next_index] == '[' || expression[next_index] == '{') {
                        isRightOperand = true;
                    }
                }
                if (!isRightOperand)
                    throw std::invalid_argument("Missing second operand in operation '-'\n");
            }
        }
        else if ((expression[i] >= 'a' && expression[i] <= 'z') || (expression[i] >= 'A' && expression[i] <= 'Z')) {
            if ((prev >= 'a' && prev <= 'z') || (prev >= 'A' && prev <= 'Z'))
                throw std::invalid_argument("Missing operation between variables!\n");
            if (prev >= '0' && prev <= '9')
                throw std::invalid_argument("Missing operation between variable and number!\n");
        }
        else if (expression[i] >= '0' && expression[i] <= '9') {
            if ((prev >= 'a' && prev <= 'z') || (prev >= 'A' && prev <= 'Z'))
                throw std::invalid_argument("Missing operation between variable and number!\n");
        }
        prev = expression[i];
        i++;
    }
    if (!brackets.is_empty())
        throw std::invalid_argument("Missing closed bracket!");
}


void sort_vector() {
    BSTree<int, int> tree;
    TVector<Pair<int, int>> vec(15);
    for (int i = 0; i < 15; i++) {
        Pair<int, int> pair(i, i * 10);
        vec[i] = pair;
    }
    shuffle(vec);
    std::cout << "vec: ";
    vec.print();
    std::cout << std::endl;
    for (int i = 0; i < 15; i++) {
        tree.insert(vec[i].first, vec[i].second);
    }
    std::cout << "sort vec: ";
    tree.print_lcr();
}

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
        throw std::invalid_argument("–†–∞–∑–º–µ—Ä –ª–∞–±–∏—Ä–∏–Ω—Ç–∞ –¥–æ–ª–∂–µ–Ω –±—ã—Ç—å –Ω–µ –º–µ–Ω—å—à–µ 5—Ö5!");

    int size = N * M;
    if (X < 1 || X > size)
        throw std::invalid_argument("–ù–µ–∫–æ—Ä—Ä–µ–∫—Ç–Ω—ã–π –Ω–æ–º–µ—Ä —è—á–µ–π–∫–∏ –≤—Ö–æ–¥–∞!");
    if (Y < 1 || Y > size)
        throw std::invalid_argument("–ù–µ–∫–æ—Ä—Ä–µ–∫—Ç–Ω—ã–π –Ω–æ–º–µ—Ä —è—á–µ–π–∫–∏ –≤—ã—Ö–æ–¥–∞!");

    if (X == Y)
        throw std::invalid_argument("–í—Ö–æ–¥ –∏ –≤—ã—Ö–æ–¥ –Ω–µ –º–æ–≥—É—Ç —Å–æ–≤–ø–∞–¥–∞—Ç—å!");

    bool entrance = (X <= M) || (X > M * (N - 1)) ||
        (X % M == 1) || (X % M == 0);
    bool exit = (Y <= M) || (Y > M * (N - 1)) ||
        (Y % M == 1) || (Y % M == 0);

    if (!entrance)
        throw std::invalid_argument("–í—Ö–æ–¥ –¥–æ–ª–∂–µ–Ω –±—ã—Ç—å —Å –∫—Ä–∞—é!");
    if (!exit)
        throw std::invalid_argument("–í—ã—Ö–æ–¥ –¥–æ–ª–∂–µ–Ω –±—ã—Ç—å —Å –∫—Ä–∞—é!");
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
    /*int cell = 1;
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
                if (j < M) {
                    if (walls[i][j]) {
                        if (cell < 10) std::cout << "| " << cell << " ";
                        else std::cout << "|" << cell << " ";
                    }
                    else {
                        if (cell < 10) std::cout << "  " << cell << " ";
                        else std::cout << " " << cell << " ";
                    }
                    cell++;
                }
                else {
                    if (walls[i][j])
                        std::cout << "|";
                    else
                        std::cout << " ";
                }
            }
        }
        std::cout << "\n";
    }*/
}

void print_labyrinth_path(const Matrix<bool>& walls, int N, int M, TVector<int>& path) {
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
                if (j < M) {
                    int cell = ((i - 1) / 2) * M + j;

                    if (walls[i][j]) {
                        if (belongs_path(cell + 1, path)) {
                            //std::cout << "| * ";
                            std::cout << "| " << "\033[32m*\033[0m" << " ";
                        }
                        else
                            std::cout << "|   ";
                    }
                    else {
                        if (belongs_path(cell + 1, path)) {
                            //std::cout << "  * ";
                            std::cout << "  " << "\033[32m*\033[0m" << " ";
                        }
                        else
                            std::cout << "    ";
                    }
                }
                else {
                    std::cout << "|";
                }
            }
        }
        std::cout << "\n";
    }
}

bool belongs_path(int cell, TVector<int>& path) {
    for (int i = 0; i < path.size(); i++) {
        if (path[i] == cell)
            return true;
    }
    return false;
}


AdjacencyListGraph<int> labyrinth_to_graph(Matrix<bool>& lab, int N, int M) {
    AdjacencyListGraph<int> g;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int cur_ind = (i * M + j) + 1;
            if (i < N - 1 && !lab[2 * i + 2][j]) {
                g.add_edge(cur_ind, cur_ind + M);
            }
            if (j < M - 1 && !lab[2 * i + 1][j + 1]) {
                g.add_edge(cur_ind, cur_ind + 1);
            }
        }
    }
    return g;
}

void maze_pathfinding(Matrix<bool>& lab, int X, int Y, int N, int M) {
    AdjacencyListGraph<int> g = labyrinth_to_graph(lab, N, M);
    TVector<int> path = algorithm_Dijkstra_Q(g, X, Y);

    print_labyrinth_path(lab, N, M, path);
}