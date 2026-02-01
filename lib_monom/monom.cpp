// Copyright 2026 Mary Maslennikova

#include "../lib_monom/monom.h"

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

Monom::~Monom() {}

const double Monom::get_coeff() const noexcept {
    return _coeff;
}
const int* Monom::get_powers() const noexcept {
    return _powers;
}

Monom& Monom::operator+=(const Monom& second) {  // нужна ли проверка на x, y, z?
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
Monom Monom::operator-() const {  // нужно ли менять сам объект?
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
    _coeff = second._coeff;
    for (int i = 0; i < VAR_COUNT; i++) {
        _powers[i] = second._powers[i];
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
bool Monom::operator>(const Monom& second) const noexcept {  // как именно сравнивать?
    for (int i = 0; i < VAR_COUNT; i++) {
        if (_powers[i] != second._powers[i]) {
            return _powers[i] > second._powers[i];
        }
    }
    return _coeff > second._coeff;
}
bool Monom::operator<(const Monom& second) const noexcept {
    if (*this == second) return false;
    return !(*this > second);
}


std::ostream& operator<<(std::ostream& os, const Monom& monom) {
    os << monom._coeff;
    for (int i = 0; i < VAR_COUNT; i++) {
        if (monom._powers[i] > 0) {
            switch (i)
            {
            case 0:
                os << 'x^' << monom._powers[i];
                break;
            case 1:
                os << 'y^' << monom._powers[i];
                break;
            case 2:
                os << 'z^' << monom._powers[i];
                break;
            default:
                break;
            }
        }
    }
    return os;
}
std::istream& operator>>(std::istream& is, Monom& monom) {
    return is;
}