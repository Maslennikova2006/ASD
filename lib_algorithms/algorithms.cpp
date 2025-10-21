// Copyright 2025 Mary Maslennikova

#include <iostream>
#include <clocale>
#include "../lib_algorithms/algorithms.h"
#include "../lib_stack/stack.h"

void show_position(Position pos) {
    switch (pos)
    {
    case intersect:
        std::cout << "Объекты пересекаются\n";
        break;
    case inside:
        std::cout << "Один объект внутри другого\n";
        break;
    case no_point:
        std::cout << "Объекты не имеют общих точек\n";
        break;
    case match:
        std::cout << "Объекты совпадают\n";
        break;
    case touch:
        std::cout << "Объекты касаются в одной точке\n";
        break;
    default:
        break;
    }
}

bool check_brackets(std::string str) {
    Stack<char> stack;

    for (int i = 0; i < str.length(); i++) {
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
    return true;
}

// +, -, *, /, ^ два аргумента
// проверка скобок


void read_expression(std::string expression) {
    if (!check_brackets(expression))
        throw std::invalid_argument("Неправильно расcтавлены скобки!\n");
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*'
            || expression[i] == '/' || expression[i] == '^') {
            if ((expression[i - 1] < '0' || (expression[i - 1] > '9' && expression[i - 1] < 'a') || expression[i - 1] > 'z') ||
                (expression[i + 1] < '0' || (expression[i + 1] > '9' && expression[i + 1] < 'a') || expression[i + 1] > 'z')) {
                throw std::invalid_argument("Не хватает одного из операндов для бинарной операции!\n");
            }
        }
    }
}