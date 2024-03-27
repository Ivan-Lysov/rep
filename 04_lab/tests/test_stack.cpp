#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack) {
	ASSERT_NO_THROW(TStack<int> st(3));
}

TEST(TStack, throws_when_create_stack_with_negative_size) {
	ASSERT_ANY_THROW(TStack<int> st(-3));
}

TEST(TStack, throws_when_create_stack_with_zero_size) {
	ASSERT_ANY_THROW(TStack<int> st(0));
}

TEST(TStack, can_not_delete_if_stack_is_empty)
{
	TStack<int> st;
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, can_create_the_copy_stack)
{
	TStack<int> st1(1);
	st1.Push(1);
	ASSERT_NO_THROW(TStack<int> st2(st1));
}

TEST(TStack, stack_is_full_check) {
	TStack<int> st(1);
	st.Push(1);
	EXPECT_EQ(true, st.IsFull());
}

TEST(TStack, stack_is_not_full_check) {
	TStack<int> st(2);
	st.Push(1);
	EXPECT_EQ(false, st.IsFull());
}

TEST(TStack, stack_is_empty_check) {
	TStack<int> st(1);
	EXPECT_EQ(true, st.IsEmpty());
}
TEST(TStack, stack_is_not_empty_check) {
	TStack<int> st(1);
	st.Push(4);
	EXPECT_EQ(false, st.IsEmpty());
}

TEST(TStack, can_pop_elements)
{
	TStack<int> st(2);
	st.Push(100);
	st.Push(42);
	st.Pop();
	EXPECT_EQ(100, st.Top());
}

TEST(TStack, throws_when_top_element_is_empty) {
	TStack<int> st(1);
	ASSERT_ANY_THROW(st.Top());
}

TEST(TStack, throws_when_pop_element_is_empty) {
	TStack<int> st(1);
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, can_top_and_push_elements)  {
	TStack<int> st(1);
	st.Push(-22);
	EXPECT_EQ(-22, st.Top());
}

TEST(TStack, can_memory_reallocation)
{
	TStack<int> st(1);
	st.Push(2);
	ASSERT_NO_THROW(st.Push(1));
}

TEST(TStack, correct_order_of_return_values)
{
	TStack <int> S(3);
	S.Push(1);
	S.Push(2);
	S.Push(3);
	ASSERT_EQ(3, S.Pop());
	ASSERT_EQ(2, S.Pop());
	ASSERT_EQ(1, S.Pop());
}