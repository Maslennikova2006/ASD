// Copyright 2025 Mary Maslennikova

#ifndef LIB_LEXEM_LEXEM_H_
#define LIB_LEXEM_LEXEM_H_

#include <string>

enum TypeLexem { Constant, Variable, OpenBracket, ClosedBracket, Function, Operator, UnOperator, OpenedAbs, ClosedAbs };

struct Lexem {
    std::string name;
    TypeLexem type;
    double value;
    int priority;
    double (*function)(double);

    Lexem(std::string _name = "", TypeLexem _type = Constant, double _value = DBL_MAX, int _priority = -1, double(*_function)(double) = nullptr);
};

#endif  // LIB_LEXEM_LEXEM_H_
