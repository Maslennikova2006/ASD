// Copyright 2025 Mary Maslennikova

//#define EASY_EXAMPLE
//#define CIRCLE
//#define SPHERE
#define EXPRESSION

#ifdef EXPRESSION
#include <iostream>
#include <clocale>
#include <string>
#include "../lib_expression/expression.h"
#include "../lib_tvector/tvector.h"

#define ID_WIDTH 5
#define EXPRESSION_WIDTH 50
#define VARIABLE_WIDTH 30
#define DIVIDER_WIDTH 4
#define TOTAL_WIDTH ID_WIDTH + EXPRESSION_WIDTH + VARIABLE_WIDTH + DIVIDER_WIDTH
void print_title() {
    std::cout << "|";
    std::cout << " ID";
    for (int i = 0; i < ID_WIDTH - 4; i++) {
        std::cout << " ";
    }
    std::cout << "|";

    std::cout << " EXPRESSION";
    for (int i = 0; i < EXPRESSION_WIDTH - 12; i++) {
        std::cout << " ";
    }
    std::cout << "|";

    std::cout << " VARAIBLES VALUES";
    for (int i = 0; i < VARIABLE_WIDTH - 15; i++) {
        std::cout << " ";
    }
    std::cout << "|\n";
}
void print_line() {
    std::cout << "+";
    for (int i = 0; i < TOTAL_WIDTH - 2; i++) {
        std::cout << "-";
    }
    std::cout << "+\n";
}
void print_data(std::string str, int width) {
    std::cout << " " << str;
    for (int i = 0; i < width - str.length() - 2; i++) {
        std::cout << " ";
    }
    std::cout << "|";
}
void print_variables(Expression& expr) {
    List<Lexem> variables = expr.get_variables();
    auto var = variables.begin();
    std::string str = " ";
    for (var; var != variables.end(); var++) {
        if ((*var).value == DBL_MAX)
            str += (*var).name + " = ?";
        else
            str += (*var).name + " = " + std::to_string(static_cast<int>((*var).value));

        auto next = var;
        next++;
        if (next != variables.end()) {
            str += ", ";
        }
    }
    std::cout << str;
    int spaces = VARIABLE_WIDTH - str.length() + 2;
    if (spaces > 0) {
        for (int j = 0; j < spaces; j++) {
            std::cout << " ";
        }
    }
}
void print_table(TVector<Expression>& expressions) {
    print_line();
    print_title();
    print_line();

    for (int i = 0; i < expressions.size(); i++) {
        std::cout << "|";
        print_data(std::to_string(i + 1), ID_WIDTH);

        print_data(expressions[i].to_string(), EXPRESSION_WIDTH);

        print_variables(expressions[i]);
        std::cout << "|\n";
    }

    print_line();
}

void print_menu() {
    std::cout << "\nМЕНЮ: \n";
    std::cout << "1. Создать новое выражение\n";
    std::cout << "2. Удалить выражение\n";
    std::cout << "3. Задать переменные\n";
    std::cout << "4. Вычислить значение выражения\n";
    std::cout << "0. Выход\n";
}

int input_id(std::string str, int max) {
    int id;
    std::cout << str;
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (id < 1 || id > max)
        throw std::invalid_argument("Неверный ID, попробуйте ещё раз!\n");
    return id;
}

void create_expression(TVector<Expression>& expressions) {
    std::string str;
    std::cout << "Введите выражение: ";
    std::getline(std::cin, str);
    Expression expr(str);
    expressions.push_back(expr);
}
void delete_expression(TVector<Expression>& expressions) {
    int id = input_id("Введите номер выражения, которое хотите удалить: ", expressions.size());
    expressions.erase(id - 1);
}
void set_variables(TVector<Expression>& expressions) {
    int id = input_id("Введите номер выражения, для которого хотите установить значения переменных: ", expressions.size());
    List<Lexem> variables = expressions[id - 1].get_variables();
    auto l = variables.begin();
    for (l; l != variables.end(); l++) {
        int val;
        std::cout << (*l).name << " = ";
        std::cin >> val;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        expressions[id - 1].set_variables((*l).name, val);
    }
}
void calculate_expression(TVector<Expression>& expressions) {
    int id = input_id("Введите номер выражения для вычисления: ", expressions.size());
    try {
        double val = expressions[id - 1].calculate();
        std::cout << "Результат для выражения " << id << ": " << val << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
    }
    std::cout << "Нажмите Enter для продолжения...";
    std::cin.get();
}

void main() {
    setlocale(LC_ALL, "rus");
    int answer;
    TVector<Expression> expressions;
    std::string st1 = "x + y * (x^2 - 16)";
    Expression expr1(st1);
    expr1.set_variables("x", 5);
    expr1.set_variables("y", 8);
    expressions.push_back(expr1);
    std::string st2 = "x_1 * sin(y + 7) + y * (-|x_2 - 17| + 23)";
    Expression expr2(st2);
    expressions.push_back(expr2);
    while (1) {
        try {
            system("cls");
            print_table(expressions);
            print_menu();
            std::cout << "\nВаш выбор: ";
            std::cin >> answer;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            switch (answer) {
            case 1:
                create_expression(expressions);
                break;
            case 2:
                delete_expression(expressions);
                break;
            case 3:
                set_variables(expressions);
                break;
            case 4:
                calculate_expression(expressions);
                break;
            case 0:
                return;
            default:
                throw std::invalid_argument("Неверный выбор!\n");
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << e.what();
            std::cout << "Нажмите Enter для продолжения...";
            std::cin.get();
        }
    }
}

#endif  // EXPRESSION


#ifdef EASY_EXAMPLE
#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }
  return 0;
}
#endif  // EASY_EXAMPLE

#ifdef CIRCLE
#include "../lib_circle/circle.h"
#include "../lib_algorithms/algorithms.h"
#include <clocale>

int main() {
    //read_expression("5t5 56hyh ggrr 6 yyv");
    setlocale(LC_ALL, "rus");
    Point point1(5, 8);
    Circle c1(point1, 9);
    Circle c2(3, 8, 6);
    show_position(check_position(c1, c2));
    Point point2(0, 0);
    Circle c3(point2, 3);
    Circle c4(15, 8, 2);
    show_position(check_position(c3, c4));
    Point point3(0, 0);
    Circle c5(point3, 3);
    Circle c6(8, 0, 5);
    show_position(check_position(c5, c6));
    Circle c7(0, 0, 5);
    Circle c8(3, 0, 4);
    show_position(check_position(c7, c8));
    Point point5(-2, 2);
    Circle c9(point5, 3);
    Circle c10(-2, 2, 3);
    show_position(check_position(c9, c10));
    return 0;
}
#endif  // CIRCLE

#ifdef SPHERE
#include "../lib_sphere/sphere.h"
#include "../lib_algorithms/algorithms.h"
#include <clocale>

int main() {
    setlocale(LC_ALL, "rus");
    Point3D point1(-2, 2, 2);
    Sphere s1(point1, 3);
    Sphere s2(-2, 2, 2, 3);
    show_position(check_position(s1, s2));
    Point3D point2(-2, 2, 2);
    Sphere s3(point2, 3);
    Sphere s4(-5, 8, 7, 2);
    show_position(check_position(s3, s4));
    Point point3(0, 3);
    Sphere s5(point3, 5, 3);
    Sphere s6(0, 3, 4, 2);
    show_position(check_position(s5, s6));
    Point point(0, 0);
    Sphere s7(point, 0, 3);
    Sphere s8(0, 1, 0, 1);
    show_position(check_position(s7, s8));
    Sphere s9(0, 0, 0, 2);
    Sphere s10(3, 0, 0, 1);
    show_position(check_position(s9, s10));
    return 0;
}
#endif  // SPHERE