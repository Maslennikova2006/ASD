// Copyright 2026 Mary Maslennikova

#include <gtest/gtest.h>
#include <string>
#include "../lib_unsorted_table_bt/unsorted_table_bt.h"

TEST(TestUnsortedTableBTLib, can_create_and_check_is_empty) {
    UnsortedTableBT<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(78, "Санкт-Петербург");
    EXPECT_FALSE(table.is_empty());
}
TEST(TestUnsortedTableBTLib, check_insert) {
    UnsortedTableBT<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    EXPECT_FALSE(table.is_empty());
    ASSERT_NO_THROW(table.insert(97, "Москва"));
}
TEST(TestUnsortedTableBTLib, check_for_insertion_exception) {
    UnsortedTableBT<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    ASSERT_ANY_THROW(table.insert(52, "Нижегородская область"));
}
TEST(TestUnsortedTableBTLib, check_erase) {
    UnsortedTableBT<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    ASSERT_NO_THROW(table.erase(52));
    EXPECT_TRUE(table.is_empty());
}
TEST(TestUnsortedTableBTLib, check_for_deletion_exception) {
    UnsortedTableBT<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    ASSERT_ANY_THROW(table.erase(25));
}
TEST(TestUnsortedTableBTLib, check_found) {
    UnsortedTableBT<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(97, "Москва");
    table.insert(16, "Казань");
    EXPECT_EQ(*table.found(52), "Нижний Новгород");
    EXPECT_EQ(table.found(25), nullptr);
}