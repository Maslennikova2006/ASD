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
std::string Parser::read_number(const std::string& str, size_t& ind) {
    std::string number = "";
    bool hasDecimal = false;

    if (ind < str.length() && str[ind] == '-') {
        number += str[ind];
        ind++;
    }

    while (ind < str.length()) {
        if (str[ind] >= '0' && str[ind] <= '9') {
            number += str[ind];
            ind++;
        }
        else if (str[ind] == '.' && !hasDecimal) {
            number += str[ind];
            hasDecimal = true;
            ind++;
        }
        else {
            break;
        }
    }
    return number;
}

int Parser::read_power(const std::string& str, size_t& ind) {
    ind = follow_the_line(str, ind);
    if (ind < str.length() && str[ind] == '^') {
        ind++;
        ind = follow_the_line(str, ind);
        std::string num = read_number(str, ind);
        if (!num.empty()) {
            return std::stoi(num);
        }
    }
    return 1;
}

Monom Parser::parse_monom(const std::string& str) {
    size_t ind = 0;
    Monom result;

    ind = follow_the_line(str, ind);

    if (ind < str.length()) {
        if (str[ind] == '-' || is_digit(str[ind])) {
            std::string numStr = read_number(str, ind);
            if (numStr == "-") {
                result.set_coeff(-1.0);
            }
            else {
                result.set_coeff(std::stod(numStr));
            }
        }
        else if (str[ind] == 'x' || str[ind] == 'y' || str[ind] == 'z') {
            result.set_coeff(1.0);
        }
        else {
            throw std::invalid_argument("Unexpected symbol at beginning");
        }
    }

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
            result.set_power(varIndex, power);
        }
    }

    return result;
}
std::string Parser::read_monom(std::string str, int& ind) {
    std::string monom = "";

    for (int i = ind; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9' || str[i] == ' ' || str[i] == '.' ||
            str[i] == 'x' || str[i] == 'y' || str[i] == 'z' || str[i] == '^')
            monom += str[i];
        else if ((str[i] == '+' || str[i] == '-') && monom != "")
            break;
        else if (str[i] != '+' && str[i] != '-')
            throw std::logic_error("There is no monome!");
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