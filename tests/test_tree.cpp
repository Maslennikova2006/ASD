// Copyright 2026 Mary Maslennikova

#include <gtest/gtest.h>
#include <string>
#include "../lib_tree/tree.h"

TEST(TestTreeLib, can_create_and_check_is_empty) {
    Tree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
    tree.insert(78, "78");
    EXPECT_FALSE(tree.is_empty());
}
TEST(TestTreeLib, check_insert) {
    Tree<int, std::string> tree;
    tree.insert(52, "52");
    auto expected = tree.find(52);
    EXPECT_EQ(*expected, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    auto expected2 = tree.find(23);
    EXPECT_EQ(*expected2, "23");
}
TEST(TestTreeLib, check_insert_repeat) {
    Tree<int, std::string> tree;
    tree.insert(52, "52");
    ASSERT_NO_THROW(tree.insert(52, "22"));
}
TEST(TestTreeLib, check_find) {
    Tree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    auto expected = tree.find(28);
    EXPECT_EQ(expected, nullptr);
    auto expected2 = tree.find(88);
    EXPECT_EQ(*expected2, "88");
}
TEST(TestTreeLib, check_find_2) {
    Tree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(52, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    auto expected2 = tree.find(52);
    EXPECT_EQ(*expected2, "52");
}
TEST(TestTreeLib, check_the_erase_of_the_sheet) {
    Tree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    tree.insert(55, "55");
    tree.insert(67, "67");
    tree.insert(75, "75");
    tree.erase(75);
    auto expected = tree.find(75);
    EXPECT_EQ(expected, nullptr);
}
TEST(TestTreeLib, check_the_erase_from_the_middle) {
    Tree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    tree.insert(55, "55");
    tree.insert(67, "67");
    tree.erase(22);
    auto expected2 = tree.find(22);
    EXPECT_EQ(expected2, nullptr);
    EXPECT_EQ(tree.root()->left->data.first, 67);
}
TEST(TestTreeLib, check_root_erase) {
    Tree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    tree.insert(55, "55");
    tree.insert(67, "67");
    tree.insert(75, "75");
    tree.erase(52);
    auto expected3 = tree.find(52);
    EXPECT_EQ(expected3, nullptr);
    EXPECT_EQ(tree.root()->data.first, 75);
}
TEST(TestTreeLib, check_erase_repeate) {
    Tree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(52, "22");
    tree.insert(23, "23");
    tree.erase(52);
    auto expected3 = tree.find(52);
    EXPECT_EQ(*expected3, "22");
}
TEST(TestTreeLib, check_the_exception_when_erase_from_an_empty_tree) {
    Tree<int, std::string> tree;
    ASSERT_ANY_THROW(tree.erase(6));
}
TEST(TestTreeLib, check_for_an_exception_when_deleting_no_exist_key) {
    Tree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    ASSERT_ANY_THROW(tree.erase(5));
}
TEST(TestTreeLib, check_clear) {
    Tree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
}