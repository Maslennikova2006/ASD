// Copyright 2026 Mary Maslennikova

#ifndef LIB_PARSER_PARSER_H_
#define LIB_PARSER_PARSER_H_

#include "../lib_monom/monom.h"
#include "../lib_list/list.h"

namespace Parser {
    Monom parse_monom(const std::string& str);
    List<Monom> parse_polynom(const std::string& str);

    int follow_the_line(size_t ind, const std::string& str);

    /*bool is_letters(char symbol);
    bool is_digit(char symbol);*/

    std::string extract_number(const std::string& expression, int index);

}

#endif  // LIB_PARSER_PARSER_H_