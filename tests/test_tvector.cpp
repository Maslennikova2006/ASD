// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_tvector/tvector.h"

TEST(TestTVectorLib, check_the_default_constructor) {
    TVector<float> vec;
    EXPECT_EQ(static_cast <size_t>(0), vec.size());
    EXPECT_EQ(static_cast<size_t>(STEP_OF_CAPACITY), vec.capacity());
    EXPECT_TRUE(vec.is_empty());
}
TEST(TestTVectorLib, check_the_initialization_constructor) {
    int array[5] = { 1, 2, 3, 4, 5 };
    TVector<int> vec(5, array);
    bool check_address_data = (vec.data() != nullptr);
    bool check_correct_values_data = true;
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] == array[i])
            check_correct_values_data &= true;
        else
            check_correct_values_data &= false;
    }
    EXPECT_EQ(static_cast <size_t>(5), vec.size());
    EXPECT_EQ(static_cast<size_t>(STEP_OF_CAPACITY), vec.capacity());
    EXPECT_TRUE(check_address_data);
    EXPECT_TRUE(check_address_data);
}
TEST(TestTVectorLib, check_the_initialization_list_constructor) {
    TVector<int> vec(4, { 1, 2, 3, 4 });
    bool check_address_data = (vec.data() != nullptr);
    bool check_correct_values_data = true;
    int v;
    for (size_t i = 0, v = 1; i < vec.size(); i++, v++) {
        if (vec[i] == v)
            check_correct_values_data &= true;
        else
            check_correct_values_data &= false;
    }
    EXPECT_EQ(static_cast <size_t>(4), vec.size());
    EXPECT_EQ(static_cast<size_t>(STEP_OF_CAPACITY), vec.capacity());
    EXPECT_TRUE(check_address_data);
    EXPECT_TRUE(check_correct_values_data);
}
TEST(TestTVectorLib, throw_when_try_copy_vector) {
    TVector<int>* obj = nullptr;
    ASSERT_ANY_THROW(TVector<int> copy_obj(*obj));
}
TEST(TestTVectorLib, check_the_copy_constructor) {
    int array[5] = { 1, 2, 3, 4, 5 };
    TVector<int> vec1(5, array);
    TVector<int> vec2(vec1);
    bool check_address_data = (vec2.data() != nullptr);
    bool check_correct_values_data = true;
    for (size_t i = 0; i < vec2.size(); i++) {
        if (vec2[i] == array[i])
            check_correct_values_data &= true;
        else
            check_correct_values_data &= false;
    }
    EXPECT_EQ(static_cast <size_t>(5), vec2.size());
    EXPECT_EQ(static_cast<size_t>(STEP_OF_CAPACITY), vec2.capacity());
    EXPECT_TRUE(check_address_data);
    EXPECT_TRUE(check_correct_values_data);
}
TEST(TestTVectorLib, check_for_equivalence) {
    int array[4] = { 1, 2, 3, 4 };
    TVector<int> vec1(4, array), vec2(4, { 1, 2, 3, 4 });
    EXPECT_TRUE(vec1 == vec2);
}
TEST(TestTVectorLib, check_for_equivalence_2) {
    int array[4] = { 1, 2, 3, 4 };
    TVector<int> vec1(4, array), vec2(4, { 1, 2, 3, 4 });
    EXPECT_FALSE(vec1 != vec2);
}
TEST(TestTVectorLib, check_for_not_equivalence) {
    int array[4] = { 1, 2, 3, 4 };
    TVector<int> vec1(4, array), vec2(5, { 1, 2, 3, 4, 5 });
    EXPECT_TRUE(vec1 != vec2);
}
TEST(TestTVectorLib, check_for_not_equivalence_2) {
    int array[5] = { 1, 2, 3, 4, 5 };
    TVector<int> vec1(5, array), vec2(4, { 1, 2, 3, 4 });
    EXPECT_FALSE(vec1 == vec2);
}
TEST(TestTVectorLib, check_reserve_with_decreasing_capacity) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.reserve(5);
    TVector<int> res({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_reserve_with_increasing_capacity) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.reserve(25);
    EXPECT_EQ(static_cast<size_t>(25), vec.capacity());
}
TEST(TestTVectorLib, check_resize_with_decreasing_size) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.resize(5);
    TVector<int> res({ 1, 2, 3, 4, 5 });
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_resize_with_increasing_size_and_capacity) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.resize(16);
    EXPECT_EQ(static_cast<size_t>(16), vec.size());
    EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
}
TEST(TestTVectorLib, check_resize_with_filling_in_the_value) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.resize(16, 0);
    TVector<int> res({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0 });
    EXPECT_EQ(static_cast<size_t>(16), vec.size());
    EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_shrink_to_fit) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.shrink_to_fit();
    TVector<int> res({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    EXPECT_EQ(static_cast<size_t>(10), vec.size());
    EXPECT_EQ(static_cast<size_t>(10), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_the_assignment_operator) {
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    TVector<int> vec2;
    vec2 = vec1;
    EXPECT_TRUE(vec2 == vec1);
}
TEST(TestTVectorLib, check_the_index_conversion_operator) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    EXPECT_EQ(4, vec[3]);
}
TEST(TestTVectorLib, check_the_index_conversion_operator_2) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    vec[3] = 5;
    EXPECT_EQ(5, vec[3]);
}
TEST(TestTVectorLib, check_the_insertion_at_the_beginning) {
    TVector<int> vec(10, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.push_front(55);
    TVector<int> res(11,
        { 55, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    EXPECT_EQ(static_cast<size_t>(15), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_the_insertion_in_the_middle) {
    TVector<int> vec(10, { 6, 2, 3, 4, 5, 6, 7, 8, 3, 4 });
    vec.insert(3, 44);
    TVector<int> res(11, { 6, 2, 3, 44, 4, 5, 6, 7, 8, 3, 4 });
    EXPECT_EQ(static_cast<size_t>(15), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_the_insertion_several_elems) {
    TVector<int> vec(10, { 6, 2, 3, 4, 5, 6, 7, 8, 5, 6 });
    vec.insert(2, 4, 99);
    EXPECT_EQ(static_cast<size_t>(15), vec.capacity());
    EXPECT_EQ(vec[2], 99);
    EXPECT_EQ(vec[5], 99);
}
TEST(TestTVectorLib, check_the_insertion_from_the_list) {
    TVector<int> vec(10, { 6, 2, 3, 4, 5, 6, 7, 8, 99, 87 });
    vec.insert(3, { 11, 22, 33 });
    TVector<int> res(13,
        { 6, 2, 3, 11, 22, 33, 4, 5, 6, 7, 8, 99, 87 });
    EXPECT_EQ(static_cast<size_t>(15), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_the_insertion_at_the_end) {
    TVector<int> vec(10, { 4, 5, 6, 7, 8, 2, 3, 4, 5, 6 });
    vec.push_back(9);
    TVector<int> res(11, { 4, 5, 6, 7, 8, 2, 3, 4, 5, 6, 9 });
    EXPECT_EQ(static_cast<size_t>(15), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_the_insertion_at_the_beginning_with_memory_reallocation) {
    TVector<int> vec(15, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    vec.push_front(55);
    TVector<int> res(16,
        { 55, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_the_insertion_in_the_middle_with_memory_reallocation) {
    TVector<int> vec(15, { 6, 2, 3, 4, 5, 6, 7, 8, 3, 4, 5, 6, 7, 8, 9 });
    vec.insert(3, 44);
    TVector<int> res(16, { 6, 2, 3, 44, 4, 5, 6, 7, 8, 3, 4, 5, 6, 7, 8, 9 });
    EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_the_insertion_several_elems_with_memory_reallocation) {
    TVector<int> vec(14, { 6, 2, 3, 4, 5, 6, 7, 8, 5, 6, 7, 8, 9, 3 });
    vec.insert(2, 4, 99);
    TVector<int> res(18,
        { 6, 2, 99, 99, 99, 99, 3, 4, 5, 6, 7, 8, 5, 6, 7, 8, 9, 3 });
    EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_the_insertion_from_the_list_with_memory_reallocation) {
    TVector<int> vec(13, { 6, 2, 3, 4, 5, 6, 7, 8, 99, 87, 5, 66, 7 });
    vec.insert(3, { 11, 22, 33 });
    TVector<int> res(16,
        { 6, 2, 3, 11, 22, 33, 4, 5, 6, 7, 8, 99, 87, 5, 66, 7 });
    EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_the_insertion_at_the_end_with_memory_reallocation) {
    TVector<int> vec(15, { 4, 5, 6, 7, 8, 2, 3, 4, 5, 6, 7, 34, 5, 4, 6 });
    vec.push_back(9);
    TVector<int> res(16, { 4, 5, 6, 7, 8, 2, 3, 4, 5, 6, 7, 34, 5, 4, 6, 9 });
    EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_for_deletion_from_the_beginning) {
    TVector<int> vec(10,
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.pop_front();
    vec.pop_front();
    vec.pop_front();
    TVector<int> res(7, { 4, 5, 6, 7, 8, 9, 10 });
    EXPECT_EQ(static_cast<size_t>(15), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_for_deletion_from_the_middle) {
    TVector<int> vec(10,
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.erase(4);
    vec.erase(3);
    vec.erase(5);
    TVector<int> res(7, { 1, 2, 3, 6, 7, 9, 10 });
    EXPECT_EQ(static_cast<size_t>(15), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_for_deletion_from_the_beginning_with_memory_reallocation) {
    TVector<int> vec(16,
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
    vec.pop_front();
    vec.pop_front();
    vec.pop_front();
    TVector<int> res(13, { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
    EXPECT_EQ(static_cast<size_t>(15), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_for_deletion_from_the_middle_with_memory_reallocation) {
    TVector<int> vec(16,
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
    vec.erase(4);
    vec.erase(3);
    vec.erase(5);
    TVector<int> res(13, { 1, 2, 3, 6, 7, 9, 10, 11, 12, 13, 14, 15, 16 });
    EXPECT_EQ(static_cast<size_t>(15), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_for_deletion_from_the_back) {
    TVector<int> vec(16,
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    TVector<int> res(13, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 });
    EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_for_complete_deletion) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.clear();
    EXPECT_EQ(static_cast<size_t>(0), vec.size());
    EXPECT_EQ(static_cast<size_t>(15), vec.capacity());
}
TEST(TestTVectorLib, check_the_insertion_after_deletion) {
    int* mass = new int[100];
    for (int i = 0; i < 100; i++) {
        mass[i] = i + 1;
    }
    TVector<int> vec(100, mass);
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(3, 6);
    vec.insert(4, 55);
    vec.insert(6, { 33, 44, 55 });
    TVector<int> res({ 2, 3, 5, 10, 55, 11, 33, 44, 55, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
        32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
        64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
        80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
        96, 97, 98, 99 });
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_the_replacement_by_index) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.replace(4, 77);
    TVector<int> res({ 1, 2, 3, 4, 77, 6, 7, 8, 9, 10 });
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_the_replacement_by_index_after_deleted) {
    int* mass = new int[100];
    for (int i = 0; i < 100; i++) {
        mass[i] = i + 1;
    }
    TVector<int> vec(100, mass);
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(3);
    vec.replace(4, 55);
    TVector<int> res({ 2, 3, 5, 7, 55, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
        33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
        49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
        65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
        81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
        97, 98, 99 });
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_at) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    size_t res = vec.at(4);
    EXPECT_EQ(5, res);
}
TEST(TestTVectorLib, check_the_exception_in_at) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    ASSERT_ANY_THROW(vec.at(10));
}
TEST(TestTVectorLib, check_assign_value) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.assign(4, 66);
    TVector<int> res({ 66, 66, 66, 66 });
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_assign_list) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    vec.assign({ 11, 22, 33, 44, 55, 66 });
    EXPECT_EQ(vec.front(), 11);
    EXPECT_EQ(vec.back(), 66);
    EXPECT_EQ(vec[3], 44);
}
TEST(TestTVectorLib, check_the_exception_when_going_out_of_bounds) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    ASSERT_ANY_THROW(vec.insert(11, { 2, 3, 4 }));
    ASSERT_ANY_THROW(vec.insert(11, 2, 77));
    ASSERT_ANY_THROW(vec.insert(12, 55));
    ASSERT_ANY_THROW(vec.erase(12));
    ASSERT_ANY_THROW(vec.erase(7, 18));
    ASSERT_ANY_THROW(vec.replace(12, 8));
}
TEST(TestTVectorLib, check_for_an_exception_when_interacting_with_an_empty_vector) {
    TVector<int> vec;
    ASSERT_ANY_THROW(vec.pop_front());
    ASSERT_ANY_THROW(vec.pop_back());
    ASSERT_ANY_THROW(vec.clear());
    ASSERT_ANY_THROW(vec.erase(10));
    ASSERT_ANY_THROW(vec.erase(7, 18));
    ASSERT_ANY_THROW(vec.replace(12, 8));
}
TEST(TestTVectorLib, check_the_insertion_into_an_empty_vector) {
    TVector<int> vec1;
    vec1.push_front(1);
    TVector<int> res1({ 1 });
    TVector<int> vec2;
    vec2.push_back(10);
    TVector<int> res2({ 10 });
    TVector<int> vec3;
    vec3.insert(0, 88);
    TVector<int> res3({ 88 });
    EXPECT_EQ(res1, vec1);
    EXPECT_EQ(res2, vec2);
    EXPECT_EQ(res3, vec3);
}
TEST(TestTVectorLib, check_shuffle_vector) {
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    TVector<int> vec2({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    shuffle(vec2);
    EXPECT_TRUE(vec1 != vec2);
}
TEST(TestTVectorLib, check_hoara_sort) {
    TVector<int> vec({ 2, 7, 3, 9, 28, 38, 93, 9, 6, 4, 2 });
    hoara_sort(vec);
    TVector<int> res({ 2, 2, 3, 4, 6, 7, 9, 9, 28, 38, 93 });
    EXPECT_TRUE(vec == res);
}
TEST(TestTVectorLib, check_find_first_element) {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int pos = find_first_elem_by_index(vec, 5);
    EXPECT_EQ(2, pos);
}
TEST(TestTVectorLib, check_find_first_element_if_there_is_no_element) {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int pos = find_first_elem_by_index(vec, 11);
    EXPECT_EQ(-1, pos);
}
TEST(TestTVectorLib, check_find_last_element) {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int pos = find_last_elem_by_index(vec, 5);
    EXPECT_EQ(4, pos);
}
TEST(TestTVectorLib, check_find_last_element_if_there_is_no_element) {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int pos = find_last_elem_by_index(vec, 11);
    EXPECT_EQ(-1, pos);
}
TEST(TestTVectorLib, check_find_several_elements) {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 5, 9 });
    int* actual_indexes = find_elem_by_index(vec, 5);
    int expected_indexes[] = { 3, 2, 4, 8 };
    bool expected_result = true;
    bool actual_result = true;
    for (size_t i = 0; i < 3; i++) {
        if (actual_indexes[i] == expected_indexes[i])
            actual_result &= true;
        else
            actual_result &= false;
    }
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestTVectorLib, check_find_several_elements_if_there_is_no_element) {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 5, 9 });
    int* indexes = find_elem_by_index(vec, 15);
    EXPECT_EQ(0, indexes[0]);
}
TEST(TestTVectorLib, check_find_first_elem_after_deletion) {
    int* mass = new int[100];
    for (int i = 0; i < 100; i++) {
        mass[i] = i + 1;
    }
    TVector<int> vec(100, mass);
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(3);
    int pos = find_first_elem_by_index(vec, 7);
    EXPECT_EQ(3, pos);
}
TEST(TestTVectorLib, check_find_last_elem_after_deletion) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
        35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
        53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
        71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88,
        89, 90, 91, 92, 93, 94, 95, 96, 7, 97, 98, 99, 100 });
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(3);
    int pos = find_last_elem_by_index(vec, 7);
    EXPECT_EQ(vec.front(), 2);
    EXPECT_EQ(vec.back(), 99);
    EXPECT_EQ(vec[3], 7);
    EXPECT_EQ(93, pos);
}
TEST(TestTVectorLib, check_find_all_elements_after_deletion) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 7, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
        34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
        52, 53, 54, 7, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
        69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
        7, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 });
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(30);
    vec.erase(3);
    int* indexes = find_elem_by_index(vec, 7);
    int right_indexes[] = { 4, 3, 17, 51, 84 };
    bool actual_result = true;
    bool expected_result = true;
    for (size_t i = 0; i < 5; i++) {
        if (indexes[i] == right_indexes[i])
            actual_result &= true;
        else
            actual_result &= false;
    }
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestTVectorLib, check_the_replacement_by_the_pointer) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 7, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
        34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
        52, 53, 54, 7, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
        69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
        7, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 });
    bool expected_result = true;
    vec.erase(2);
    vec.replace(vec.begin() + 4, 99);
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(99, vec[4]);
}
TEST(TestTVectorLib, check_shifted_insert_into_a_full_array_with_deleted_elems) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 });
    bool expected_result = true;
    vec.erase(2);
    vec.erase(5);
    vec.insert(5, 88);
    vec.insert(7, 99);
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(88, vec[5]);
    EXPECT_EQ(99, vec[7]);
    EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
}
TEST(TestTVectorLib, check_find_first_element_2) {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int* ptr = find_first_elem_by_pointer(vec, 5);
    EXPECT_EQ(&vec[2], ptr);
    EXPECT_EQ(5, *ptr);
}
TEST(TestTVectorLib, check_find_first_element_if_there_is_no_element_2) {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int* ptr = find_first_elem_by_pointer(vec, 11);
    EXPECT_EQ(nullptr, ptr);
}
TEST(TestTVectorLib, check_find_last_element_2) {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int* ptr = find_last_elem_by_pointer(vec, 5);
    EXPECT_EQ(&vec[4], ptr);
    EXPECT_EQ(5, *ptr);
}
TEST(TestTVectorLib, check_find_last_element_if_there_is_no_element_2) {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 9 });
    int* ptr = find_last_elem_by_pointer(vec, 11);
    EXPECT_EQ(nullptr, ptr);
}
TEST(TestTVectorLib, check_find_several_elements_2) {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 5, 9 });
    TVector<int*> ptrs = find_elem_by_pointer(vec, 5);
    TVector<int*> true_ptrs({ &vec[2], &vec[4], &vec[8] });
    bool expected_result = true;
    bool actual_result = true;
    for (size_t i = 0; i < ptrs.size(); i++) {
        if (ptrs[i] == true_ptrs[i])
            actual_result &= true;
        else
            actual_result &= false;
    }
    EXPECT_EQ(static_cast<size_t>(3), ptrs.size());
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestTVectorLib, check_find_several_elements_if_there_is_no_element_2) {
    TVector<int> vec({ 1, 2, 5, 4, 5, 3, 6, 7, 5, 9 });
    TVector<int*> ptrs = find_elem_by_pointer(vec, 10);
    EXPECT_EQ(static_cast<size_t>(0), ptrs.size());
}
TEST(TestTVectorLib, check_find_first_elem_after_deletion_2) {
    int* mass = new int[100];
    for (int i = 0; i < 100; i++) {
        mass[i] = i + 1;
    }
    TVector<int> vec(100, mass);
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(3);
    int* ptr = find_first_elem_by_pointer(vec, 7);
    EXPECT_EQ(&vec[3], ptr);
    EXPECT_EQ(7, *ptr);
}
TEST(TestTVectorLib, check_find_last_elem_after_deletion_2) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
        35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
        53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
        71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88,
        89, 90, 91, 92, 93, 94, 95, 96, 7, 97, 98, 99, 100 });
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(3);
    int* ptr = find_last_elem_by_pointer(vec, 7);
    EXPECT_EQ(&vec[93], ptr);
    EXPECT_EQ(7, *ptr);
}
TEST(TestTVectorLib, check_find_all_elements_after_deletion_2) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 7, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
        34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
        52, 53, 54, 7, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
        69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
        7, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 });
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();
    vec.erase(30);
    vec.erase(3);
    TVector<int*> ptrs = find_elem_by_pointer(vec, 7);
    TVector<int*> true_ptrs({ &vec[3], &vec[17], &vec[51], &vec[84] });
    bool expected_result = true;
    bool actual_result = true;
    for (size_t i = 0; i < ptrs.size(); i++) {
        if (ptrs[i] == true_ptrs[i])
            actual_result &= true;
        else
            actual_result &= false;
    }
    EXPECT_EQ(static_cast<size_t>(4), ptrs.size());
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestTVectorLib, check_the_replace_by_the_pointer_after_searching_and_deleting) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 7, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
        34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
        52, 53, 54, 7, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
        69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
        7, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 });
    int* ptr = find_first_elem_by_pointer(vec, 10);
    vec.erase(9);
    ASSERT_ANY_THROW(vec.replace(ptr, 99));
}
TEST(TestTVectorLib, check_shifted_insert_into_a_full_array_with_deleted_elems_2) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 });
    vec.erase(2);
    vec.erase(5);
    vec.insert(3, 2, 77);
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(77, vec[3]);
    EXPECT_EQ(77, vec[4]);
    EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
}
TEST(TestTVectorLib, check_shifted_insert_into_a_full_array_with_deleted_elems_3) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 });
    vec.erase(2);
    vec.erase(3);
    vec.insert(3, { 3, 6 });
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(3, vec[3]);
    EXPECT_EQ(6, vec[4]);
    EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
}
TEST(TestTVectorLib, check_shifted_push_front_into_a_full_array_with_deleted_elems) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 });
    bool expected_result = true;
    vec.erase(2);
    vec.erase(3);
    vec.push_front(11);
    vec.push_front(22);
    EXPECT_EQ(22, vec.front());
    EXPECT_EQ(11, vec[1]);
    EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
}
TEST(TestTVectorLib, check_shifted_push_back_into_a_full_array_with_deleted_elems) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 });
    bool expected_result = true;
    vec.erase(2);
    vec.erase(3);
    vec.push_back(11);
    vec.push_back(22);
    EXPECT_EQ(22, vec.back());
    EXPECT_EQ(11, vec[27]);
    EXPECT_EQ(static_cast<size_t>(30), vec.capacity());
}
