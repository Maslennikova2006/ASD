// Copyright 2026 Mary Maslennikova

#include <gtest/gtest.h>
#include <string>
#include "../lib_sorted_table_avl/sorted_table_avl.h"

TEST(TestSortedTableAVLLib, can_create_and_check_is_empty) {
    SortedTableAVL<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(78, "Санкт-Петербург");
    EXPECT_FALSE(table.is_empty());
}
TEST(TestSortedTableAVLLib, check_insert) {
    SortedTableAVL<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    EXPECT_FALSE(table.is_empty());
    ASSERT_NO_THROW(table.insert(97, "Москва"));
}
TEST(TestSortedTableAVLLib, check_for_insertion_exception) {
    SortedTableAVL<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(16, "Казань");
    table.insert(97, "Москва");
    ASSERT_ANY_THROW(table.insert(52, "Нижегородская область"));
}
TEST(TestSortedTableAVLLib, check_erase) {
    SortedTableAVL<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    ASSERT_NO_THROW(table.erase(52));
    EXPECT_TRUE(table.is_empty());
}
TEST(TestSortedTableAVLLib, check_for_deletion_exception) {
    SortedTableAVL<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    ASSERT_ANY_THROW(table.erase(25));
    table.insert(78, "Санкт-Петербург");
    table.insert(97, "Москва");
    ASSERT_ANY_THROW(table.erase(90));
}
TEST(TestSortedTableAVLLib, check_found) {
    SortedTableAVL<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(97, "Москва");
    table.insert(16, "Казань");
    EXPECT_EQ(*table.found(52), "Нижний Новгород");
    EXPECT_EQ(table.found(25), nullptr);
}
TEST(TestSortedTableAVLLib, check_the_sorting) {
    SortedTableAVL<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(97, "Москва");
    table.insert(16, "Казань");
    table.insert(78, "Санкт-Петербург");
    table.insert(55, "Омск");
    table.insert(18, "Ижевск");
    auto root = table.rows().root();
    EXPECT_EQ(root->data.first, 52);
    EXPECT_EQ(root->left->data.first, 16);
    EXPECT_EQ(root->left->right->data.first, 18);
    EXPECT_EQ(root->right->data.first, 78);
    EXPECT_EQ(root->right->left->data.first, 55);
    EXPECT_EQ(root->right->right->data.first, 97);
}
