// Copyright 2026 Mary Maslennikova

#ifndef LIB_POLYNOM_POLYNOM_H_
#define LIB_POLYNOM_POLYNOM_H_

#include <stdexcept>
#include "../lib_list/list.h"
#include "../lib_monom/monom.h"

// + вычисление полинома в точке

class Polynom {
    List<Monom> _polynom;

public:
    Polynom();
    Polynom(const Monom& monom);
    Polynom(const Polynom& other);

    ~Polynom();

    Polynom& operator+=(const Polynom& second);
    Polynom& operator-=(const Polynom& second);
    Polynom& operator*=(const Polynom& second);
    Polynom& operator*=(const double scalar);
    Polynom& operator/=(const double scalar);

    Polynom operator+(const Polynom& second) const;
    Polynom operator-(const Polynom& second) const;
    Polynom operator-() const;
    Polynom operator*(const Polynom& second) const;
    Polynom operator*(const double scalar) const;
    Polynom operator/(const double scalar) const;

    Polynom& operator+=(const Monom& monom);
    Polynom& operator-=(const Monom& monom);
    Polynom& operator*=(const Monom& monom);
    Polynom& operator/=(const Monom& monom);

    Polynom operator+(const Monom& monom) const;
    Polynom operator-(const Monom& monom) const;
    Polynom operator*(const Monom& monom) const;
    Polynom operator/(const Monom& monom) const;

    bool operator==(const Polynom& second) const noexcept;
    bool operator!=(const Polynom& second) const noexcept;
    bool operator>(const Polynom& second) const noexcept;
    bool operator<(const Polynom& second) const noexcept;

    Polynom& operator=(const Polynom& second);

    double calculate(double x, double y, double z) const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Polynom& monom);
    friend std::istream& operator>>(std::istream& is, Polynom& monom);
};

#endif  // LIB_POLYNOM_POLYNOM_H_
