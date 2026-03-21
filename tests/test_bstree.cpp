// Copyright 2026 Mary Maslennikova

#include <gtest/gtest.h>
#include <string>
#include "../lib_bstree/bstree.h"

TEST(TestBSTreeLib, can_create_and_check_is_empty) {
    BSTree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
    tree.insert(78, "78");
    EXPECT_FALSE(tree.is_empty());
}
TEST(TestBSTreeLib, check_insert) {
    BSTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    tree.insert(20, "20");
    auto root = tree.root();
    EXPECT_EQ(root->data.first, 52);
    EXPECT_EQ(root->left->data.first, 22);
    EXPECT_EQ(root->left->left->data.first, 20);
    EXPECT_EQ(root->left->right->data.first, 23);
    EXPECT_EQ(root->right->data.first, 88);
}
TEST(TestBSTreeLib, check_for_insertion_exception) {
    BSTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    ASSERT_ANY_THROW(tree.insert(22, "20"));
}
TEST(TestBSTreeLib, check_find) {
    BSTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    tree.insert(60, "60");
    tree.insert(90, "90");
    auto expected = tree.find(28);
    EXPECT_EQ(expected, nullptr);
    auto expected2 = tree.find(60);
    EXPECT_EQ(*expected2, "60");
}
TEST(TestBSTreeLib, check_the_erase_of_the_sheet) {
    BSTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    tree.insert(55, "55");
    tree.insert(67, "67");
    tree.erase(67);
    auto expected = tree.find(67);
    EXPECT_EQ(expected, nullptr);
    EXPECT_EQ(tree.root()->right->left->right, nullptr);
}
TEST(TestBSTreeLib, check_the_erase_of_a_node_with_one_child) {
    BSTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    tree.insert(55, "55");
    tree.insert(67, "67");
    tree.erase(22);  // один правый ребенок
    auto expected = tree.find(22);
    EXPECT_EQ(expected, nullptr);
    EXPECT_EQ(tree.root()->left->data.first, 23);
    tree.erase(88);
    auto expected2 = tree.find(88);
    EXPECT_EQ(expected2, nullptr);
    EXPECT_EQ(tree.root()->right->data.first, 55);
}
TEST(TestBSTreeLib, check_the_erase_of_a_node_with_two_children) {
    BSTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(20, "20");
    tree.insert(88, "88");
    tree.insert(55, "55");
    tree.insert(23, "23");
    tree.insert(67, "67");
    tree.insert(90, "90");
    tree.erase(88);
    auto expected = tree.find(88);
    EXPECT_EQ(expected, nullptr);
    EXPECT_EQ(tree.root()->right->data.first, 67);
    EXPECT_EQ(tree.root()->right->right->data.first, 90);
    tree.erase(52);
    auto expected2 = tree.find(52);
    EXPECT_EQ(expected2, nullptr);
    EXPECT_EQ(tree.root()->data.first, 23);
    EXPECT_EQ(tree.root()->left->data.first, 22);
}
TEST(TestBSTreeLib, check_the_exception_when_erase_from_an_empty_tree) {
    BSTree<int, std::string> tree;
    ASSERT_ANY_THROW(tree.erase(6));
}
TEST(TestBSTreeLib, check_for_an_exception_when_deleting_no_exist_key) {
    BSTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    ASSERT_ANY_THROW(tree.erase(5));
}
TEST(TestBSTreeLib, check_clear) {
    BSTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
}