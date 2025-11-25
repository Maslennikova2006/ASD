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

// (, ), +, -, *, /, ^, числа, переменные
// +, -, *, /, ^ два аргумента
// - унарный минус
// проверка скобок

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
