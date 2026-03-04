// Copyright 2026 Mary Maslennikova

#include "../lib_parser/parser.h"
#include <string>

size_t Parser::follow_the_line(const std::string& str, size_t ind) {
    while (ind < str.length() && (str[ind] == ' ' || str[ind] == '*' || str[ind] == '+')) {
        ind++;
    }
    return ind;
}
bool Parser::is_digit(char symbol) {
    return (symbol >= '0' && symbol <= '9');
}
bool Parser::is_variable(char symbol) {
    return symbol == 'x' || symbol == 'y' || symbol == 'z';
}
std::string Parser::read_number(const std::string& str, size_t& ind) {
    std::string number = "";
    bool hasDecimal = false;

    if (ind >= str.length())
        throw std::invalid_argument("Unexpected end of string while reading number!");

    if (str[ind] == '-') {
        number += str[ind];
        ind++;
    }

    while (ind < str.length()) {
        if (is_digit(str[ind])) {
            number += str[ind];
            ind++;
        }
        else if (str[ind] == '.' && !hasDecimal) {
            number += str[ind];
            hasDecimal = true;
            ind++;
        }
        else break;
    }
    return number;
}

int Parser::read_power(const std::string& str, size_t& ind) {
    ind = follow_the_line(str, ind);
    if (ind < str.length() && str[ind] == '^') {
        ind++;
        ind = follow_the_line(str, ind);
        if (ind >= str.length() || !is_digit(str[ind]))
            throw std::invalid_argument("Expected number after '^'!");
        std::string num = read_number(str, ind);
        if (!num.empty()) {
            int power = std::stoi(num);
            if (power < 0)
                throw std::invalid_argument("Power cannot be negative!");
            return power;
        }
    }
    return 1;
}

Monom Parser::parse_monom(const std::string& str) {
    size_t ind = 0;
    Monom result;

    ind = follow_the_line(str, ind);

    if (ind >= str.length())
        throw std::invalid_argument("Unexpected end of monom!");
    if (str[ind] == '+' || str[ind] == '/' || str[ind] == '*')
        throw std::invalid_argument(std::string("Unexpected symbol '") + str[ind] + "' at beginning!");

    if (str[ind] == '-' || is_digit(str[ind])) {
        bool isMinus = (str[ind] == '-');
        std::string num = read_number(str, ind);

        if (num == "-")
            result.set_coeff(isMinus ? -1.0 : 1.0);
        else
            result.set_coeff(std::stod(num));
    }
    else if (is_variable(str[ind])) {
        result.set_coeff(1.0);
    }
    else
        throw std::invalid_argument("Unexpected symbol at beginning!");

    while (ind < str.length()) {
        ind = follow_the_line(str, ind);
        if (ind >= str.length()) break;

        int varIndex = -1;
        if (str[ind] == 'x') varIndex = 0;
        else if (str[ind] == 'y') varIndex = 1;
        else if (str[ind] == 'z') varIndex = 2;
        else break;

        ind++;

        int power = read_power(str, ind);
        if (varIndex >= 0) {
            if (power < 0)
                throw std::invalid_argument("The power cannot be negative!");
            result.set_power(varIndex, power);
        }

        ind = follow_the_line(str, ind);
        if (ind < str.length() && str[ind] == '^')
            throw std::invalid_argument("Invalid power syntax!");
    }
    return result;
}
std::string Parser::read_monom(std::string str, int ind) {
    std::string monom = "";

    for (int i = ind; i < str.length(); i++) {
        if (is_digit(str[i]) || is_variable(str[i]) ||
            str[i] == ' ' || str[i] == '.' || str[i] == '^')
            monom += str[i];
        else if ((str[i] == '+' || str[i] == '-') && monom != "")
            break;
        else
            throw std::logic_error("Invalid symbol!");
    }
    return monom;
}
List<Monom> Parser::parse_polynom(const std::string& str) {
    std::string monom;
    int i = 0;
    List<Monom> res;
    bool isMinus = false;

    while (i < str.length()) {
        i = follow_the_line(str, i);
        if (str[i] == '-') {
            isMinus = true;
            i++;
            continue;
        }

        monom = read_monom(str, i);
        i += monom.length();

        Monom mon(monom);
        if (isMinus) {
            mon.set_coeff((-1) * mon.get_coeff());
            isMinus = false;
        }

        if (res.is_empty()) {
            res.push_back(mon);
            continue;
        }

        Node<Monom>* cur = res.head();
        bool isInserted = false;
        int j = 0;
        while (cur != nullptr) {
            if (mon > cur->value) {
                res.insert(j, mon);
                isInserted = true;
                break;
            }
            else if (mon == cur->value) {
                cur->value += mon;
                isInserted = true;
                break;
            }
            cur = cur->next;
            j++;
        }
        if (!isInserted)
            res.push_back(mon);
    }
    return res;
}