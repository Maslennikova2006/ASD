// Copyright 2025 Mary Maslennikova

#include "../lib_expression/expression.h"
#include "../lib_parser/parser.h"
#include "../lib_stack/stack.h"
#include <iostream>

Expression::Expression(std::string& expr) {
    try {
        _lexems = Parser::parse(expr);
    }
    catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
    _polishRecord = Parser::compilationPolishRecord(_lexems);
    for (auto& l : _lexems) {
        std::cout << l.name << " ";
    }
    std::cout << std::endl;
}
Expression::Expression(List<Lexem>& expr) {
    _lexems = expr;  // нужны ли проверки на корректность?
    _polishRecord = Parser::compilationPolishRecord(expr);
}
Expression::Expression(const Expression& other) {
    _lexems = other._lexems;
    _polishRecord = other._polishRecord;
}

void Expression::set_variables(std::string name, double value) {
    bool found = false;
    for (auto& lexem : _polishRecord) {
        if (lexem.name == name) {
            lexem.value = value;
            found = true;
        }
    }

    if (!found) {
        throw std::invalid_argument("No matching variables found!\n");
    }
}

double Expression::calculate() {
    Stack<double> values(_lexems.get_count());

    for (auto& lexem : _polishRecord) {
        switch (lexem.type) {
        case Constant:
        case Variable: {
            values.push(lexem.value);
            break;
        }

        case UnOperator: {
            double val = values.top();
            values.pop();
            values.push(-val);
            break;
        }

        case Operator: {
            double b = values.top();
            values.pop();
            double a = values.top();
            values.pop();

            if (lexem.name == "+") values.push(a + b);
            else if (lexem.name == "-") values.push(a - b);
            else if (lexem.name == "*") values.push(a * b);
            else if (lexem.name == "/") {
                if (b == 0) throw std::invalid_argument("Division by zero");
                values.push(a / b);
            }
            else if (lexem.name == "^") {
                values.push(pow(a, b));
            }
            break;
        }

        case Function: {
            double arg = values.top();
            values.pop();
            values.push(lexem.function(arg));
            break;
        }

        default:
            throw std::invalid_argument("Unexpected lexem type in polish record: " + lexem.name);
        }
    }

    return values.top();
}
