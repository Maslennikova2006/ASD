// Copyright 2025 Mary Maslennikova

//#define EASY_EXAMPLE
//#define CIRCLE
//#define SPHERE
//#define SKIP_LIST
//#define UNSORTED_TABLE_M
//#define UNSORTED_TABLE_L
//#define SORTED_TABLE_M
//#define TREE
//#define UNSORTED_TABLE_BT
//#define BSTREE
//#define SORTED_TABLE_BST
//#define HEAP
//#define QUEUEPRIORITY
//#define HASHTABLEC
//#define HASHTABLEOA
//#define ADJACENCY_LIST_GRAPH
//#define EDGES_LIST_GRAPH
//#define ALG_DEX
//#define SORTED_TABLE_AVL
//#define INTERFACE
//#define LABYRINTH

#include <iostream>

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

#ifdef SKIP_LIST
#include <clocale>
#include "../lib_skip_list/skip_list.h"
int main() {
    setlocale(LC_ALL, "rus");
    SkipList<int, std::string> list;
    list.insert(2, "22");
    list.insert(8, "88");
    list.insert(4, "44");
    list.insert(7, "77");
    list.print();
    return 0;
}
#endif  // SKIP_LIST


#ifdef UNSORTED_TABLE_M
#include <clocale>
#include <string>
#include "../lib_unsorted_table_m/unsorted_table_m.h"
int main() {
    setlocale(LC_ALL, "rus");
    UnsortedTableM<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(97, "Москва");
    table.insert(16, "Казань");
    table.insert(78, "Санкт-Петербург");
    table.insert(55, "Омск");
    table.insert(18, "Ижевск");
    std::cout << table;
    table.erase(97);
    std::cout << table;
    const std::string* found = table.found(52);
    std::cout << *found;
    return 0;
}
#endif  // UNSORTED_TABLE_M


#ifdef UNSORTED_TABLE_L
#include <clocale>
#include <string>
#include "../lib_unsorted_table_l/unsorted_table_l.h"
int main() {
    setlocale(LC_ALL, "rus");
    UnsortedTableL<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(97, "Москва");
    table.insert(16, "Казань");
    table.insert(78, "Санкт-Петербург");
    table.insert(55, "Омск");
    table.insert(18, "Ижевск");
    std::cout << table;
    table.erase(97);
    std::cout << table;
    const std::string* found = table.found(52);
    std::cout << *found;
    return 0;
}
#endif  // UNSORTED_TABLE_L


#ifdef SORTED_TABLE_M
#include <clocale>
#include <string>
#include "../lib_sorted_table_m/sorted_table_m.h"
int main() {
    setlocale(LC_ALL, "rus");
    SortedTableM<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(97, "Москва");
    table.insert(16, "Казань");
    table.insert(78, "Санкт-Петербург");
    table.insert(55, "Омск");
    table.insert(18, "Ижевск");
    std::cout << table;
    table.erase(97);
    std::cout << table;
    const std::string* found = table.found(52);
    std::cout << *found;
    return 0;
}
#endif  // SORTED_TABLE_M

#ifdef TREE
#include <clocale>
#include <string>
#include "../lib_tree/tree.h"
int main() {
    setlocale(LC_ALL, "rus");
    Tree<int, std::string> tree;
    tree.insert(52, "Нижний Новгород");
    tree.insert(97, "Москва");
    tree.insert(16, "Казань");
    tree.insert(23, "Сочи");
    tree.insert(55, "Омск");
    tree.insert(18, "Ижевск");
    tree.insert(76, "Ярославль");
    tree.insert(64, "Саратов");
    tree.insert(34, "Волгоград");
    tree.insert(12, "Йошкар-Ола");
    tree.insert(33, "Муром");
    tree.insert(7, "Нальчик");
    tree.insert(37, "Иваново");

    tree.insert(64, "Саратов");
    tree.insert(34, "Волгоград");
    tree.insert(12, "Йошкар-Ола");
    tree.insert(33, "Муром");
    tree.insert(7, "Нальчик");
    tree.insert(37, "Иваново");
    tree.insert(64, "Саратов");
    tree.insert(34, "Волгоград");
    tree.insert(12, "Йошкар-Ола");
    tree.print_clr();
    const std::string* found = tree.find(78);
    if (!found)
        std::cout << "\nnullptr";
    else
        std::cout << "\n" << * found;
    std::cout << std::endl;
    //tree.erase(78);
    tree.print_w();
    std::cout << std::endl;
    tree.print();
    return 0;
}
#endif  // TREE

#ifdef UNSORTED_TABLE_BT
#include <clocale>
#include <string>
#include "../lib_unsorted_table_bt/unsorted_table_bt.h"
int main() {
    setlocale(LC_ALL, "rus");
    UnsortedTableBT<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(97, "Москва");
    table.insert(16, "Казань");
    table.insert(78, "Санкт-Петербург");
    table.insert(55, "Омск");
    table.insert(18, "Ижевск");
    std::cout << table;
    table.erase(97);
    std::cout << table;
    const std::string* found = table.found(52);
    std::cout << *found;
    return 0;
}
#endif  // UNSORTED_TABLE_BT

#ifdef BSTREE
#include <clocale>
#include <string>
#include "../lib_algorithms/algorithms.h"
#include "../lib_bstree/bstree.h"
#include "../lib_tvector/tvector.h"
#include "../lib_itable/itable.h"
int main() {
    setlocale(LC_ALL, "rus");
    //sort_vector();
    BSTree<int, int> tree;
    tree.insert(9, 9);
    tree.insert(5, 5);
    tree.insert(18, 18);
    tree.insert(3, 3);
    tree.insert(8, 8);
    tree.insert(16, 16);
    tree.insert(20, 20);
    tree.insert(7, 7);
    tree.print_lcr();
    std::cout << std::endl;
    tree.erase(5);
    tree.print_lcr();
    return 0;
}
#endif  // BSTREE

#ifdef SORTED_TABLE_BST
#include <clocale>
#include <string>
#include "../lib_algorithms/algorithms.h"
#include "../lib_sorted_table_bst/sorted_table_bst.h"
#include "../lib_tvector/tvector.h"
#include "../lib_itable/itable.h"
int main() {
    setlocale(LC_ALL, "rus");
    SortedTableBST<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(97, "Москва");
    table.insert(16, "Казань");
    table.insert(78, "Санкт-Петербург");
    table.insert(55, "Омск");
    table.insert(18, "Ижевск");
    std::cout << table;
    table.erase(97);
    std::cout << table;
    const std::string* found = table.found(16);
    std::cout << *found;
    return 0;
}
#endif  // SORTED_TABLE_BST

#ifdef HEAP
#include <clocale>
#include <string>
#include "../lib_tvector/tvector.h"
#include "../lib_heap/heap.h"
int main() {
    setlocale(LC_ALL, "rus");
    Heap<Pair<int, int>> heap;
    int count = 15;
    TVector<Pair<int, int>> vec(count);
    for (int i = 0; i < count; i++) {
        Pair<int, int> pair(i, i * 10);
        vec[i] = pair;
    }
    shuffle(vec);
    std::cout << "vec: ";
    vec.print();

    for (int i = 0; i < count; i++) {
        heap.insert(vec[i]);
    }

    std::cout << "vec sort: ";
    for (int i = 0; i < count; i++) {
        std::cout << heap.root() << " ";
        heap.pop();
    }

    return 0;
}

#endif  // HEAP

#ifdef QUEUEPRIORITY
#include <clocale>
#include <string>
#include "../lib_tvector/tvector.h"
#include "../lib_queue_priority/queue_priority.h"
int main() {
    setlocale(LC_ALL, "rus");
    QueuePriority<PairPriority<std::string>> queue;
    int count = 16;
    TVector<PairPriority<std::string>> vec;
    /*for (int i = 0; i < count; i++) {
        PairPriority<std::string> pair(i, std::to_string((i + 4) * 10), i);
        vec[i] = pair;
    }
    shuffle(vec);*/
    vec.push_back(PairPriority <std::string>(1, "100", 1));
    vec.push_back(PairPriority <std::string>(3, "300", 2));
    vec.push_back(PairPriority <std::string>(4, "4400", 3));
    vec.push_back(PairPriority <std::string>(1, "1000", 4));
    vec.push_back(PairPriority <std::string>(1, "50", 5));
    vec.push_back(PairPriority <std::string>(3, "330", 6));
    vec.push_back(PairPriority <std::string>(4, "400", 7));
    vec.push_back(PairPriority <std::string>(7, "70", 8));
    vec.push_back(PairPriority <std::string>(5, "330", 9));
    vec.push_back(PairPriority <std::string>(9, "400", 10));
    vec.push_back(PairPriority <std::string>(10, "800", 11));
    vec.push_back(PairPriority <std::string>(4, "404", 12));
    vec.push_back(PairPriority <std::string>(7, "707", 13));
    vec.push_back(PairPriority <std::string>(3, "3303", 14));
    vec.push_back(PairPriority <std::string>(9, "900", 15));
    vec.push_back(PairPriority <std::string>(10, "900", 16));
    int k;
    std::cout << "Введите число k (k до " << count << "): ";
    std::cin >> k;
    std::cout << "vec: ";
    vec.print();

    for (int i = 0; i < count; i++) {
        queue.insert(vec[i]);
    }

    std::cout << "Самые важные k элементов: ";
    for (int i = 0; i < k; i++) {
        std::cout << queue.top() << " ";
        queue.pop();
    }

    return 0;
}

#endif  // QUEUEPRIORITY

#ifdef HASHTABLEC
#include <clocale>
#include <string>
#include "../lib_tvector/tvector.h"
#include "../lib_hash_table_c/hashtablec.h"
int main() {
    setlocale(LC_ALL, "rus");
    HashTableC<std::string> table(20);

    TVector<Pair<std::string, std::string>> s1;
    s1.push_back(Pair<std::string, std::string>("one", "1"));
    s1.push_back(Pair<std::string, std::string>("two", "2"));  //
    s1.push_back(Pair<std::string, std::string>("five", "5"));  //
    s1.push_back(Pair<std::string, std::string>("four", "4"));
    s1.push_back(Pair<std::string, std::string>("seven", "7"));

    TVector<Pair<std::string, std::string>> s2;
    s2.push_back(Pair<std::string, std::string>("zero", "0"));
    s2.push_back(Pair<std::string, std::string>("two", "2"));  //
    s2.push_back(Pair<std::string, std::string>("five", "5"));  //
    s2.push_back(Pair<std::string, std::string>("six", "6"));

    for (int i = 0; i < s1.size(); i++) {
        try {
            table.insert(s1[i].first, s1[i].second);
        }
        catch (...) {

        }
    }
    for (int i = 0; i < s2.size(); i++) {
        try {
            table.insert(s2[i].first, s2[i].second);
        }
        catch (...) {

        }
    }

    std::cout << table;

    return 0;
}
#endif  // HASHTABLEC

#ifdef HASHTABLEOA
#include <clocale>
#include <string>
#include "../lib_tvector/tvector.h"
#include "../lib_hash_table_oa/hashtableoa.h"
int main() {
    setlocale(LC_ALL, "rus");
    HashTableOA<std::string> table(20);

    TVector<Pair<std::string, std::string>> s1;
    s1.push_back(Pair<std::string, std::string>("one", "1"));
    s1.push_back(Pair<std::string, std::string>("two", "2"));
    s1.push_back(Pair<std::string, std::string>("five", "5"));
    s1.push_back(Pair<std::string, std::string>("four", "4"));
    s1.push_back(Pair<std::string, std::string>("seven", "7"));
    s1.push_back(Pair<std::string, std::string>("zero", "0"));
    s1.push_back(Pair<std::string, std::string>("six", "6"));

    for (int i = 0; i < s1.size(); i++) {
        table.insert(s1[i].first, s1[i].second);
    }

    std::cout << table;

    return 0;
}
#endif  // HASHTABLEOA

#ifdef ADJACENCY_LIST_GRAPH
#include <clocale>
#include <string>
#include "../lib_tvector/tvector.h"
#include "../lib_adjacency_list_graph/adjacency_list_graph.h"
int main() {
    setlocale(LC_ALL, "rus");
    AdjacencyListGraph<int> graph(true, true);

    graph.add_edge(1, 7, 2);
    graph.add_edge(2, 7);
    graph.add_edge(1, 4, 5);
    graph.add_edge(4, 5, 2);
    graph.add_edge(2, 3, 3);
    graph.add_edge(4, 3, 5);

    graph.print();

    graph.delete_vertex(4);

    graph.print();

    return 0;
}
#endif  // ADJACENCY_LIST_GRAPH

#ifdef EDGES_LIST_GRAPH
#include <clocale>
#include <string>
#include "../lib_tvector/tvector.h"
#include "../lib_edges_list_graph/edges_list_graph.h"
int main() {
    setlocale(LC_ALL, "rus");
    EdgesListGraph<int> graph({ {{1, 7}, 1}, {{2, 7}, 5}, {{1, 4}, 2}}, true, true);

    graph.add_edge(4, 5, 2);
    graph.add_edge(2, 3, 3);
    graph.add_edge(4, 3, 5);

    graph.print();

    graph.delete_vertex(4);

    graph.print();

    graph.delete_edge(2, 3);

    graph.print();

    return 0;
}

#endif  // EDGES_LIST_GRAPH

#ifdef ALG_DEX
#include <clocale>
#include <string>
#include "../lib_tvector/tvector.h"
#include "../lib_adjacency_list_graph/adjacency_list_graph.h"
#include "../lib_algorithms/algorithms.h"
int main() {
    setlocale(LC_ALL, "rus");
    AdjacencyListGraph<int> graph({ {{0, 1}, 6}, {{1, 4}, 30} }, false, true);

    graph.add_edge(1, 2, 22);
    graph.add_edge(2, 4, 5);
    graph.add_edge(0, 3, 1);
    graph.add_edge(3, 2, 4);

    graph.print();

    TVector<int> res = algorithm_Dijkstra_Q(graph, 1, 4);
    //TVector<int> res = algorithm_Dijkstra(graph, 1, 4);
    res.print();

    return 0;
}
#endif  // ALG_DEX

#ifdef SORTED_TABLE_AVL
#include <clocale>
#include <string>
#include "../lib_algorithms/algorithms.h"
#include "../lib_sorted_table_avl/sorted_table_avl.h"
#include "../lib_tvector/tvector.h"
#include "../lib_itable/itable.h"
int main() {
    setlocale(LC_ALL, "rus");
    SortedTableAVL<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(97, "Москва");
    table.insert(16, "Казань");
    table.insert(78, "Санкт-Петербург");
    table.insert(55, "Омск");
    table.insert(18, "Ижевск");
    std::cout << table;
    table.erase(97);
    std::cout << table;
    const std::string* found = table.found(16);
    std::cout << *found;
    return 0;
}
#endif  // SORTED_TABLE_AVL


#ifdef INTERFACE
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


#ifdef LABYRINTH
#include "../lib_matrix/matrix.h"
#include "../lib_algorithms/algorithms.h"
void main() {
    Matrix<bool> lab = generate_labyrinth(13, 118, 10, 12);
    //std::cout << lab << std::endl;
    print_labyrinth(lab, 10, 12);
}

#endif  // LABYRINTH
