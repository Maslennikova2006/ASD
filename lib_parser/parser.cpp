// Copyright 2025 Mary Maslennikova

#include "../lib_parser/parser.h"
#include "../lib_stack/stack.h"
#include "../lib_functions/functions.h"

int Parser::follow_the_line(size_t ind, const std::string& expr) {
    while (ind < expr.length() && expr[ind] == ' ') {
        ind++;
    }
    return ind;
}
bool Parser::is_opened_bracket(char symbol) {
    return (symbol == '(' || symbol == '[' || symbol == '{');
}
bool Parser::is_closed_bracket(char symbol) {
    return (symbol == ')' || symbol == ']' || symbol == '}');
}
bool Parser::is_operation(char symbol) {
    return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^');
}
bool Parser::is_letters(char symbol) {
    return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z');
}
bool Parser::is_digit(char symbol) {
    return (symbol >= '0' && symbol <= '9');
}

List<Lexem> Parser::parse(const std::string& expression) {
    List<Lexem> lexems;
    Stack<char> brackets(expression.length());
    char prev = '\0';
    bool expectOperand = true;
    size_t i = 0;
    while (i < expression.length()) {
        i = follow_the_line(i, expression);
        if (i >= expression.length()) break;

        if (expectOperand) {
            if (is_letters(expression[i])) {
                if (is_digit(prev) || is_letters(prev))
                    throw std::invalid_argument(print_error_location(i) + "Missing operation between variables or numbers!\n");

                parse_variable_or_function(i, expression, lexems, brackets, expectOperand);
            }
            else if (is_opened_bracket(expression[i])) {
                if (is_digit(prev) || is_letters(prev) || is_closed_bracket(prev))
                    throw std::invalid_argument(print_error_location(i) + "An operation is missing between the opening bracket and the number, variable or closing bracket!\n");
                brackets.push(expression[i]);
                lexems.push_back(Lexem(std::string({ expression[i] }), OpenedBracket));

                int next_index = i + 1;
                next_index = follow_the_line(next_index, expression);
                if (next_index < expression.length()) {
                    char symbol = expression[next_index];
                    if ((is_operation(symbol) && symbol != '-') || is_closed_bracket(symbol))
                        throw std::invalid_argument(print_error_location(next_index) + "An operation or a closing bracket cannot follow an opening bracket!\n");
                }
            }
            else if (expression[i] == '|') {
                brackets.push('|');
                lexems.push_back(Lexem("abs", Function, DBL_MAX, function_priority, Functions::abs));
                lexems.push_back(Lexem("(", OpenedBracket));

                int next_index = i + 1;
                next_index = follow_the_line(next_index, expression);
                if (next_index < expression.length()) {
                    char symbol = expression[next_index];
                    if ((is_operation(symbol) && symbol != '-') || is_closed_bracket(symbol))
                        throw std::invalid_argument(print_error_location(next_index) + "An operation or a closing bracket cannot follow an opening bracket!\n");
                }
            }
            else if (expression[i] == '-' && (prev == '\0' || is_opened_bracket(prev) || prev == '|')) {
                int next_index = i + 1;
                next_index = follow_the_line(next_index, expression);
                char symbol = expression[next_index];
                if (next_index >= expression.length() || !(is_digit(symbol) || is_letters(symbol) || is_opened_bracket(symbol) || symbol == '|'))
                    throw std::invalid_argument(print_error_location(next_index) + "Missing operand for unary minus!\n");
                lexems.push_back(Lexem("~", UnOperator, DBL_MAX, unary_priority));
            }
            else if (is_digit(expression[i])) {
                if (is_letters(prev))
                    throw std::invalid_argument(print_error_location(i) + "Missing operation between variable and number!\n");
                std::string num = extract_number(expression, i);
                lexems.push_back(Lexem(num, Constant, std::stod(num)));
                i += num.length() - 1;
                expectOperand = false;
            }
            else
                throw std::invalid_argument(print_error_location(i) + "Missing operand!\n");
        }
        else {
            if (is_closed_bracket(expression[i])) {
                if (brackets.is_empty())
                    throw std::invalid_argument(print_error_location(i) + "Missing opened bracket!\n");

                char expectedBracket = set_expectedBracket(expression[i]);
                if (brackets.top() == expectedBracket) {
                    brackets.pop();
                    lexems.push_back(Lexem(std::string({ expression[i] }), ClosedBracket));
                }
                else
                    throw std::invalid_argument(print_error_location(i) + "A different type of bracket was expected: '" + std::string(1, expectedBracket) + "'!\n");

                if (is_operation(prev))
                    throw std::invalid_argument(print_error_location(i) + "The operation cannot be performed before the closing bracket!\n");
            }
            else if (expression[i] == '|') {
                if (brackets.is_empty() || brackets.top() != '|')
                    throw std::invalid_argument(print_error_location(i) + "Missing opened abs bracket!\n");

                brackets.pop();
                lexems.push_back(Lexem(")", ClosedBracket));

                if (is_operation(prev))
                    throw std::invalid_argument(print_error_location(i) + "The operation cannot be performed before the closing abs!\n");
            }
            else if (is_operation(expression[i])) {
                bool isRightOperand = false;
                int next_index = i + 1;
                next_index = follow_the_line(next_index, expression);
                if (next_index < expression.length()) {
                    char symbol = expression[next_index];
                    if (is_digit(symbol) || is_letters(symbol) || is_opened_bracket(symbol) || symbol == '|') {
                        isRightOperand = true;
                    }
                }
                if (!isRightOperand)
                    throw std::logic_error(print_error_location(next_index) + "Missing second operand in operation '" + std::string(1, expression[i]) + "'!\n");

                int priority = set_priority(expression[i]);
                lexems.push_back(Lexem(std::string({ expression[i] }), Operator, DBL_MAX, priority));
                expectOperand = true;
            }
            else {
                throw std::logic_error(print_error_location(i) + "Missing operation!\n");
            }
        }

        prev = expression[i];
        i++;
    }
    if (!brackets.is_empty())
        throw std::invalid_argument(print_error_location(i) + "Missing closed bracket!\n");
    return lexems;
}
std::string Parser::extract_number(const std::string& expression, int index) {
    std::string number;
    int i = index;

    while (i < expression.length()) {
        if (expression[i] >= '0' && expression[i] <= '9') {
            number += expression[i];
        }
        else {
            break;
        }
        i++;
    }
    return number;
}

std::string Parser::extract_variable_or_function(const std::string& expression, int index) {
    std::string str;
    int i = index;

    while (i < expression.length() && (is_letters(expression[i]) || is_digit(expression[i]) || expression[i] == '_')) {
        str += expression[i];
        i++;
    }
    return str;
}

double(*Parser::get_function(const std::string name))(double) {
    if (name == "sin" || name == "Sin") {
        return Functions::sin;
    }
    else if (name == "cos" || name == "Cos") {
        return Functions::cos;
    }
    else if (name == "tg" || name == "Tg") {
        return Functions::tg;
    }
    return nullptr;
}

std::string Parser::print_error_location(size_t ind) {
    std::string error_location = std::string(19 + ind, ' ') + "^\n";
    std::string error = "Error in function 'Parser::parse()' at " + std::to_string(ind + 1) + " symbol: ";
    return error_location + error;
}

int Parser::set_priority(char operation) {
    switch (operation) {
    case '+': case '-':
        return addition_priority;
    case '*': case '/':
        return multiplication_priority;
    case '^':
        return pow_priority;
    default:
        return -1;
    }
}
char Parser::set_expectedBracket(char bracket) {
    switch (bracket) {
    case ')':
        return '(';
    case ']':
        return '[';
    case '}':
        return '{';
    }
}

void Parser::parse_variable_or_function(size_t& ind, const std::string& expr, List<Lexem>& lexems, Stack<char>& brackets, bool& expectOperand) {
    std::string str = extract_variable_or_function(expr, ind);
    int next_index = ind + str.length();
    next_index = follow_the_line(next_index, expr);

    if (next_index < expr.length() && is_opened_bracket(expr[next_index])) {
        if (str == "sin" || str == "cos" || str == "tg" ||
            str == "Sin" || str == "Cos" || str == "Tg") {
            double(*func)(double) = get_function(str);
            if (func != nullptr) {
                lexems.push_back(Lexem(str, Function, DBL_MAX, function_priority, func));
                ind = next_index;
                if (!is_opened_bracket(expr[ind]))
                    throw std::invalid_argument(print_error_location(ind) + "Expected opening bracket after function!\n");
                brackets.push(expr[ind]);
                lexems.push_back(Lexem(std::string({ expr[ind] }), OpenedBracket));

                next_index = ind + 1;
                next_index = follow_the_line(next_index, expr);
                if (next_index < expr.length()) {
                    char symbol = expr[next_index];
                    if ((is_operation(symbol) && symbol != '-') || is_closed_bracket(symbol))
                        throw std::invalid_argument(print_error_location(next_index) + "An operation or a closing bracket cannot follow an opening bracket!\n");
                }
            }
            else
                throw std::invalid_argument(print_error_location(ind) + "Unknown function: " + str + "\n");
        }
    }
    else {
        bool validVariable = false;
        if (str.length() == 1 && is_letters(str[0]))
            validVariable = true;
        else if (str.length() > 1 && str[1] == '_') {
            if (is_letters(str[0]) && is_digit(str[2]))
                validVariable = true;
        }
        if (!validVariable) {
            for (size_t j = 1; j < str.length(); j++) {
                if (is_letters(str[j]))
                    throw std::logic_error(print_error_location(ind + j) + "Missing operation!\n");
            }
            throw std::invalid_argument(print_error_location(ind) + "Invalid variable name!\n");
        }
        lexems.push_back(Lexem(str, Variable));
        ind += str.length() - 1;
        expectOperand = false;
    }
}
