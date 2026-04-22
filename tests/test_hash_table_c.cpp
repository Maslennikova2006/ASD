// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_hash_table_c/hashtablec.h"

TEST(TestHashTableCLib, can_create_and_check_is_empty) {
    HashTableC<std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert("78", "Санкт-Петербург");
    EXPECT_FALSE(table.is_empty());
}
TEST(TestHashTableCLib, check_insert) {
    HashTableC<std::string> table;
    table.insert("52", "Нижний Новгород");
    EXPECT_FALSE(table.is_empty());
    ASSERT_NO_THROW(table.insert("97", "Москва"));
}
TEST(TestHashTableCLib, check_for_insertion_exception) {
    HashTableC<std::string> table;
    table.insert("52", "Нижний Новгород");
    ASSERT_ANY_THROW(table.insert("52", "Нижегородская область"));
}
TEST(TestHashTableCLib, check_for_deletion_from_the_beginning) {
    HashTableC<std::string> table;
    table.insert("52", "Нижний Новгород");
    ASSERT_NO_THROW(table.erase("52"));
    EXPECT_TRUE(table.is_empty());
}
TEST(TestHashTableCLib, check_for_deletion_from_the_middle) {
    HashTableC<std::string> table;
    table.insert("52", "Нижний Новгород");
    table.insert("25", "Приморский край");
    ASSERT_NO_THROW(table.erase("25"));
    EXPECT_EQ(table.found("25"), nullptr);
}
TEST(TestHashTableCLib, check_for_deletion_exception) {
    HashTableC<std::string> table;
    table.insert("52", "Нижний Новгород");
    ASSERT_ANY_THROW(table.erase("25"));
}
TEST(TestHashTableCLib, check_found) {
    HashTableC<std::string> table;
    table.insert("52", "Нижний Новгород");
    table.insert("97", "Москва");
    table.insert("16", "Казань");
    EXPECT_EQ(*table.found("52"), "Нижний Новгород");
    EXPECT_EQ(table.found("25"), nullptr);
}