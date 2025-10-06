// Copyright 2025 Mary Maslennikova

//#define EASY_EXAMPLE
#define INTERFACE

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
#include <iostream>

template <typename T> class Matrix;
template <typename T> class TriangleMatrix;
template <typename T> class MathVector;

template <typename T>
bool actions_with_ordinary_matrices(Matrix<T>& A, Matrix<T>& B,
    Matrix<T>& C, MathVector<T>& vector_c, int answer_operation);
template <typename T>
bool actions_with_triangle_matrices(TriangleMatrix<T>& A, TriangleMatrix<T>& B,
    TriangleMatrix<T>& C, MathVector<T>& vector_c, int answer_operation);

void matrix_menu(int& answer_matrix, bool& isExit) {
    std::cout << "                  MENU MATRIX\n";
    std::cout << "1) Ordinary matrix\n";
    std::cout << "2) Triangle matrix\n";
    std::cout << "0) Exit\n";
    while (1) {
        std::cout << "Your choice: ";
        std::cin >> answer_matrix;
        if (answer_matrix < 0 || answer_matrix > 2)
            std::cout << "Try again!\n";
        else
            break;
    }
    if (answer_matrix == 0)
        isExit = true;
}
void operation_menu(int& answer_operation, bool& isExit) {
    std::cout << "                  MENU OPERATION\n";
    std::cout << "1) Summation\n";
    std::cout << "2) Subtraction\n";
    std::cout << "3) Multiplication\n";
    std::cout << "4) Multiplication by a scalar\n";
    std::cout << "5) Multiplication by a vector\n";
    std::cout << "0) Exit\n";
    while (1) {
        std::cout << "Your choice: ";
        std::cin >> answer_operation;
        if (answer_operation < 0 || answer_operation > 5)
            std::cout << "Try again!\n";
        else
            break;
    }
    if (answer_operation == 0)
        isExit = true;
}
void check_size(int size) {
    if (size <= 0)
        throw std::logic_error("The size must be greater than 0!\n");
}
template <typename T>
bool actions_with_ordinary_matrices(Matrix<T>& A, Matrix<T>& B,
    Matrix<T>& C, MathVector<T>& vector_c, int answer_operation) {
    size_t M_a, N_a;
    size_t M_b, N_b;
    size_t size;
    T scalar;
    MathVector<T> vector;
    std::cout << "Enter the size of the matrix A:\n";
    while (1) {
        std::cout << "Rows(M): ";
        std::cin >> M_a;
        try {
            check_size(M_a);
        }
        catch (const std::exception& ex) {
            std::cerr << ex.what();
            continue;
        }
        break;
    }
    while (1) {
        std::cout << "Columns(N): ";
        std::cin >> N_a;
        try {
            check_size(N_a);
        }
        catch (const std::exception& ex) {
            std::cerr << ex.what();
            continue;
        }
        break;
    }
    A = Matrix<T>(M_a, N_a);
    std::cout << "Enter the matrix: \n";
    std::cin >> A;
    if (answer_operation >= 1 && answer_operation <= 3) {
        std::cout << "Enter the size of the matrix B:\n";
        while (1) {
            std::cout << "Rows(M): ";
            std::cin >> M_b;
            try {
                check_size(M_b);
            }
            catch (const std::exception& ex) {
                std::cerr << ex.what();
                continue;
            }
            break;
        }
        while (1) {
            std::cout << "Columns(N): ";
            std::cin >> N_b;
            try {
                check_size(N_b);
            }
            catch (const std::exception& ex) {
                std::cerr << ex.what();
                continue;
            }
            break;
        }
        B = Matrix<T>(M_b, N_b);
        std::cout << "Enter the matrix: \n";
        std::cin >> B;
    }
    else if (answer_operation == 4) {
        std::cout << "Enter a scalar: \n";
        std::cin >> scalar;
    }
    else if (answer_operation == 5) {
        std::cout << "Enter the size of the vector: \n";
        while (1) {
            std::cout << "Size: ";
            std::cin >> size;
            try {
                check_size(size);
            }
            catch (const std::exception& ex) {
                std::cerr << ex.what();
                continue;
            }
            break;
        }
        std::cout << "Enter a vector: \n";
        std::cin >> vector;
    }
    switch (answer_operation) {
    case 1:
        try {
            C = A + B;
        }
        catch (const std::exception& ex) {
            std::cerr << ex.what();
            return false;
        }
        break;
    case 2:
        try {
            C = A - B;
        }
        catch (const std::exception& ex) {
            std::cerr << ex.what();
            return false;
        }
        break;
    case 3:
        try {
            C = A * B;
        }
        catch (const std::exception& ex) {
            std::cerr << ex.what();
            return false;
        }
        break;
    case 4:
        C = A * scalar;
        break;
    case 5:
        try {
            vector_c = A * vector;
        }
        catch (const std::exception& ex) {
            std::cerr << ex.what();
            return false;
        }
        break;
    default:
        break;
    }
    return true;
}
template <typename T>
bool actions_with_triangle_matrices(TriangleMatrix<T>& A, TriangleMatrix<T>& B,
    TriangleMatrix<T>& C, MathVector<T>& vector_c, int answer_operation) {
    size_t size_a, size_b;
    size_t size;
    MathVector<T> vector;
    T scalar;
    std::cout << "Enter the size of the matrix A:\n";
    while (1) {
        std::cout << "Size: ";
        std::cin >> size_a;
        try {
            check_size(size_a);
        }
        catch (const std::exception& ex) {
            std::cerr << ex.what();
            continue;
        }
        break;
    }
    A = TriangleMatrix<T>(size_a);
    std::cout << "Enter the matrix: \n";
    std::cin >> A;
    if (answer_operation >= 1 && answer_operation <= 3) {
        std::cout << "Enter the size of the matrix B:\n";
        while (1) {
            std::cout << "Size: ";
            std::cin >> size_b;
            try {
                check_size(size_b);
            }
            catch (const std::exception& ex) {
                std::cerr << ex.what();
                continue;
            }
            break;
        }
        B = TriangleMatrix<T>(size_b);
        std::cout << "Enter the matrix: \n";
        std::cin >> B;
    }
    else if (answer_operation == 4) {
        std::cout << "Enter a scalar: \n";
        std::cin >> scalar;
    }
    else if (answer_operation == 5) {
        std::cout << "Enter the size of the vector: \n";
        while (1) {
            std::cout << "Size: ";
            std::cin >> size;
            try {
                check_size(size);
            }
            catch (const std::exception& ex) {
                std::cerr << ex.what();
                continue;
            }
            break;
        }
        std::cout << "Enter a vector: \n";
        std::cin >> vector;
    }
    switch (answer_operation) {
    case 1:
        try {
            C = A + B;
        }
        catch (const std::exception& ex) {
            std::cerr << ex.what();
            return false;
        }
        break;
    case 2:
        try {
            C = A - B;
        }
        catch (const std::exception& ex) {
            std::cerr << ex.what();
            return false;
        }
        break;
    case 3:
        try {
            C = A * B;
        }
        catch (const std::exception& ex) {
            std::cerr << ex.what();
            return false;
        }
        break;
    case 4:
        C = A * scalar;
        break;
    case 5:
        try {
            vector_c = A * vector;
        }
        catch (const std::exception& ex) {
            std::cerr << ex.what();
            return false;
        }
        break;
    default:
        break;
    }
    return true;
}

#ifdef INTERFACE
#include <iostream>
#include "../lib_trianglematrix/trianglematrix.h"

int main() {
    while (1) {
        int answer_matrix;
        int answer_operation;
        bool isExit = false;
        bool isSuccess = false;
        operation_menu(answer_operation, isExit);
        if (isExit)
            break;
        matrix_menu(answer_matrix, isExit);
        if (isExit)
            break;
        system("cls");
        if (answer_matrix == 1) {
            Matrix<int> matrix_a, matrix_b, matrix_c;
            MathVector<int> vector_c;
            isSuccess = actions_with_ordinary_matrices<int>(matrix_a, matrix_b, matrix_c, vector_c, answer_operation);
            if (isSuccess) {
                std::cout << "Result: \n";
                if (answer_operation != 5) {
                    std::cout << matrix_c;
                }
                else {
                    std::cout << vector_c;
                }
            }
        }
        else {
            TriangleMatrix<int> matrix_a, matrix_b, matrix_c;
            MathVector<int> vector_c;
            isSuccess = actions_with_triangle_matrices<int>(matrix_a, matrix_b, matrix_c, vector_c, answer_operation);
            if (isSuccess) {
                std::cout << "Result: \n";
                if (answer_operation != 5) {
                    std::cout << matrix_c;
                }
                else {
                    std::cout << vector_c;
                }
            }
        }
        char answer;
        std::cout << "\nDo you want to continue?\n";
        std::cout << "Your choice: ";
        std::cin >> answer;
        if (answer == 'n')
            break;
        else {
            system("cls");
            continue;
        }
    }

    return 0;
}
#endif  // INTERFACE
