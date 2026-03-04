// Copyright 2026 Mary Maslennikova

#include <gtest/gtest.h>
#include <string>
#include "../lib_sorted_table_m/sorted_table_m.h"

TEST(TestSortedTableMLib, can_create_and_check_is_empty) {
    SortedTableM<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    table.insert(78, "Санкт-Петербург");
    EXPECT_FALSE(table.is_empty());
}
TEST(TestSortedTableMLib, check_insert) {
    SortedTableM<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    EXPECT_FALSE(table.is_empty());
    ASSERT_NO_THROW(table.insert(97, "Москва"));
}
TEST(TestSortedTableMLib, check_for_insertion_exception) {
    SortedTableM<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(16, "Казань");
    table.insert(97, "Москва");
    ASSERT_ANY_THROW(table.insert(52, "Нижегородская область"));
}
TEST(TestSortedTableMLib, check_erase) {
    SortedTableM<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    ASSERT_NO_THROW(table.erase(52));
    EXPECT_TRUE(table.is_empty());
}
TEST(TestSortedTableMLib, check_for_deletion_exception) {
    SortedTableM<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    ASSERT_ANY_THROW(table.erase(25));
    table.insert(78, "Санкт-Петербург");
    table.insert(97, "Москва");
    ASSERT_ANY_THROW(table.erase(90));
}
TEST(TestSortedTableMLib, check_found) {
    SortedTableM<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(97, "Москва");
    table.insert(16, "Казань");
    EXPECT_EQ(*table.found(52), "Нижний Новгород");
    EXPECT_EQ(table.found(25), nullptr);
}
TEST(TestSortedTableMLib, check_the_sorting) {
    SortedTableM<int, std::string> table;
    table.insert(52, "Нижний Новгород");
    table.insert(97, "Москва");
    table.insert(16, "Казань");
    table.insert(78, "Санкт-Петербург");
    table.insert(55, "Омск");
    table.insert(18, "Ижевск");
    TVector<int> expected_keys({ 16, 18, 52, 55, 78, 97 });
    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(expected_keys[i], table.get_rows()[i].first);
    }
}