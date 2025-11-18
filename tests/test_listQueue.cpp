// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_listQueue/listQueue.h"


TEST(TestListQueueLib, can_create_default_queue) {
    ListQueue<int> queue;
    EXPECT_EQ(-1, queue.get_size());
}
TEST(TestListQueueLib, can_create_queue) {
    ListQueue<int> queue(20);
    EXPECT_EQ(20, queue.get_size());
}
TEST(TestListQueueLib, throw_when_try_constructor_with_size) {
    ASSERT_ANY_THROW(ListQueue<int>(-5));
}
TEST(TestListQueueLib, throw_when_try_copy_constructor) {
    ListQueue<int>* obj = nullptr;
    ASSERT_ANY_THROW(ListQueue<int> copy_obj(*obj));
}
TEST(TestListQueueLib, check_the_copy_constructor) {
    ListQueue<int> q1(5);
    q1.push(3);
    ListQueue<int> q2(q1);
    EXPECT_EQ(q1.get_size(), q2.get_size());
    EXPECT_EQ(q1.head(), q2.head());
    EXPECT_EQ(q1.tail(), q2.tail());
}
TEST(TestListQueueLib, check_push) {
    ListQueue<int> queue(5);
    queue.push(10);
    queue.push(15);
    EXPECT_EQ(10, queue.head());
    EXPECT_EQ(15, queue.tail());
}
TEST(TestListQueueLib, check_push_2) {
    ListQueue<int> queue(5);
    queue.push(10);
    queue.push(15);
    queue.push(18);
    queue.push(20);
    queue.push(4);
    queue.pop();
    queue.pop();
    queue.push(78);
    EXPECT_EQ(18, queue.head());
    EXPECT_EQ(78, queue.tail());
}
TEST(TestListQueueLib, throw_when_try_push) {
    ListQueue<int> queue(3);
    queue.push(5);
    queue.push(3);
    queue.push(77);
    ASSERT_ANY_THROW(queue.push(99));
}
TEST(TestListQueueLib, check_pop) {
    ListQueue<int> queue(5);
    queue.push(5);
    queue.push(8);
    queue.push(3);
    queue.pop();
    EXPECT_EQ(8, queue.head());
    EXPECT_EQ(3, queue.tail());
}
TEST(TestListQueueLib, throw_when_try_pop) {
    ListQueue<int> queue(3);
    ASSERT_ANY_THROW(queue.pop());
}
TEST(TestListQueueLib, check_head) {
    ListQueue<int> queue(5);
    queue.push(5);
    queue.push(8);
    queue.push(3);
    queue.pop();
    EXPECT_EQ(8, queue.head());
}
TEST(TestListQueueLib, throw_when_try_head) {
    ListQueue<int> queue(3);
    ASSERT_ANY_THROW(queue.head());
}
TEST(TestListQueueLib, check_tail) {
    ListQueue<int> queue(5);
    queue.push(5);
    queue.push(8);
    queue.push(3);
    queue.pop();
    EXPECT_EQ(3, queue.tail());
}
TEST(TestListQueueLib, throw_when_try_tail) {
    ListQueue<int> queue(3);
    ASSERT_ANY_THROW(queue.tail());
}
TEST(TestListQueueLib, check_is_empty) {
    ListQueue<int> queue(5);
    EXPECT_TRUE(queue.is_empty());
}
TEST(TestListQueueLib, check_is_empty_2) {
    ListQueue<int> queue(5);
    queue.push(5);
    queue.push(8);
    queue.push(3);
    EXPECT_FALSE(queue.is_empty());
}
TEST(TestListQueueLib, check_is_full) {
    ListQueue<int> queue(5);
    EXPECT_FALSE(queue.is_full());
}
TEST(TestListQueueLib, check_is_full_2) {
    ListQueue<int> queue(5);
    queue.push(5);
    queue.push(8);
    queue.push(3);
    queue.push(7);
    queue.push(15);
    EXPECT_TRUE(queue.is_full());
}
TEST(TestListQueueLib, check_is_full_3) {
    ListQueue<int> queue;
    queue.push(5);
    queue.push(8);
    queue.push(3);
    EXPECT_FALSE(queue.is_full());
}
TEST(TestListQueueLib, check_clear) {
    ListQueue<int> queue(5);
    queue.push(5);
    queue.push(8);
    queue.push(3);
    queue.push(7);
    queue.clear();
    queue.push(3);
    queue.push(7);
    EXPECT_EQ(3, queue.head());
    EXPECT_EQ(7, queue.tail());
}