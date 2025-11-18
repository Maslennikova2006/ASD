// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_list/list.h"
#include "../lib_listStack/listStack.h"

TEST(TestListStackLib, can_create) {
    ASSERT_NO_THROW(ListStack<int> stack);
}
TEST(TestListStackLib, check_constructor) {
    ListStack<int> stack;
    EXPECT_EQ(-1, stack.get_size());
}
TEST(TestListStackLib, check_constructor_2) {
    ListStack<int> stack(20);
    EXPECT_EQ(20, stack.get_size());
}
TEST(TestListStackLib, throw_when_try_constructor_with_size) {
    ASSERT_ANY_THROW(ListStack<int>(-5));
}
TEST(TestListStackLib, check_copy_constructor) {
    ListStack<int> stack(5);
    ListStack<int> copy(stack);
    EXPECT_EQ(stack.get_size(), copy.get_size());
}
TEST(TestListStackLib, check_push) {
    ListStack<int> stack(5);
    stack.push(5);
    EXPECT_EQ(5, stack.top());
}
TEST(TestListStackLib, throw_when_try_push) {
    ListStack<int> stack(3);
    stack.push(5);
    stack.push(3);
    stack.push(77);
    ASSERT_ANY_THROW(stack.push(99));
}
TEST(TestListStackLib, check_pop) {
    ListStack<int> stack(5);
    stack.push(5);
    stack.push(8);
    stack.push(3);
    stack.pop();
    EXPECT_EQ(8, stack.top());
}
TEST(TestListStackLib, throw_when_try_pop) {
    ListStack<int> stack(3);
    ASSERT_ANY_THROW(stack.pop());
}
TEST(TestListStackLib, check_top) {
    ListStack<int> stack(5);
    stack.push(5);
    stack.push(8);
    stack.push(3);
    EXPECT_EQ(3, stack.top());
}
TEST(TestListStackLib, throw_when_try_top) {
    ListStack<int> stack(3);
    ASSERT_ANY_THROW(stack.top());
}
TEST(TestListStackLib, check_is_empty) {
    ListStack<int> stack(5);
    EXPECT_TRUE(stack.is_empty());
}
TEST(TestListStackLib, check_is_empty_2) {
    ListStack<int> stack(5);
    stack.push(5);
    stack.push(8);
    stack.push(3);
    EXPECT_FALSE(stack.is_empty());
}
TEST(TestListStackLib, check_is_full) {
    ListStack<int> stack(5);
    EXPECT_FALSE(stack.is_full());
}
TEST(TestListStackLib, check_is_full_2) {
    ListStack<int> stack(5);
    stack.push(5);
    stack.push(8);
    stack.push(3);
    stack.push(7);
    stack.push(15);
    EXPECT_TRUE(stack.is_full());
}
TEST(TestListStackLib, check_is_full_3) {
    ListStack<int> stack;
    stack.push(5);
    stack.push(8);
    stack.push(3);
    EXPECT_FALSE(stack.is_full());
}
TEST(TestListStackLib, check_clear) {
    ListStack<int> stack(5);
    stack.push(5);
    stack.push(8);
    stack.push(3);
    stack.clear();
    stack.push(8);
    stack.push(3);
    EXPECT_EQ(3, stack.top());
}