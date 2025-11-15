// Copyright 2025 Mary Maslennikova

#include <gtest/gtest.h>
#include "../lib_queue/queue.h"


TEST(TestQueueLib, can_create_default_queue) {
    Queue<int> queue;
    EXPECT_EQ(15, queue.get_size());
    EXPECT_EQ(0, queue.get_count());
    EXPECT_EQ(0, queue.get_head());
}
TEST(TestQueueLib, can_create_queue) {
    Queue<int> queue(20);
    EXPECT_EQ(20, queue.get_size());
    EXPECT_EQ(0, queue.get_count());
    EXPECT_EQ(0, queue.get_head());
}
TEST(TestQueueLib, throw_when_try_constructor_with_size) {
    ASSERT_ANY_THROW(Queue<int>(-5));
}
TEST(TestQueueLib, throw_when_try_copy_constructor) {
    Queue<int>* obj = nullptr;
    ASSERT_ANY_THROW(Queue<int> copy_obj(*obj));
}
TEST(TestQueueLib, check_the_copy_constructor) {
    Queue<int> q1(5);
    q1.push(3);
    Queue<int> q2(q1);
    EXPECT_EQ(q1.get_size(), q2.get_size());
    EXPECT_EQ(q1.get_count(), q2.get_count());
    EXPECT_EQ(q1.get_head(), q2.get_head());
}
TEST(TestQueueLib, check_push) {
    Queue<int> queue(5);
    queue.push(10);
    queue.push(15);
    EXPECT_EQ(10, queue.head());
    EXPECT_EQ(15, queue.tail());
    EXPECT_EQ(2, queue.get_count());
}
TEST(TestQueueLib, check_push_2) {
    Queue<int> queue(5);
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
    EXPECT_EQ(4, queue.get_count());
}
TEST(TestQueueLib, throw_when_try_push) {
    Queue<int> queue(3);
    queue.push(5);
    queue.push(3);
    queue.push(77);
    ASSERT_ANY_THROW(queue.push(99));
}
TEST(TestQueueLib, check_pop) {
    Queue<int> queue(5);
    queue.push(5);
    queue.push(8);
    queue.push(3);
    queue.pop();
    EXPECT_EQ(8, queue.head());
    EXPECT_EQ(3, queue.tail());
}
TEST(TestQueueLib, throw_when_try_pop) {
    Queue<int> queue(3);
    ASSERT_ANY_THROW(queue.pop());
}
TEST(TestQueueLib, check_head) {
    Queue<int> queue(5);
    queue.push(5);
    queue.push(8);
    queue.push(3);
    queue.pop();
    EXPECT_EQ(8, queue.head());
}
TEST(TestQueueLib, throw_when_try_head) {
    Queue<int> queue(3);
    ASSERT_ANY_THROW(queue.head());
}
TEST(TestQueueLib, check_tail) {
    Queue<int> queue(5);
    queue.push(5);
    queue.push(8);
    queue.push(3);
    queue.pop();
    EXPECT_EQ(3, queue.tail());
}
TEST(TestQueueLib, throw_when_try_tail) {
    Queue<int> queue(3);
    ASSERT_ANY_THROW(queue.tail());
}
TEST(TestQueueLib, check_is_empty) {
    Queue<int> queue(5);
    EXPECT_TRUE(queue.is_empty());
}
TEST(TestQueueLib, check_is_empty_2) {
    Queue<int> queue(5);
    queue.push(5);
    queue.push(8);
    queue.push(3);
    EXPECT_FALSE(queue.is_empty());
}
TEST(TestQueueLib, check_is_full) {
    Queue<int> queue(5);
    EXPECT_FALSE(queue.is_full());
}
TEST(TestQueueLib, check_is_full_2) {
    Queue<int> queue(5);
    queue.push(5);
    queue.push(8);
    queue.push(3);
    queue.push(7);
    queue.push(15);
    EXPECT_TRUE(queue.is_full());
}
TEST(TestQueueLib, check_clear) {
    Queue<int> queue(5);
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