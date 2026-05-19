// Copyright 2026 Mary Maslennikova

#include <gtest/gtest.h>
#include <string>
#include "../lib_rbtree/rbtree.h"

TEST(TestRBTreeLib, can_create_and_check_is_empty) {
    RBTree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
    tree.insert(78, "78");
    EXPECT_FALSE(tree.is_empty());
}
TEST(TestRBTreeLib, check_insert) {
    RBTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    tree.insert(20, "20");
    auto root = tree.root();
    EXPECT_EQ(root->color, black);
    EXPECT_EQ(root->left->color, black);
    EXPECT_EQ(root->left->left->color, red);
    EXPECT_EQ(root->right->color, black);
    EXPECT_EQ(root->right->right->color, red);
}
TEST(TestRBTreeLib, check_insert2) {
    RBTree<int, std::string> tree;
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
    auto root = tree.root();
    EXPECT_EQ(root->color, black);  // 55
    EXPECT_EQ(root->left->color, black);  // 33
    EXPECT_EQ(root->left->left->color, black);  // 10
    EXPECT_EQ(root->left->right->color, black);  // 44
    EXPECT_EQ(root->left->left->left->color, red);  // 5
    EXPECT_EQ(root->right->color, black);  // 75
    EXPECT_EQ(root->right->right->color, red);  // 83
    EXPECT_EQ(root->right->right->left->color, black);  // 79
    EXPECT_EQ(root->right->right->right->color, black);  // 90
    EXPECT_EQ(root->right->left->color, black);  // 61
    EXPECT_EQ(root->right->left->left->color, red);  // 56
    EXPECT_EQ(root->right->left->right->color, red);  // 65
    EXPECT_EQ(root->right->right->right->left->color, red);  // 85
}
TEST(TestRBTreeLib, check_insert3) {
    RBTree<int, std::string> tree;
    tree.insert(55, "55");
    tree.insert(33, "33");
    tree.insert(73, "73");
    tree.insert(20, "20");
    tree.insert(25, "25");
    auto root = tree.root();
    EXPECT_EQ(root->color, black);  // 55
    EXPECT_EQ(root->left->color, black);  // 25
    EXPECT_EQ(root->left->left->color, red);  // 20
    EXPECT_EQ(root->left->right->color, red);  // 33
    EXPECT_EQ(root->right->color, black);  // 73
    EXPECT_EQ(root->data.first, 55);
    EXPECT_EQ(root->left->data.first, 25);
    EXPECT_EQ(root->left->left->data.first, 20);
    EXPECT_EQ(root->left->right->data.first, 33);
    EXPECT_EQ(root->right->data.first, 73);
}
TEST(TestRBTreeLib, check_for_insertion_exception) {
    RBTree<int, std::string> tree;
    tree.insert(52, "52");
    tree.insert(22, "22");
    tree.insert(23, "23");
    tree.insert(88, "88");
    ASSERT_ANY_THROW(tree.insert(22, "20"));
}
TEST(TestRBTreeLib, check_find) {
    RBTree<int, std::string> tree;
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
    auto expected = tree.find(28);
    EXPECT_EQ(expected, nullptr);
    auto expected2 = tree.find(61);
    EXPECT_EQ(*expected2, "61");
}
TEST(TestRBTreeLib, check_erase_root) {
    RBTree<int, std::string> tree;
    tree.insert(30, "30");
    tree.erase(30);
    EXPECT_TRUE(tree.is_empty());
}
TEST(TestRBTreeLib, check_erase_black_leaf) {
    RBTree<int, std::string> tree;
    tree.insert(30, "30");
    tree.insert(20, "20");
    tree.insert(40, "40");
    tree.insert(50, "50");
    tree.erase(20);
    tree.print();
    auto root = tree.root();
    EXPECT_EQ(root->color, black);
    EXPECT_EQ(root->left->color, black);
    EXPECT_EQ(root->right->color, black);
    EXPECT_EQ(root->data.first, 40);
    EXPECT_EQ(root->left->data.first, 30);
    EXPECT_EQ(root->right->data.first, 50);
}
TEST(TestRBTreeLib, check_erase_red_leaf) {
    RBTree<int, std::string> tree;
    tree.insert(30, "30");
    tree.insert(20, "20");
    tree.insert(40, "40");
    tree.insert(50, "50");
    tree.erase(50);
    auto root = tree.root();
    EXPECT_EQ(root->color, black);
    EXPECT_EQ(root->left->color, black);
    EXPECT_EQ(root->right->color, black);
    EXPECT_EQ(root->data.first, 30);
    EXPECT_EQ(root->left->data.first, 20);
    EXPECT_EQ(root->right->data.first, 40);
}
TEST(TestRBTreeLib, check_erase_red_node_with_two_black_children) {
    RBTree<int, std::string> tree;
    tree.insert(50, "50");
    tree.insert(30, "30");
    tree.insert(75, "75");
    tree.insert(15, "15");
    tree.insert(35, "35");
    tree.insert(10, "10");
    tree.erase(30);
    tree.print();
    auto root = tree.root();
    EXPECT_EQ(root->color, black);
    EXPECT_EQ(root->left->color, black);
    EXPECT_EQ(root->right->color, black);
    EXPECT_EQ(root->left->left->color, red);
    EXPECT_EQ(root->left->right->color, red);
    EXPECT_EQ(root->data.first, 50);
    EXPECT_EQ(root->left->data.first, 15);
    EXPECT_EQ(root->right->data.first, 75);
    EXPECT_EQ(root->left->left->data.first, 10);
    EXPECT_EQ(root->left->right->data.first, 35);
}