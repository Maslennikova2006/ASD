// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_dlist/dlist.h"

TEST(TestDListLib, can_create) {
    ASSERT_NO_THROW(DList<int> list);
}
TEST(TestDListLib, can_create_2) {
    DList<int> list;
    EXPECT_EQ(nullptr, list.head());
    EXPECT_EQ(nullptr, list.tail());
    EXPECT_EQ((size_t)0, list.get_count());
}
TEST(TestDListLib, can_create_copy_constructor) {
    DList<int> list;
    ASSERT_NO_THROW(DList<int>(list));
}
TEST(TestDListLib, check_for_emptiness) {
    DList<int> list;
    EXPECT_TRUE(list.is_empty());
}
TEST(TestDListLib, check_for_emptiness_2) {
    DList<int> list;
    list.push_back(5);
    list.push_back(6);
    EXPECT_FALSE(list.is_empty());
}
TEST(TestDListLib, check_push_back) {
    DList<int> list;
    list.push_back(5);
    list.push_back(6);
    EXPECT_EQ(list.head()->value, 5);
    EXPECT_EQ(list.tail()->value, 6);
    EXPECT_EQ(list.head()->next, list.tail());
    EXPECT_EQ(list.tail()->prev, list.head());
    EXPECT_EQ((size_t)2, list.get_count());
}
TEST(TestDListLib, check_push_front) {
    DList<int> list;
    list.push_front(15);
    list.push_front(35);
    EXPECT_EQ(list.head()->value, 35);
    EXPECT_EQ(list.tail()->value, 15);
    EXPECT_EQ(list.head()->next, list.tail());
    EXPECT_EQ(list.tail()->prev, list.head());
    EXPECT_EQ((size_t)2, list.get_count());
}
TEST(TestDListLib, check_insert_by_pointer) {
    DList<int> list;
    list.push_front(15);
    list.push_front(25);
    list.push_front(35);
    list.insert(list.head()->next, 55);
    EXPECT_EQ(list.head()->next->next->value, 55);
    EXPECT_EQ(list.head()->next->next->prev->value, 25);
    EXPECT_EQ(list.head()->next->next->next->value, 15);
    EXPECT_EQ((size_t)4, list.get_count());
}
TEST(TestDListLib, check_insert_by_pointer_when_list_is_empty) {
    DList<int> list;
    ASSERT_ANY_THROW(list.insert(list.head(), 55));
}
TEST(TestDListLib, check_insert_front_by_pos) {
    DList<int> list;
    list.push_front(25);
    list.insert((size_t)0, 55);
    EXPECT_EQ(list.head()->value, 55);
    EXPECT_EQ(list.head()->next->prev->value, 55);
    EXPECT_EQ(list.tail()->value, 25);
    EXPECT_EQ((size_t)2, list.get_count());
}
TEST(TestDListLib, check_insert_back_by_pos) {
    DList<int> list;
    list.push_back(77);
    list.insert((size_t)1, 55);
    EXPECT_EQ(list.head()->value, 77);
    EXPECT_EQ(list.head()->next->prev->value, 77);
    EXPECT_EQ(list.tail()->value, 55);
    EXPECT_EQ((size_t)2, list.get_count());
}
TEST(TestDListLib, check_insert_by_pos) {
    DList<int> list;
    list.push_back(34);
    list.push_back(72);
    list.push_front(27);
    list.insert((size_t)1, 55);
    EXPECT_EQ(list.head()->value, 27);
    EXPECT_EQ(list.head()->next->prev->value, 27);
    EXPECT_EQ(list.tail()->value, 72);
    EXPECT_EQ((size_t)4, list.get_count());
}
TEST(TestDListLib, check_insert_by_pos_when_wrong_pos) {
    DList<int> list;
    list.push_back(34);
    list.push_back(72);
    list.push_front(27);
    ASSERT_ANY_THROW(list.insert((size_t)5, 88));
}
TEST(TestDListLib, check_pop_back_when_list_is_empty) {
    DList<int> list;
    ASSERT_ANY_THROW(list.pop_back());
}
TEST(TestDListLib, check_pop_back_when_one_elem_in_list) {
    DList<int> list;
    list.push_back(44);
    list.push_back(33);
    list.push_back(22);
    list.pop_back();
    EXPECT_EQ(list.tail()->prev->value, 44);
    EXPECT_EQ(list.tail()->value, 33);
    EXPECT_EQ((size_t)2, list.get_count());
}
TEST(TestDListLib, check_pop_back) {
    DList<int> list;
    list.push_back(7);
    list.push_back(4);
    list.push_back(84);
    list.push_back(37);
    list.pop_back();
    EXPECT_EQ(list.tail()->prev->value, 4);
    EXPECT_EQ(list.tail()->value, 84);
    EXPECT_EQ((size_t)3, list.get_count());
}
TEST(TestDListLib, check_pop_front_when_list_is_empty) {
    DList<int> list;
    ASSERT_ANY_THROW(list.pop_front());
}
TEST(TestDListLib, check_pop_front_when_one_elem_in_list) {
    DList<int> list;
    list.push_back(44);
    list.pop_front();
    EXPECT_EQ(nullptr, list.head());
    EXPECT_EQ(nullptr, list.tail());
    EXPECT_EQ((size_t)0, list.get_count());
}
TEST(TestDListLib, check_pop_front) {
    DList<int> list;
    list.push_back(7);
    list.push_back(4);
    list.push_back(84);
    list.push_back(37);
    list.pop_front();
    EXPECT_EQ(list.head()->value, 4);
    EXPECT_EQ(list.head()->prev, nullptr);
    EXPECT_EQ((size_t)3, list.get_count());
}
TEST(TestDListLib, check_erase_by_pointer_when_list_is_empty) {
    DList<int> list;
    ASSERT_ANY_THROW(list.erase(list.head()));
}
TEST(TestDListLib, check_erase_by_pointer) {
    DList<int> list;
    list.push_back(7);
    list.push_back(4);
    list.push_back(84);
    list.push_back(48);
    list.push_back(54);
    list.erase(list.head()->next->next);
    EXPECT_EQ(list.head()->value, 7);
    EXPECT_EQ(list.head()->next->next->value, 48);
    EXPECT_EQ(list.head()->next->next->prev->value, 4);
    EXPECT_EQ((size_t)4, list.get_count());
}
TEST(TestDListLib, check_erase_front_by_pos) {
    DList<int> list;
    list.push_back(7);
    list.insert((size_t)0, 55);
    list.erase((size_t)0);
    EXPECT_EQ(list.head()->value, 7);
    EXPECT_EQ(list.head()->prev, nullptr);
    EXPECT_EQ((size_t)1, list.get_count());
}
TEST(TestDListLib, check_erase_back_by_pos) {
    DList<int> list;
    list.push_back(77);
    list.insert((size_t)1, 55);
    list.erase((size_t)1);
    EXPECT_EQ(list.tail()->value, 77);
    EXPECT_EQ(list.tail()->next, nullptr);
    EXPECT_EQ((size_t)1, list.get_count());
}
TEST(TestDListLib, check_erase_by_pos) {
    DList<int> list;
    list.push_back(34);
    list.push_back(72);
    list.push_back(72);
    list.push_front(27);
    list.erase((size_t)1);
    EXPECT_EQ(list.head()->next->value, 72);
    EXPECT_EQ(list.head()->next->prev->value, 27);
    EXPECT_EQ(list.tail()->value, 72);
    EXPECT_EQ((size_t)3, list.get_count());
}
TEST(TestDListLib, check_erase_by_pos_when_wrong_pos) {
    DList<int> list;
    list.push_back(34);
    list.push_back(72);
    list.push_front(27);
    ASSERT_ANY_THROW(list.erase((size_t)5));
}
TEST(TestDListLib, check_iterator_when_list_is_empty) {
    DList<int> list;
    DList<int>::Iterator it;
    bool enter—ycle = false;
    for (it = list.begin(); it != list.end(); it++) {
        enter—ycle = true;
    }
    EXPECT_FALSE(enter—ycle);
}
TEST(TestDListLib, check_iterator_for_reading) {
    DList<int> list;
    DList<int>::Iterator it;
    for (int i = 0; i < 10; i++) {
        list.push_back(i + 1);
    }
    int i = 1;
    for (it = list.begin(); it != list.end(); it++) {
        EXPECT_EQ(i, *it);
        i++;
    }
}
TEST(TestDListLib, check_iterator_for_reading_2) {
    DList<int> list;
    DList<int>::Iterator it;
    for (int i = 10; i < 0; i--) {
        list.push_back(i);
    }
    int i = 10;
    for (it = list.end(); it != list.begin(); it--) {
        EXPECT_EQ(i, *it);
        i--;
    }
}
TEST(TestDListLib, check_iterator_for_writting) {
    DList<int> list;
    DList<int>::Iterator it;
    int i = 1;
    for (it = list.begin(); it != list.end(); it++) {
        *it = i;
        EXPECT_EQ(i, *it);
        i++;
    }
}
TEST(TestDListLib, check_iterator_for_writting_2) {
    DList<int> list;
    DList<int>::Iterator it;
    int i = 1;
    for (it = list.end(); it != list.begin(); it--) {
        *it = i;
        EXPECT_EQ(i, *it);
        i++;
    }
}