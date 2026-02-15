// Copyright 2026 Mary Maslennikova

#include "../lib_polynom/polynom.h"

Polynom::Polynom() {
    Monom zero;
    _polynom.push_back(zero);
}
Polynom::Polynom(const Monom& monom) {
    _polynom.push_back(monom);
}
Polynom::Polynom(const Polynom& other) {
    _polynom = List<Monom>(other._polynom);
}

Polynom::~Polynom() {}

Polynom& Polynom::operator+=(const Polynom& second) {
    List<Monom> res;
    Node<Monom>* i = _polynom.head();
    Node<Monom>* j = second._polynom.head();
    while (i != nullptr && j != nullptr) {
        if (i->value > j->value) {
            res.push_back(i->value);
            i = i->next;
        }
        else if (i->value < j->value) {
            res.push_back(j->value);
            j = j->next;
        }
        else {
            Monom sum = i->value + j->value;
            if (sum.get_coeff() != 0) {
                res.push_back(sum);
            }
            i = i->next;
            j = j->next;
        }
    }
    while (i != nullptr) {
        res.push_back(i->value);
        i = i->next;
    }
    while (j != nullptr) {
        res.push_back(j->value);
        j = j->next;
    }
    _polynom = res;
    return *this;
}
Polynom& Polynom::operator-=(const Polynom& second) {
    List<Monom> res;
    Node<Monom>* i = _polynom.head();
    Node<Monom>* j = second._polynom.head();
    while (i != nullptr && j != nullptr) {
        if (i->value > j->value) {
            res.push_back(i->value);
            i = i->next;
        }
        else if (i->value < j->value) {
            res.push_back(j->value);
            j = j->next;
        }
        else {
            Monom sub = i->value - j->value;
            if (sub.get_coeff() != 0) {
                res.push_back(sub);
            }
            i = i->next;
            j = j->next;
        }
    }
    while (i != nullptr) {
        res.push_back(i->value);
        i = i->next;
    }
    while (j != nullptr) {
        res.push_back(j->value);
        j = j->next;
    }
    _polynom = res;
    return *this;
}
Polynom& Polynom::operator*=(const Polynom& second) {  // если после умножение появились подобные?
    List<Monom> res;
    Node<Monom>* i = _polynom.head();
    while (i != nullptr) {
        Node<Monom>* j = second._polynom.head();
        while (j != nullptr) {
            Monom mul = i->value * j->value;
            res.push_back(mul);
            j = j->next;
        }
        i = i->next;
    }
    _polynom = res;
    return *this;
}
Polynom& Polynom::operator*=(const double scalar) {
    if (scalar == 0) {
        _polynom.clear();
        return *this;
    }
    List<Monom> res;
    Node<Monom>* i = _polynom.head();
    while (i != nullptr) {
        Monom mul = i->value * scalar;
        res.push_back(mul);
        i = i->next;
    }
    _polynom = res;
    return *this;
}
Polynom& Polynom::operator/=(const double scalar) {
    if (scalar == 0)
        throw std::invalid_argument("You can't divide by zero!");
    List<Monom> res;
    Node<Monom>* i = _polynom.head();
    while (i != nullptr) {
        Monom mul = i->value / scalar;
        res.push_back(mul);
        i = i->next;
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
    Node<Monom>* i = _polynom.head();
    while (i != nullptr) {
        res._polynom.push_back(-(i->value));
        i = i->next;
    }
    return res;
}
Polynom Polynom::operator*(const Polynom& second) const {
    Polynom res(*this);
    res *= second;
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
    List<Monom> res;
    Node<Monom>* i = _polynom.head();
    bool isInserted = false;
    while (i != nullptr) {
        if (i->value == monom) {
            Monom sum = i->value + monom;
            res.push_back(sum);
            isInserted = true;
            i = i->next;
        }
        else if (i->value < monom && !isInserted) {
            res.push_back(monom);
            res.push_back(i->value);
            isInserted = true;
            i = i->next;
        }
        else {
            res.push_back(i->value);
            i = i->next;
        }
    }
    if (!isInserted)
        res.push_back(monom);
    _polynom = res;
    return *this;
}
Polynom& Polynom::operator-=(const Monom& monom) {  // ?
    List<Monom> res;
    Node<Monom>* i = _polynom.head();
    bool isInserted = false;
    while (i != nullptr) {
        if (i->value == monom) {
            Monom sub = i->value - monom;  // не добавлять если коэфф стал 0
            res.push_back(sub);
            isInserted = true;
            i = i->next;
        }
        else if (i->value < monom && !isInserted) {
            res.push_back(-monom);
            res.push_back(i->value);
            isInserted = true;
            i = i->next;
        }
        else {
            res.push_back(i->value);
            i = i->next;
        }
    }
    if (!isInserted)
        res.push_back(-monom);
    _polynom = res;
    return *this;
}
Polynom& Polynom::operator*=(const Monom& monom) {
    Node<Monom>* i = _polynom.head();
    while (i != nullptr) {
        i->value = i->value * monom;
        i = i->next;
    }
    return *this;
}
Polynom& Polynom::operator/=(const Monom& monom) {  // проверить на 0
    Node<Monom>* i = _polynom.head();
    while (i != nullptr) {
        i->value = i->value / monom;
        i = i->next;
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
    Node<Monom>* i = _polynom.head();
    Node<Monom>* j = second._polynom.head();
    if (_polynom.get_count() != second._polynom.get_count())
        return false;
    while (i != nullptr && j != nullptr) {
        if (i->value != j->value)
            return false;
        i = i->next;
        j = j->next;
    }
    return true;
}
bool Polynom::operator!=(const Polynom& second) const noexcept {
    return !(*this == second);
}
bool Polynom::operator>(const Polynom& second) const noexcept {
    Node<Monom>* i = _polynom.head();
    Node<Monom>* j = second._polynom.head();
    while (i != nullptr && j != nullptr) {
        if (i->value < j->value)
            return false;
        else if (i->value == j->value) {
            if (i->value.get_coeff() > j->value.get_coeff())
                return true;
            else if (i->value.get_coeff() < j->value.get_coeff())
                return false;
            i = i->next;
            j = j->next;
        }
        else
            return true;
    }
    if (i == nullptr)
        return false;
    return true;
}
bool Polynom::operator<(const Polynom& second) const noexcept {
    return !(*this > second) && (*this != second);
}

Polynom& Polynom::operator=(const Polynom& second) {
    if (this != &second) {
        _polynom = second._polynom;
    }
    return *this;
}
