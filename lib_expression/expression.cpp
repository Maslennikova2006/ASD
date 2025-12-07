// Copyright 2025 Mary Maslennikova

#include "../lib_expression/expression.h"
#include "../lib_parser/parser.h"
#include "../lib_stack/stack.h"
#include <iostream>


Expression::Expression() {
    _lexems = List<Lexem>();
    _polishRecord = List<Lexem>();
}
Expression::Expression(std::string& expr) {
    _lexems = Parser::parse(expr);
    _polishRecord = compilation_polishRecord(_lexems);
}
Expression::Expression(List<Lexem>& expr) {
    _lexems = expr;
    _polishRecord = compilation_polishRecord(expr);
}
Expression::Expression(const Expression& other) {
    _lexems = other._lexems;
    _polishRecord = other._polishRecord;
}

void Expression::set_variables(std::string name, double value) {
    bool found = false;
    auto lexem = _polishRecord.begin();
    for (lexem; lexem != _polishRecord.end(); lexem++) {
        if ((*lexem).name == name) {
            (*lexem).value = value;
            found = true;
        }
    }
    if (!found) {
        throw std::invalid_argument("No matching variables found!\n");
    }
}
List<Lexem> Expression::get_variables() {
    List<Lexem> variables;
    List<Lexem> unique_var;
    auto lexem = _polishRecord.begin();
    for (lexem; lexem != _polishRecord.end(); lexem++) {
        if ((*lexem).type == Variable) {
            bool exist = false;
            auto var = unique_var.begin();
            for (var; var != unique_var.end(); var++) {
                if ((*lexem).name == (*var).name) {
                    exist = true;
                    break;
                }
            }
            if (!exist) {
                variables.push_back(*lexem);
                unique_var.push_back(*lexem);
            }
        }
    }
    return variables;
}

double Expression::calculate() {
    Stack<double> values;
    auto lexem = _polishRecord.begin();
    for (lexem; lexem != _polishRecord.end(); lexem++) {
        switch ((*lexem).type) {
        case Constant:
        case Variable:
            if ((*lexem).value == DBL_MAX)
                throw std::invalid_argument("The value of the variable '" + (*lexem).name + "' is not set!\n");
            values.push((*lexem).value);
            break;

        case UnOperator: {
            if (values.is_empty())
                throw std::invalid_argument("Not enough operands for unary operator!\n");
            double val = values.top();
            values.pop();
            values.push(-val);
            break;
        }

        case Operator: {
            if (values.get_size() < 2)
                throw std::invalid_argument("Not enough operands for binary operator!\n");
            double b = values.top();
            values.pop();
            double a = values.top();
            values.pop();

            if ((*lexem).name == "+") values.push(a + b);
            else if ((*lexem).name == "-") values.push(a - b);
            else if ((*lexem).name == "*") values.push(a * b);
            else if ((*lexem).name == "/") {
                if (b == 0) throw std::invalid_argument("Division by zero!\n");
                values.push(a / b);
            }
            else if ((*lexem).name == "^") values.push(pow(a, b));
            break;
        }
        case Function: {
            if (values.is_empty())
                throw std::invalid_argument("Not enough operands for function!\n");
            double arg = values.top();
            values.pop();
            values.push((*lexem).function(arg));
            break;
        }

        default:
            throw std::invalid_argument("Unexpected lexem type in polish record: " + (*lexem).name);
        }
    }
    return values.top();
}

std::string Expression::to_string() {
    std::string str;
    auto lexem = _lexems.begin();
    for (lexem; lexem != _lexems.end(); lexem++) {
        str += (*lexem).name;
    }
    return str;
}

List<Lexem> Expression::compilation_polishRecord(const List<Lexem>& lexems) {
    List<Lexem> polishRecord;
    Stack<Lexem> operators;
    auto lexem = lexems.begin();
    for (lexem; lexem != lexems.end(); lexem++) {
        switch ((*lexem).type) {
        case Constant:
        case Variable:
            polishRecord.push_back(*lexem);
            break;
        case Function:
            operators.push(*lexem);
            break;
        case Operator:
        case UnOperator:
            while (!operators.is_empty() &&
                operators.top().type != OpenedBracket &&
                operators.top().priority >= (*lexem).priority) {
                polishRecord.push_back(operators.top());
                operators.pop();
            }
            operators.push(*lexem);
            break;
        case OpenedBracket:
            operators.push(*lexem);
            break;
        case ClosedBracket:
            while (!operators.is_empty() && operators.top().type != OpenedBracket) {
                polishRecord.push_back(operators.top());
                operators.pop();
            }
            if (!operators.is_empty() && operators.top().type == OpenedBracket) {
                operators.pop();
            }
            if (!operators.is_empty() && operators.top().type == Function) {
                polishRecord.push_back(operators.top());
                operators.pop();
            }
            break;
        default:
            break;
        }
    }
    while (!operators.is_empty()) {
        polishRecord.push_back(operators.top());
        operators.pop();
    }
    return polishRecord;
}
