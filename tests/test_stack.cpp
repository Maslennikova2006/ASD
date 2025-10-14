// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_stack/stack.h"

TEST(TestStackLib, can_create_default_stack) {
    Stack<int> stack;
    EXPECT_EQ(15, stack.get_size());
    EXPECT_EQ(-1, stack.get_top());
}
TEST(TestStackLib, can_create_stack) {
    Stack<int> stack(20);
    EXPECT_EQ(20, stack.get_size());
    EXPECT_EQ(-1, stack.get_top());
}
TEST(TestStackLib, throw_when_try_constructor_with_size) {
    ASSERT_ANY_THROW(Stack<int>(-5));
}
TEST(TestStackLib, throw_when_try_copy_constructor) {
    Stack<int>* obj = nullptr;
    ASSERT_ANY_THROW(Stack<int> copy_obj(*obj));
}
TEST(TestStackLib, check_the_copy_constructor) {
    Stack<int> st1(5);
    st1.push(3);
    Stack<int> st2(st1);
    EXPECT_EQ(5, st2.get_size());
    EXPECT_EQ(0, st2.get_top());
    EXPECT_EQ(3, st2.top());
}
TEST(TestStackLib, check_push) {
    Stack<int> stack(5);
    stack.push(5);
    EXPECT_EQ(5, stack.top());
}
TEST(TestStackLib, throw_when_try_push) {
    Stack<int> stack(3);
    stack.push(5);
    stack.push(3);
    stack.push(77);
    ASSERT_ANY_THROW(stack.push(99));
}
TEST(TestStackLib, check_pop) {
    Stack<int> stack(5);
    stack.push(5);
    stack.push(8);
    stack.push(3);
    stack.pop();
    EXPECT_EQ(8, stack.top());
}
TEST(TestStackLib, throw_when_try_pop) {
    Stack<int> stack(3);
    ASSERT_ANY_THROW(stack.pop());
}
TEST(TestStackLib, check_top) {
    Stack<int> stack(5);
    stack.push(5);
    stack.push(8);
    stack.push(3);
    EXPECT_EQ(3, stack.top());
}
TEST(TestStackLib, throw_when_try_top) {
    Stack<int> stack(3);
    ASSERT_ANY_THROW(stack.top());
}
TEST(TestStackLib, check_is_empty) {
    Stack<int> stack(5);
    EXPECT_TRUE(stack.is_empty());
}
TEST(TestStackLib, check_is_empty_2) {
    Stack<int> stack(5);
    stack.push(5);
    stack.push(8);
    stack.push(3);
    EXPECT_FALSE(stack.is_empty());
}
TEST(TestStackLib, check_is_full) {
    Stack<int> stack(5);
    EXPECT_FALSE(stack.is_full());
}
TEST(TestStackLib, check_is_full_2) {
    Stack<int> stack(5);
    stack.push(5);
    stack.push(8);
    stack.push(3);
    stack.push(7);
    stack.push(15);
    EXPECT_TRUE(stack.is_full());
}
TEST(TestStackLib, check_clear) {
    Stack<int> stack(5);
    stack.push(5);
    stack.push(8);
    stack.push(3);
    stack.clear();
    stack.push(8);
    stack.push(3);
    EXPECT_EQ(3, stack.top());
}
