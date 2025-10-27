// Copyright 2025 Mary Maslennikova

#include <iostream>
#include <clocale>
#include <string>
#include <sstream>
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

// (, ), +, -, *, /, ^, числа, переменные
// +, -, *, /, ^ два аргумента
// проверка скобок


void read_expression(std::string expression) {
    std::istringstream iss(expression);
    std::string symbol;
    Stack<char> brackets;
    char prev = '\0';

    while (iss >> symbol) {
        for (int i = 0; i < symbol.length(); i++) {
            if (symbol[i] == '(') {
                if ((prev >= 'a' && prev <= 'z') || (prev >= '0' && prev <= '9') || prev == ')')
                    throw std::invalid_argument("An operation is missing between the opening bracket and the number, variable or closing bracket!\n");
                brackets.push(symbol[i]);
                if (symbol[i + 1] == '+' || symbol[i + 1] == '-' || symbol[i + 1] == '*' ||
                    symbol[i + 1] == '/' || symbol[i + 1] == '^' || symbol[i + 1] == ')')
                    throw std::invalid_argument("An operation or a closing bracket cannot follow an opening bracket!\n");
            }
            else if (symbol[i] == ')') {
                if (brackets.is_empty())
                    throw std::invalid_argument("Missing opened bracket!\n");
                brackets.pop();
                if (prev == '+' || prev == '-' || prev == '*' ||
                    prev == '/' || prev == '^')
                    throw std::invalid_argument("The operation cannot be performed before the closing bracket!\n");
            }

            else if (symbol[i] == '+' || symbol[i] == '-' || symbol[i] == '*' ||
                symbol[i] == '/' || symbol[i] == '^') {
                if (prev == '\0' || prev == '(' || prev == '+' || prev == '-' ||
                    prev == '*' || prev == '/' || prev == '^') {
                    throw std::invalid_argument("Missing first operand in operation " + std::string(1, symbol[i]) + "!\n");
                }

                bool isRightOperand = false;
                if (i < symbol.length() - 1) {
                    if (symbol[i + 1] != ')' && symbol[i + 1] != '+' && symbol[i + 1] != '-' && 
                        symbol[i + 1] != '*' && symbol[i + 1] != '/' && symbol[i + 1] != '^')
                        isRightOperand = true;
                }
                else {
                    std::string next;
                    if (iss >> next) {
                        if (next[0] != ')' && next[0] != '+' && next[0] != '-' &&
                            next[0] != '*' && next[0] != '/' && next[0] != '^') {
                            isRightOperand = true;
                        }
                        for (int j = next.length() - 1; j >= 0; j--) {
                            iss.putback(next[j]);
                        }
                    }
                }
                if (!isRightOperand)
                    throw std::invalid_argument("Missing second operand in operation " + std::string(1, symbol[i]) + "!\n");
            }

            else if (symbol[i] >= 'a' && symbol[i] <= 'z') {
                if (prev >= 'a' && prev <= 'z')
                    throw std::invalid_argument("Missing operation between variables!\n");
                if (prev >= '0' && prev <= '9')
                    throw std::invalid_argument("Missing operation between variable and number!\n");
            }
            else if (symbol[i] >= '0' && symbol[i] <= '9') {
                if (prev >= 'a' && prev <= 'z')
                    throw std::invalid_argument("Missing operation between variable and number!\n");
            }
            prev = symbol[i];
        }
    }
    if (!brackets.is_empty())
        throw std::invalid_argument("Missing closed bracket!");
}
