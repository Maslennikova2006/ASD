// Copyright 2026 Mary Maslennikova

#include <gtest/gtest.h>
#include <string>
#include "../lib_unsorted_table_m/unsorted_table_m.h"

TEST(TestUnsortedTableMLib, can_create_and_check_is_empty) {
    UnsortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(78, "Санкт-Петербург");
    EXPECT_FALSE(table.is_empty());
}
TEST(TestUnsortedTableMLib, check_insert) {
    UnsortedTableM<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    EXPECT_FALSE(table.is_empty());
    ASSERT_NO_THROW(table.insert(97, "Москва"));
}
TEST(TestUnsortedTableMLib, check_for_insertion_exception) {
    UnsortedTableM<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    ASSERT_ANY_THROW(table.insert(52, "Нижегородская область"));
}
TEST(TestUnsortedTableMLib, check_erase) {
    UnsortedTableM<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    ASSERT_NO_THROW(table.erase(52));
    EXPECT_TRUE(table.is_empty());
}
TEST(TestUnsortedTableMLib, check_for_deletion_exception) {
    UnsortedTableM<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    ASSERT_ANY_THROW(table.erase(25));
}
TEST(TestUnsortedTableMLib, check_found) {
    UnsortedTableM<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(97, "Москва");
    table.insert(16, "Казань");
    EXPECT_EQ(*table.found(52), "Нижний Новгород");
    EXPECT_EQ(table.found(25), nullptr);
}