// Copyright 2026 Mary Maslennikova

#include <gtest/gtest.h>
#include <string>
#include "../lib_avltree/avltree.h"

TEST(TestAVLTreeLib, can_create_and_check_is_empty) {
    AVLTree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
    tree.insert(78, "78");
    EXPECT_FALSE(tree.is_empty());
}
TEST(TestAVLTreeLib, check_insert) {
    AVLTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    tree.insert(20, "20");
    auto root = tree.root();
    EXPECT_EQ(root->data.first, 23);
    EXPECT_EQ(root->left->data.first, 22);
    EXPECT_EQ(root->left->left->data.first, 20);
    EXPECT_EQ(root->right->data.first, 52);
    EXPECT_EQ(root->right->right->data.first, 88);
}
TEST(TestAVLTreeLib, check_for_insertion_exception) {
    AVLTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    ASSERT_ANY_THROW(tree.insert(22, "20"));
}
TEST(TestAVLTreeLib, check_find) {
    AVLTree<int, std::string> tree;
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
TEST(TestAVLTreeLib, check_the_erase_of_the_sheet) {
    AVLTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    tree.insert(55, "55");
    tree.insert(67, "67");
    tree.insert(20, "20");
    tree.erase(67);
    auto expected = tree.find(67);
    EXPECT_EQ(expected, nullptr);
    EXPECT_EQ(tree.root()->data.first, 23);
}
TEST(TestAVLTreeLib, check_the_erase_of_a_node_with_one_child) {
    AVLTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    tree.insert(55, "55");
    tree.insert(67, "67");
    tree.insert(24, "24");
    tree.erase(52);  // один левый ребенок
    auto expected = tree.find(52);
    EXPECT_EQ(expected, nullptr);
    EXPECT_EQ(tree.root()->left->right->data.first, 24);
    EXPECT_EQ(tree.root()->data.first, 55);
}
TEST(TestAVLTreeLib, check_the_erase_of_a_node_with_two_children) {
    AVLTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(20, "20");
    tree.insert(88, "88");
    tree.insert(55, "55");
    tree.insert(23, "23");
    tree.insert(67, "67");
    tree.insert(90, "90");
    tree.erase(67);  // два ребенка (55 и 88)
    auto expected = tree.find(67);
    EXPECT_EQ(expected, nullptr);
    EXPECT_EQ(tree.root()->right->data.first, 88);
    EXPECT_EQ(tree.root()->right->right->data.first, 90);
    EXPECT_EQ(tree.root()->right->left->data.first, 55);
    tree.erase(52);  // корень
    auto expected2 = tree.find(52);
    EXPECT_EQ(expected2, nullptr);
    EXPECT_EQ(tree.root()->data.first, 23);
}
TEST(TestAVLTreeLib, check_erase) {
    AVLTree<int, std::string> tree;
    tree.insert(55, "55");
    tree.insert(33, "33");
    tree.insert(75, "75");
    tree.insert(10, "10");
    tree.insert(61, "61");
    tree.insert(44, "44");
    tree.insert(83, "83");
    tree.insert(5, "5");
    tree.insert(56, "56");
    tree.insert(79, "79");
    tree.insert(65, "65");
    tree.insert(90, "90");
    tree.insert(85, "85");
    tree.erase(44);
    auto expected = tree.find(44);
    EXPECT_EQ(expected, nullptr);
    EXPECT_EQ(tree.root()->data.first, 75);
    EXPECT_EQ(tree.root()->left->data.first, 55);
    EXPECT_EQ(tree.root()->right->data.first, 83);
    EXPECT_EQ(tree.root()->left->left->data.first, 10);
}
TEST(TestAVLTreeLib, check_erase_root) {
    AVLTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.erase(52);
    auto expected = tree.find(52);
    EXPECT_EQ(expected, nullptr);
    EXPECT_TRUE(tree.is_empty());
}
TEST(TestAVLTreeLib, check_the_exception_when_erase_from_an_empty_tree) {
    AVLTree<int, std::string> tree;
    ASSERT_ANY_THROW(tree.erase(6));
}
TEST(TestAVLTreeLib, check_for_an_exception_when_deleting_no_exist_key) {
    AVLTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    ASSERT_ANY_THROW(tree.erase(5));
}
TEST(TestAVLTreeLib, check_clear) {
    AVLTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
}
