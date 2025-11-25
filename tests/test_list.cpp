// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_list/list.h"

TEST(TestListLib, can_create) {
    ASSERT_NO_THROW(List<int> list);
}
TEST(TestListLib, can_create_2) {
    List<int> list;
    EXPECT_EQ(nullptr, list.head());
    EXPECT_EQ(nullptr, list.tail());
    EXPECT_EQ((size_t)0, list.get_count());
}
TEST(TestListLib, can_create_copy_constructor) {
    List<int> list;
    ASSERT_NO_THROW(List<int>(list));
}
TEST(TestListLib, check_for_emptiness) {
    List<int> list;
    EXPECT_TRUE(list.is_empty());
}
TEST(TestListLib, check_for_emptiness_2) {
    List<int> list;
    list.push_back(5);
    list.push_back(6);
    EXPECT_FALSE(list.is_empty());
}
TEST(TestListLib, check_push_back) {
    List<int> list;
    list.push_back(5);
    list.push_back(6);
    EXPECT_EQ(list.head()->value, 5);
    EXPECT_EQ(list.tail()->value, 6);
    EXPECT_EQ((size_t)2, list.get_count());
}
TEST(TestListLib, check_push_front) {
    List<int> list;
    list.push_front(15);
    list.push_front(35);
    EXPECT_EQ(list.head()->value, 35);
    EXPECT_EQ(list.tail()->value, 15);
    EXPECT_EQ((size_t)2, list.get_count());
}
TEST(TestListLib, check_insert_by_pointer) {
    List<int> list;
    list.push_front(15);
    list.push_front(25);
    list.push_front(35);
    list.insert(list.head()->next, 55);
    EXPECT_EQ(list.head()->next->next->value, 55);
    EXPECT_EQ(list.head()->value, 35);
    EXPECT_EQ(list.tail()->value, 15);
    EXPECT_EQ((size_t)4, list.get_count());
}
TEST(TestListLib, check_insert_by_pointer_when_list_is_empty) {
    List<int> list;
    ASSERT_ANY_THROW(list.insert(list.head(), 55));
}
TEST(TestListLib, check_insert_front_by_pos) {
    List<int> list;
    list.insert((size_t)0, 55);
    EXPECT_EQ(list.head()->value, 55);
    EXPECT_EQ(list.tail()->value, 55);
    EXPECT_EQ((size_t)1, list.get_count());
}
TEST(TestListLib, check_insert_back_by_pos) {
    List<int> list;
    list.push_back(77);
    list.insert((size_t)1, 55);
    EXPECT_EQ(list.head()->value, 77);
    EXPECT_EQ(list.tail()->value, 55);
    EXPECT_EQ((size_t)2, list.get_count());
}
TEST(TestListLib, check_insert_by_pos) {
    List<int> list;
    list.push_back(34);
    list.push_back(72);
    list.push_front(27);
    list.insert((size_t)1, 55);
    EXPECT_EQ(list.head()->value, 27);
    EXPECT_EQ(list.tail()->value, 72);
    EXPECT_EQ((size_t)4, list.get_count());
}
TEST(TestListLib, check_insert_by_pos_when_wrong_pos) {
    List<int> list;
    list.push_back(34);
    list.push_back(72);
    list.push_front(27);
    ASSERT_ANY_THROW(list.insert((size_t)5, 88));
}
TEST(TestListLib, check_pop_back_when_list_is_empty) {
    List<int> list;
    ASSERT_ANY_THROW(list.pop_back());
}
TEST(TestListLib, check_pop_back_when_one_elem_in_list) {
    List<int> list;
    list.push_back(44);
    list.pop_back();
    EXPECT_EQ(nullptr, list.head());
    EXPECT_EQ(nullptr, list.tail());
    EXPECT_EQ((size_t)0, list.get_count());
}
TEST(TestListLib, check_pop_back) {
    List<int> list;
    list.push_back(7);
    list.push_back(4);
    list.push_back(84);
    list.push_back(37);
    list.pop_back();
    EXPECT_EQ(list.head()->value, 7);
    EXPECT_EQ(list.tail()->value, 84);
    EXPECT_EQ((size_t)3, list.get_count());
}
TEST(TestListLib, check_pop_front_when_list_is_empty) {
    List<int> list;
    ASSERT_ANY_THROW(list.pop_front());
}
TEST(TestListLib, check_pop_front_when_one_elem_in_list) {
    List<int> list;
    list.push_back(44);
    list.pop_front();
    EXPECT_EQ(nullptr, list.head());
    EXPECT_EQ(nullptr, list.tail());
    EXPECT_EQ((size_t)0, list.get_count());
}
TEST(TestListLib, check_pop_front) {
    List<int> list;
    list.push_back(7);
    list.push_back(4);
    list.push_back(84);
    list.push_back(37);
    list.pop_front();
    EXPECT_EQ(list.head()->value, 4);
    EXPECT_EQ(list.tail()->value, 37);
    EXPECT_EQ((size_t)3, list.get_count());
}
TEST(TestListLib, check_erase_by_pointer_when_list_is_empty) {
    List<int> list;
    ASSERT_ANY_THROW(list.erase(list.head()));
}
TEST(TestListLib, check_erase_by_pointer) {
    List<int> list;
    list.push_back(7);
    list.push_back(4);
    list.push_back(84);
    list.push_back(48);
    list.push_back(54);
    list.erase(list.head()->next->next);
    EXPECT_EQ(list.head()->value, 7);
    EXPECT_EQ(list.head()->next->next->value, 48);
    EXPECT_EQ(list.tail()->value, 54);
    EXPECT_EQ((size_t)4, list.get_count());
}
TEST(TestListLib, check_erase_front_by_pos) {
    List<int> list;
    list.push_back(7);
    list.insert((size_t)0, 55);
    list.erase((size_t)0);
    EXPECT_EQ(list.head()->value, 7);
    EXPECT_EQ(list.tail()->value, 7);
    EXPECT_EQ((size_t)1, list.get_count());
}
TEST(TestListLib, check_erase_back_by_pos) {
    List<int> list;
    list.push_back(77);
    list.insert((size_t)1, 55);
    list.erase((size_t)1);
    EXPECT_EQ(list.head()->value, 77);
    EXPECT_EQ(list.tail()->value, 77);
    EXPECT_EQ((size_t)1, list.get_count());
}
TEST(TestListLib, check_erase_by_pos) {
    List<int> list;
    list.push_back(34);
    list.push_back(72);
    list.push_back(88);
    list.push_front(27);
    list.erase((size_t)1);
    EXPECT_EQ(list.head()->value, 27);
    EXPECT_EQ(list.head()->next->value, 88);
    EXPECT_EQ(list.tail()->value, 88);
    EXPECT_EQ((size_t)3, list.get_count());
}
TEST(TestListLib, check_erase_by_pos_when_wrong_pos) {
    List<int> list;
    list.push_back(34);
    list.push_back(72);
    list.push_front(27);
    ASSERT_ANY_THROW(list.erase((size_t)5));
}
TEST(TestListLib, check_iterator_when_list_is_empty) {
    List<int> list;
    List<int>::Iterator it;
    bool enterCycle = false;
    for (it = list.begin(); it != list.end(); it++) {
        enterCycle = true;
    }
    EXPECT_FALSE(enterCycle);
}
TEST(TestListLib, check_iterator_for_reading) {
    List<int> list;
    List<int>::Iterator it;
    for (int i = 0; i < 10; i++) {
        list.push_back(i + 1);
    }
    int i = 1;
    for (it = list.begin(); it != list.end(); it++) {
        EXPECT_EQ(i, *it);
        i++;
    }
    it = list.begin();
    EXPECT_EQ(1, *(it++));
    EXPECT_EQ(4, *(it+=2));
    EXPECT_EQ(5, *(++it));
}
TEST(TestListLib, check_iterator_for_writting) {
    List<int> list;
    List<int>::Iterator it;
    int i = 1;
    for (int i = 0; i < 10; i++) {
        list.push_back(i + 1);
    }
    for (it = list.begin(); it != list.end(); it++) {
        *it = i + 2;
        EXPECT_EQ(i + 2, *it);
        i++;
    }
    it = list.begin();
    EXPECT_EQ(3, *(it++));
    EXPECT_EQ(6, *(it += 2));
    EXPECT_EQ(7, *(++it));
}