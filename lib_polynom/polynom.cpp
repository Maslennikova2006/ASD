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
    auto p1 = _polynom.begin();
    auto p2 = second._polynom.begin();
    while (p1 != _polynom.end() && p2 != second._polynom.end()) {
        if ((*p1) == (*p2)) {
            *p1 += *p2;
            p1++;
            p2++;
        }
        else {
            if (*p1 < *p2)
                p1++;
            else {
                _polynom.insert(p1, *p2);
                p2++;
            }
        }

    }
}
Polynom& operator-=(const Polynom& second);
Polynom& operator*=(const Polynom& second);
Polynom& operator/=(const Polynom& second);
Polynom& operator*=(const double scalar);
Polynom& operator/=(const double scalar);