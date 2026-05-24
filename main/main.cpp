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
//#define SORTED_TABLE_RB
//#define POLYNOM
#define EXPERIMENT

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
    AdjacencyListGraph<int> graph({ {{1, 7}, 1} }, false, true);
    //AdjacencyListGraph<int> graph(false, true);
    //AdjacencyListGraph<int> graph(true, false);
    //AdjacencyListGraph<int> graph(false, false);

    graph.add_edge(2, 7);
    graph.add_edge(1, 4, 5);
    graph.add_edge(4, 5, 2);
    graph.add_edge(2, 3, 3);
    graph.add_edge(4, 3, 5);

    graph.print();

    graph.delete_vertex(4);
    graph.delete_edge(2, 3);

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
    //EdgesListGraph<int> graph({ {{1, 7}, 1}, {{2, 7}, 5}, {{1, 4}, 2} }, true, false);
    //EdgesListGraph<int> graph({ {{1, 7}, 1}, {{2, 7}, 5}, {{1, 4}, 2} }, false, true);
    //EdgesListGraph<int> graph({ {{1, 7}, 1}, {{2, 7}, 5}, {{1, 4}, 2} }, false, false);


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


#ifdef SORTED_TABLE_RB
#include <clocale>
#include <string>
#include "../lib_algorithms/algorithms.h"
#include "../lib_sorted_table_rb/sorted_table_rb.h"
#include "../lib_tvector/tvector.h"
#include "../lib_itable/itable.h"
int main() {
    setlocale(LC_ALL, "rus");
    SortedTableRB<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(97, "Москва");
    table.insert(16, "Казань");
    table.insert(78, "Санкт-Петербург");
    table.insert(55, "Омск");
    table.insert(18, "Ижевск");
    std::cout << table;
    const std::string* found = table.found(16);
    std::cout << *found;
    return 0;
}
#endif  // SORTED_TABLE_RB

#ifdef POLYNOM
#include "../lib_polynom/polynom.h"
#include <clocale>
#include <iostream>

int main() {
    setlocale(LC_ALL, "rus");
    Polynom p1("5.8x^2+8y^3z^4-6.8z^2");
    Polynom p2("2.3x^2-4y^3z^4+8.3y^3z");
    p1 += p2;
    std::cout << "result" << std::endl;
    std::cout << p1;
    return 0;
}
#endif  // POLYNOM

#ifdef EXPERIMENT
#include "../lib_experiment/experiment.h"
#include "../lib_unsorted_table_m/unsorted_table_m.h"
#include "../lib_sorted_table_m/sorted_table_m.h"
#include "../lib_sorted_table_bst/sorted_table_bst.h"
#include <clocale>
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <vector>

#define SIZE 100000
#define COUNT_NOT_EXIST_KEYS 5
#define COUNT_EXPERIMENT 10

int main() {
    setlocale(LC_ALL, "rus");
    TVector<double> insert;
    TVector<double> found;
    TVector<double> erase;

    for (int i = 1; i <= COUNT_EXPERIMENT; i++) {
        //UnsortedTableM<std::string, Polynom> table;
        //SortedTableM<std::string, Polynom> table;
        SortedTableBST<std::string, Polynom> table;
        auto sec_insert = std::chrono::duration<double>::zero();
        TVector<std::string> exist_keys;
        std::ifstream in("C:/GitHub/ASD/polynoms.txt");
        if (!in.is_open()) {
            std::cout << "Файл polynoms.txt не открывается!\n";
            return 1;
        }
        std::string line;
        int count = 0;
        while (std::getline(in, line)) {
            if (line.empty()) continue;
            size_t sepPos = line.find(';');
            if (sepPos == std::string::npos) continue;

            std::string name = line.substr(0, sepPos);
            Polynom p;

            std::string rest = line.substr(sepPos + 1);
            std::stringstream ss(rest);
            std::string monomStr;

            while (std::getline(ss, monomStr, ';')) {
                std::stringstream monomSs(monomStr);
                std::string numStr;
                int coeff, pow1, pow2, pow3;

                std::getline(monomSs, numStr, ','); coeff = std::stoi(numStr);
                std::getline(monomSs, numStr, ','); pow1 = std::stoi(numStr);
                std::getline(monomSs, numStr, ','); pow2 = std::stoi(numStr);
                std::getline(monomSs, numStr, ','); pow3 = std::stoi(numStr);
                int powers[3] = { pow1, pow2, pow3 };
                Monom m(coeff, powers);
                p += m;
            }

            auto start_insert = std::chrono::high_resolution_clock::now();
            table.insert(name, p);
            auto end_insert = std::chrono::high_resolution_clock::now();

            sec_insert += std::chrono::duration<double>(end_insert - start_insert);

            exist_keys.push_back(name);
            count++;
            if (count == SIZE)
                break;
        }

        std::cout << i << ") Вставка: " << sec_insert.count() << " сек" << std::endl;
        insert.push_back(sec_insert.count());

        shuffle(exist_keys);

        // Поиск
        auto start_found = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < SIZE; j++) {
            if (j >= SIZE - COUNT_NOT_EXIST_KEYS)
                table.found(exist_keys[j] + "h");
            else
                table.found(exist_keys[j]);
        }
        auto end_found = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> sec_found = end_found - start_found;
        std::cout << i << ") Поиск: " << sec_found.count() << " сек" << std::endl;
        found.push_back(sec_found.count());

        // Удаление
        auto start_erase = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < exist_keys.size(); j++) {
            table.erase(exist_keys[j]);
        }
        auto end_erase = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> sec_erase = end_erase - start_erase;
        std::cout << i << ") Удаление: " << sec_erase.count() << " сек" << std::endl;
        erase.push_back(sec_erase.count());
    }


    double total_insert = 0.0, total_found = 0.0, total_erase = 0.0;
    for (int i = 0; i < COUNT_EXPERIMENT; i++) {
        total_insert += insert[i];
        total_found += found[i];
        total_erase += erase[i];
    }
    std::cout << std::endl << "Среднее время вставки: " << total_insert / COUNT_EXPERIMENT << std::endl;
    std::cout << "Среднее время поиска: " << total_found / COUNT_EXPERIMENT << std::endl;
    std::cout << "Среднее время удаление: " << total_erase / COUNT_EXPERIMENT << std::endl;

    //generator.print();
    //std::cout << table;

    //std::cout « table;
    //GeneratorPolynoms gen;
    //int size = 100000;

    //TVector<Pair<int, Polynom>> data = gen.generate_data(size, 5);
    //SortedTableRB<int, Polynom> table;
    //auto start_insert = std::chrono::high_resolution_clock::now();
    //for (int i = 0; i < size; i++) {
    //    table.insert(data[i].first, data[i].second);
    //}
    //auto end_insert = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> sec_insert = end_insert - start_insert;
    //std::cout << "Вставка: " << sec_insert.count() << " сек" << std::endl;
    ////std::cout << table;

    //TVector<int> exist_keys;
    //TVector<int> not_exist_keys;
    //for (int i = 0; i < size; i += 10) {
    //    exist_keys.push_back(data[i].first);
    //    not_exist_keys.push_back(-data[i].first);
    //}
    //auto start_found = std::chrono::high_resolution_clock::now();
    //for (int i = 0; i < exist_keys.size(); i++) {
    //    table.found(exist_keys[i]);
    //    table.found(not_exist_keys[i]);
    //}
    //auto end_found = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> sec_found = end_found - start_found;
    //std::cout << "Поиск: " << sec_found.count() << " сек" << std::endl;


    //auto start_erase = std::chrono::high_resolution_clock::now();
    //for (int i = 0; i < exist_keys.size(); i++) {
    //    table.erase(exist_keys[i]);
    //}
    //auto end_erase = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> sec_erase = end_erase - start_erase;
    //std::cout << "Удаление: " << sec_erase.count() << " сек" << std::endl;
    ////generator.print();
    ////std::cout << table;
    return 0;
}
#endif  // EXPERIMENT