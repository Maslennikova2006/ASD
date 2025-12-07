// Copyright 2025 Mary Maslennikova

#include "../lib_lexem/lexem.h"

Lexem::Lexem(std::string _name, TypeLexem _type, double _value, int _priority, double(*_function)(double)) {
    name = _name;
    type = _type;
    value = _value;
    priority = _priority;
    function = _function;
}
bool Lexem::operator!=(const Lexem& other) const noexcept {
    return !(name == other.name && type == other.type && value == other.value && priority == other.priority && function == other.function);
}