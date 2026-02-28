// Copyright 2026 Mary Maslennikova

#include "../lib_monom/monom.h"
#include "../lib_parser/parser.h"
#include <iostream>
#include <string>

Monom::Monom(double coeff, const int* powers) {
    _coeff = coeff;
    if (powers) {
        for (int i = 0; i < VAR_COUNT; i++) {
            _powers[i] = powers[i];
        }
    }
    else {
        for (int i = 0; i < VAR_COUNT; i++) {
            _powers[i] = 0;
        }
    }
}
Monom::Monom(const Monom& other) {
    _coeff = other._coeff;
    for (int i = 0; i < VAR_COUNT; i++) {
        _powers[i] = other._powers[i];
    }
}
Monom::Monom(const std::string& str) : Monom(Parser::parse_monom(str)) {
}

Monom::~Monom() {}

const double Monom::get_coeff() const noexcept {
    return _coeff;
}
const int* Monom::get_powers() const noexcept {
    return _powers;
}

void Monom::set_coeff(double coeff) noexcept {
    _coeff = coeff;
}
void Monom::set_power(int ind, int value) noexcept {
    _powers[ind] = value;
}

Monom& Monom::operator+=(const Monom& second) {
    if (*this != second)
        throw std::logic_error("You can't add dissimilar monoms!");
    _coeff += second._coeff;
    return *this;
}
Monom& Monom::operator-=(const Monom& second) {
    if (*this != second)
        throw std::logic_error("You can't subtract dissimilar monoms!");
    _coeff -= second._coeff;
    return *this;
}
Monom& Monom::operator*=(const Monom& second) {
    _coeff *= second._coeff;
    for (int i = 0; i < VAR_COUNT; i++) {
        _powers[i] += second._powers[i];
    }
    return *this;
}
Monom& Monom::operator/=(const Monom& second) {
    if (second._coeff == 0)
        throw std::invalid_argument("Division by zero monom!");
    _coeff /= second._coeff;
    for (int i = 0; i < VAR_COUNT; i++) {
        _powers[i] -= second._powers[i];
    }
    return *this;
}
Monom& Monom::operator*=(const double scalar) {
    _coeff *= scalar;
    return *this;
}
Monom& Monom::operator/=(const double scalar) {
    if (scalar == 0)
        throw std::invalid_argument("Division by zero monom!");
    _coeff /= scalar;
    return *this;
}

Monom Monom::operator+(const Monom& second) const {
    Monom res(*this);
    res += second;
    return res;
}
Monom Monom::operator-(const Monom& second) const {
    Monom res(*this);
    res -= second;
    return res;
}
Monom Monom::operator-() const {
    Monom res(*this);
    res._coeff = -_coeff;
    return res;
}
Monom Monom::operator*(const Monom& second) const {
    Monom res(*this);
    res *= second;
    return res;
}
Monom Monom::operator/(const Monom& second) const {
    Monom res(*this);
    res /= second;
    return res;
}
Monom Monom::operator*(const double scalar) {
    Monom res(*this);
    res *= scalar;
    return res;
}
Monom Monom::operator/(const double scalar) {
    Monom res(*this);
    res /= scalar;
    return res;
}

Monom& Monom::operator=(const Monom& second) {
    if (this != &second) {
        _coeff = second._coeff;
        for (int i = 0; i < VAR_COUNT; i++) {
            _powers[i] = second._powers[i];
        }
    }
    return *this;
}

bool Monom::operator==(const Monom& second) const noexcept {
    bool isSimilar = true;
    for (int i = 0; i < VAR_COUNT; i++) {
        isSimilar &= (_powers[i] == second._powers[i]);
    }
    return isSimilar;
}
bool Monom::operator!=(const Monom& second) const noexcept {
    return !(*this == second);
}
bool Monom::operator>(const Monom& second) const noexcept {
    for (int i = 0; i < VAR_COUNT; i++) {
        if (_powers[i] != second._powers[i]) {
            return _powers[i] > second._powers[i];
        }
    }
    return false;
}
bool Monom::operator<(const Monom& second) const noexcept {
    if (*this == second) return false;
    return !(*this > second);
}

double Monom::calculate(double x, double y, double z) const noexcept {
    double res = _coeff * pow(x, _powers[0]) * pow(y, _powers[1]) * pow(z, _powers[2]);
    return res;
}
std::string Monom::toString() const noexcept {
    std::string str = std::to_string(_coeff);
    for (int i = 0; i < VAR_COUNT; i++) {
        if (_powers[i] > 0) {
            switch (i) {
            case 0:
                str += "x";
                break;
            case 1:
                str += "y";
                break;
            case 2:
                str += "z";
                break;
            }
            if (_powers[i] > 1) {
                str += "^";
                str += std::to_string(_powers[i]);
            }
        }
    }
    return str;
}

std::ostream& operator<<(std::ostream& os, const Monom& monom) {
    os << monom.toString();
    return os;
}
std::istream& operator>>(std::istream& is, Monom& monom) {
    std::string str;
    is >> str;
    monom = Parser::parse_monom(str);
    return is;
}

Monom operator*(const double scalar, const Monom& monom) {
    return monom * scalar;
}