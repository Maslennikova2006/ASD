// Copyright 2025 Mary Maslennikova

#include "../lib_parser/parser.h"
#include "../lib_stack/stack.h"
#include "../lib_sin/sin.h"
#include "../lib_cos/cos.h"
#include "../lib_tg/tg.h"

List<Lexem> Parser::parse(const std::string& expression) {
    List<Lexem> lexems;
    Stack<char> brackets;
    char prev = '\0';
    for (int i = 0; i < expression.length(); i++) {
        while (i < expression.length() && expression[i] == ' ') {
            i++;
        }
        if (expression[i] == '|') {
            if (prev == '\0' || prev == '(' || prev == '[' || prev == '{' ||
                prev == '+' || prev == '-' || prev == '*' || prev == '/' || prev == '^' || prev == '|') {
                brackets.push('|');
                lexems.push_back(Lexem("|", OpenedAbs, 0, 5));
            }
            else {
                if (brackets.is_empty() || brackets.top() != '|') {
                    throw std::invalid_argument("Missing opened modulus bracket!\n");
                }
                brackets.pop();
                lexems.push_back(Lexem("|", ClosedAbs, 0, 5));

                if (prev == '+' || prev == '-' || prev == '*' || prev == '/' || prev == '^') {
                    throw std::invalid_argument("The operation cannot be performed before the closing modulus!\n");
                }
            }
        }
        else if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            if ((prev >= 'a' && prev <= 'z') || (prev >= '0' && prev <= '9') || prev == ')')
                throw std::invalid_argument("An operation is missing between the opening bracket and the number, variable or closing bracket!\n");
            brackets.push(expression[i]);
            lexems.push_back(Lexem(std::string({expression[i]}), OpenBracket, 0, 5));
            int next_index = i + 1;
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
                if (brackets.top() == '(') {
                    brackets.pop();
                    lexems.push_back(Lexem(std::string({ expression[i] }), ClosedBracket));
                }
                else
                    throw std::invalid_argument("An incorrect bracket was used, and ')' was expected!");
                break;
            case '}':
                if (brackets.top() == '{') {
                    brackets.pop();
                    lexems.push_back(Lexem(std::string({ expression[i] }), ClosedBracket));
                }
                else
                    throw std::invalid_argument("An incorrect bracket was used, and '}' was expected!");
                break;
            case ']':
                if (brackets.top() == '[') {
                    brackets.pop();
                    lexems.push_back(Lexem(std::string({ expression[i] }), ClosedBracket));
                }
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
            int next_index = i + 1;
            while (next_index < expression.length() && expression[next_index] == ' ') {
                next_index++;
            }
            if (next_index < expression.length()) {
                if ((expression[next_index] >= '0' && expression[next_index] <= '9') ||
                    (expression[next_index] >= 'a' && expression[next_index] <= 'z') ||
                    expression[next_index] == '(' || expression[next_index] == '[' || expression[next_index] == '{') {
                    isRightOperand = true;
                }
            }
            if (!isRightOperand)
                throw std::invalid_argument("Missing second operand in operation '" + std::string(1, expression[i]) + "'!\n");
            int priority = 0;
            switch (expression[i]) {
            case '+':
                priority = 1;
                break;
            case '*': case '/':
                priority = 2;
                break;
            case '^':
                priority = 3;
                break;
            default:
                break;
            }
            lexems.push_back(Lexem(std::string({ expression[i] }), Operator, 0, priority));
        }
        else if (expression[i] == '-') {
            if (prev == '\0' || prev == '(' || prev == '[' || prev == '{' ||
                prev == '+' || prev == '-' || prev == '*' || prev == '/' || prev == '^') {
                int next_index = i + 1;
                while (next_index < expression.length() && expression[next_index] == ' ') {
                    next_index++;
                }
                if (next_index >= expression.length()) {
                    throw std::invalid_argument("Missing operand for unary minus!\n");
                }
                if (!((expression[next_index] >= '0' && expression[next_index] <= '9') ||
                        (expression[next_index] >= 'a' && expression[next_index] <= 'z') ||
                        expression[next_index] == '(' || expression[next_index] == '[' || expression[next_index] == '{')) {
                    throw std::invalid_argument("Missing operand for unary minus!\n");
                }
                lexems.push_back(Lexem("~", UnOperator, 0, 4));
            }
            else {
                bool isRightOperand = false;
                int next_index = i + 1;
                while (next_index < expression.length() && expression[next_index] == ' ') {
                    next_index++;
                }
                if (next_index < expression.length()) {
                    if ((expression[next_index] >= '0' && expression[next_index] <= '9') ||
                        (expression[next_index] >= 'a' && expression[next_index] <= 'z') ||
                        expression[next_index] == '(' || expression[next_index] == '[' || expression[next_index] == '{') {
                        isRightOperand = true;
                    }
                }
                if (!isRightOperand)
                    throw std::invalid_argument("Missing second operand in operation '-'\n");
                lexems.push_back(Lexem("-", Operator, 0, 1));
            }
        }
        else if ((expression[i] >= 'a' && expression[i] <= 'z') || (expression[i] >= 'A' && expression[i] <= 'Z')) {
            if (prev >= 'a' && prev <= 'z')
                throw std::invalid_argument("Missing operation between variables!\n");
            if (prev >= '0' && prev <= '9')
                throw std::invalid_argument("Missing operation between variable and number!\n");
            std::string word = extractVariableOrFunction(expression, i);

            int next_index = i + word.length();
            while (next_index < expression.length() && expression[next_index] == ' ') {
                next_index++;
            }
            if (next_index < expression.length() && expression[next_index] == '(') {
                if (word == "sin" || word == "cos" || word == "tg" || word == "Sin" || word == "Cos" || word == "Tg") {
                    double(*func)(double) = getFunction(word);
                    if (func != nullptr) {
                        lexems.push_back(Lexem(word, Function, 0, 5, func));
                    }
                    else {
                        throw std::invalid_argument("Unknown function: " + word + "\n");
                    }
                }
                else {
                    throw std::invalid_argument("Unknown function: " + word + "\n");
                }
            }
            else {
                lexems.push_back(Lexem(word, Variable));
            }

            i += word.length() - 1;
        }
        else if (expression[i] >= '0' && expression[i] <= '9') {
            if ((prev >= 'a' && prev <= 'z') || (prev >= 'A' && prev <= 'Z'))
                throw std::invalid_argument("Missing operation between variable and number!\n");
            std::string num = extractNumber(expression, i);
            lexems.push_back(Lexem(num, Constant, std::stod(num)));
            i += num.length() - 1;
        }
        prev = expression[i];
    }
    if (!brackets.is_empty())
        throw std::invalid_argument("Missing closed bracket!");
    return lexems;
}
std::string Parser::extractNumber(const std::string& expression, int startIndex) {
    std::string number;
    bool hasPoint = false;
    int i = startIndex;

    while (i < expression.length()) {
        if (expression[i] >= '0' && expression[i] <= '9') {
            number += expression[i];
        }
        else if (expression[i] == '.' && !hasPoint) {
            number += expression[i];
            hasPoint = true;
        }
        else {
            break;
        }
        i++;
    }

    if (!number.empty() && number.back() == '.')
        throw std::invalid_argument("Invalid number format: ends with point!\n");

    return number;
}

std::string Parser::extractVariableOrFunction(const std::string& expression, int index) {
    std::string word;
    int i = index;

    while (i < expression.length() && ((expression[i] >= 'a' && expression[i] <= 'z') ||
            (expression[i] >= 'A' && expression[i] <= 'Z') || (expression[i] >= '0' && expression[i] <= '9'))) {
        word += expression[i];
        i++;
    }

    return word;
}

double(*Parser::getFunction(const std::string name))(double) {
    if (name == "sin" || name == "Sin") {
        return [](double x) { return Sin(x).calculate(); };
    }
    else if (name == "cos" || name == "Cos") {
        return [](double x) { return Cos(x).calculate(); };
    }
    else if (name == "tg" || name == "Tg") {
        return [](double x) { return Tg(x).calculate(); };
    }
    return nullptr;
}
