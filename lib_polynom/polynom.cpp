// Copyright 2026 Mary Maslennikova

#include "../lib_polynom/polynom.h"
#include "../lib_parser/parser.h"
#include <iostream>

Polynom::Polynom() {
    Monom zero;
    _polynom.push_back(zero);
}
Polynom::Polynom(const Monom& monom) : _polynom() {
    _polynom.push_back(monom);
}
Polynom::Polynom(const Polynom& other) {
    _polynom = List<Monom>(other._polynom);
}
Polynom::Polynom(const std::string& str) : _polynom() {
    _polynom = Parser::parse_polynom(str);
}

Polynom::~Polynom() {}

List<Monom> Polynom::get_monoms() const noexcept {
    return _polynom;
}

Polynom& Polynom::operator+=(const Polynom& second) {
    List<Monom> res;
    auto it1 = _polynom.begin();
    auto it2 = second._polynom.begin();

    while (it1 != nullptr && it2 != nullptr) {
        if (*it1 > *it2) {
            res.push_back(*it1);
            it1++;
        }
        else if (*it1 < *it2) {
            res.push_back(*it2);
            it2++;
        }
        else {
            Monom sum = *it1 + *it2;
            if (sum.get_coeff() != 0) {
                res.push_back(sum);
            }
            it1++;
            it2++;
        }
    }

    while (it1 != nullptr) {
        res.push_back(*it1);
        it1++;
    }

    while (it2 != nullptr) {
        res.push_back(*it2);
        it2++;
    }

    _polynom = res;
    return *this;
}
Polynom& Polynom::operator-=(const Polynom& second) {
    List<Monom> res;
    auto it1 = _polynom.begin();
    auto it2 = second._polynom.begin();

    while (it1 != nullptr && it2 != nullptr) {
        if (*it1 > *it2) {
            res.push_back(*it1);
            it1++;
        }
        else if (*it1 < *it2) {
            res.push_back(-(*it2));
            it2++;
        }
        else {
            Monom sub = *it1 - *it2;
            if (sub.get_coeff() != 0) {
                res.push_back(sub);
            }
            it1++;
            it2++;
        }
    }

    while (it1 != nullptr) {
        res.push_back(*it1);
        it1++;
    }

    while (it2 != nullptr) {
        res.push_back(-(*it2));
        it2++;
    }

    _polynom = res;
    return *this;
}
Polynom& Polynom::operator*=(const Polynom& second) {
    Polynom res;
    res._polynom.pop_back();
    auto it1 = _polynom.begin();
    while (it1 != nullptr) {
        auto it2 = second._polynom.begin();
        while (it2 != nullptr) {
            res += (*it1) * (*it2);
            it2++;
        }
        it1++;
    }
    *this = res;
    return *this;
}

Polynom& Polynom::operator+=(const double scalar) {
    if (scalar == 0.0)
        return *this;
    Monom monom(scalar);
    *this += monom;
    return *this;
}
Polynom& Polynom::operator-=(const double scalar) {
    if (scalar == 0.0)
        return *this;
    Monom monom(scalar);
    *this -= monom;
    return *this;
}
Polynom& Polynom::operator*=(const double scalar) {
    if (scalar == 0.0) {
        _polynom.clear();
        Monom zero;
        _polynom.push_back(zero);
        return *this;
    }
    List<Monom> res;
    auto it = _polynom.begin();
    while (it != nullptr) {
        res.push_back((*it) * scalar);
        it++;
    }
    _polynom = res;
    return *this;
}
Polynom& Polynom::operator/=(const double scalar) {
    if (scalar == 0.0)
        throw std::invalid_argument("You can't divide by zero!");

    List<Monom> res;
    auto it = _polynom.begin();
    while (it != nullptr) {
        res.push_back((*it) / scalar);
        it++;
    }
    _polynom = res;
    return *this;
}

Polynom Polynom::operator+(const Polynom& second) const {
    Polynom res(*this);
    res += second;
    return res;
}
Polynom Polynom::operator-(const Polynom& second) const {
    Polynom res(*this);
    res -= second;
    return res;
}
Polynom Polynom::operator-() const {
    Polynom res;
    res._polynom.pop_back();
    auto it = _polynom.begin();
    while (it != nullptr) {
        res._polynom.push_back(-(*it));
        it++;
    }
    return res;
}
Polynom Polynom::operator*(const Polynom& second) const {
    Polynom res(*this);
    res *= second;
    return res;
}

Polynom Polynom::operator+(const double scalar) const {
    Polynom res(*this);
    res += scalar;
    return res;
}
Polynom Polynom::operator-(const double scalar) const {
    Polynom res(*this);
    res -= scalar;
    return res;
}
Polynom Polynom::operator*(const double scalar) const {
    Polynom res(*this);
    res *= scalar;
    return res;
}
Polynom Polynom::operator/(const double scalar) const {
    Polynom res(*this);
    res /= scalar;
    return res;
}

Polynom& Polynom::operator+=(const Monom& monom) {
    if (monom.get_coeff() == 0.0)
        return *this;
    List<Monom> res;
    auto it = _polynom.begin();
    bool isInserted = false;

    while (it != nullptr) {
        if (*it == monom) {
            Monom sum = *it + monom;
            res.push_back(sum);
            isInserted = true;
            it++;
        }
        else if (*it < monom && !isInserted) {
            res.push_back(monom);
            res.push_back(*it);
            isInserted = true;
            it++;
        }
        else {
            res.push_back(*it);
            it++;
        }
    }

    if (!isInserted) {
        res.push_back(monom);
    }

    _polynom = res;
    return *this;
}
Polynom& Polynom::operator-=(const Monom& monom) {
    if (monom.get_coeff() == 0.0)
        return *this;
    List<Monom> res;
    auto it = _polynom.begin();
    bool isInserted = false;

    while (it != nullptr) {
        if (*it == monom) {
            Monom sub = *it - monom;
            if (sub.get_coeff() != 0) {
                res.push_back(sub);
                isInserted = true;
            }
            it++;
        }
        else if (*it < monom && !isInserted) {
            res.push_back(-monom);
            res.push_back(*it);
            isInserted = true;
            it++;
        }
        else {
            res.push_back(*it);
            it++;
        }
    }

    if (!isInserted) {
        res.push_back(-monom);
    }

    _polynom = res;
    return *this;
}
Polynom& Polynom::operator*=(const Monom& monom) {
    if (monom.get_coeff() == 0.0) {
        _polynom.clear();
        Monom zero;
        _polynom.push_back(zero);
        return *this;
    }
    auto it = _polynom.begin();
    while (it != nullptr) {
        (*it) *= monom;
        it++;
    }
    return *this;
}
Polynom& Polynom::operator/=(const Monom& monom) {
    if (monom.get_coeff() == 0)
        throw std::invalid_argument("You can't divide by zero!");
    auto it = _polynom.begin();
    while (it != nullptr) {
        (*it) /= monom;
        it++;
    }
    return *this;
}

Polynom Polynom::operator+(const Monom& monom) const {
    Polynom res(*this);
    res += monom;
    return res;
}
Polynom Polynom::operator-(const Monom& monom) const {
    Polynom res(*this);
    res -= monom;
    return res;
}
Polynom Polynom::operator*(const Monom& monom) const {
    Polynom res(*this);
    res *= monom;
    return res;
}
Polynom Polynom::operator/(const Monom& monom) const {
    Polynom res(*this);
    res /= monom;
    return res;
}

bool Polynom::operator==(const Polynom& second) const noexcept {
    auto it1 = _polynom.begin();
    auto it2 = second._polynom.begin();
    if (_polynom.get_count() != second._polynom.get_count())
        return false;
    while (it1 != nullptr && it2 != nullptr) {
        if ((*it1) != (*it2) || (((*it1) == (*it2)) &&
            ((*it1).get_coeff() != (*it2).get_coeff())))
            return false;
        it1++;
        it2++;
    }
    return true;
}
bool Polynom::operator!=(const Polynom& second) const noexcept {
    return !(*this == second);
}
bool Polynom::operator>(const Polynom& second) const noexcept {
    auto it1 = _polynom.begin();
    auto it2 = second._polynom.begin();
    while (it1 != nullptr && it2 != nullptr) {
        if ((*it1) < (*it2))
            return false;
        else if ((*it1) == (*it2)) {
            if ((*it1).get_coeff() > (*it2).get_coeff())
                return true;
            else if ((*it1).get_coeff() < (*it2).get_coeff())
                return false;
            it1++;
            it2++;
        }
        else
            return true;
    }
    if (it1 == nullptr)
        return false;
    return true;
}
bool Polynom::operator<(const Polynom& second) const noexcept {
    return second > *this;
}

Polynom& Polynom::operator=(const Polynom& second) {
    if (this != &second) {
        _polynom = second._polynom;
    }
    return *this;
}

double Polynom::calculate(double x, double y, double z) const noexcept {
    double res = 0.0;
    auto it = _polynom.begin();
    while (it != nullptr) {
        res += (*it).calculate(x, y, z);
        it++;
    }
    return res;
}
std::string Polynom::toString() const noexcept {
    std::string str = "";
    auto it = _polynom.begin();
    bool isFirst = true;
    while (it != nullptr) {
        if (!isFirst && (*it).get_coeff() > 0)
            str += "+";
        str += (*it).toString();
        it++;
        isFirst = false;
    }
    return str;
}

std::ostream& operator<<(std::ostream& os, const Polynom& polynom) {
    os << polynom.toString();
    return os;
}
std::istream& operator>>(std::istream& is, Polynom& polynom) {
    std::string str;
    is >> str;
    polynom._polynom = Parser::parse_polynom(str);
    return is;
}

Polynom operator+(const Monom& monom, const Polynom& polynom) {
    return polynom + monom;
}
Polynom operator-(const Monom& monom, const Polynom& polynom) {
    return monom + (-polynom);
}
Polynom operator*(const Monom& monom, const Polynom& polynom) {
    return polynom * monom;
}

Polynom operator*(const double scalar, const Polynom& polynom) {
    return polynom * scalar;
}