// Copyright 2025 Mary Maslennikova

#include <iostream>
#include <clocale>
#include "../lib_algorithms/algorithms.h"

void show_position(Position pos) {
    switch (pos)
    {
    case intersect:
        std::cout << "Объекты пересекаются\n";
        break;
    case inside:
        std::cout << "Один объект внутри другого\n";
        break;
    case no_point:
        std::cout << "Объекты не имеют общих точек\n";
        break;
    case match:
        std::cout << "Объекты совпадают\n";
        break;
    case touch:
        std::cout << "Объекты касаются в одной точке\n";
        break;
    default:
        break;
    }
}