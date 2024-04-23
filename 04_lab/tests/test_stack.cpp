//
//#include "stack.h"
//#include <gtest.h>
//
//TEST(TStack, can_create_stack)
//{
//	ASSERT_NO_THROW(TStack<int> stack(5));
//}
//
//TEST(TStack, throws_when_create_stack_with_negative_size)
//{
//	ASSERT_ANY_THROW(TStack<int> stack(-5));
//}
//
//TEST(TStack, throws_when_create_stack_with_zero_size)
//{
//	ASSERT_ANY_THROW(TStack<int> stack(0));
//}
//
//TEST(TStack, can_not_delete_if_stack_is_empty)
//{
//	TStack<int> stack;
//	ASSERT_ANY_THROW(stack.Pop());
//}
//
//TEST(TStack, can_create_the_copy_stack)
//{
//	TStack<int> stack1(1);
//	stack1.Push(1);
//	ASSERT_NO_THROW(TStack<int> stack2(stack1));
//}
//
//TEST(TStack, stack_is_full_check)
//{
//	TStack<int> stack(1);
//	stack.Push(1);
//	EXPECT_EQ(true, stack.IsFull());
//}
//
//TEST(TStack, stack_is_empty_check)
//{
//	TStack<int> stack(1);
//	EXPECT_EQ(true, stack.IsEmpty());
//}
//
//TEST(TStack, can_pop_elements)
//{
//	TStack<int> stack(2);
//	stack.Push(300);
//	stack.Push(500);
//	stack.Pop();
//	EXPECT_EQ(300, stack.Top());
//}
//
//TEST(TStack, throws_when_top_element_is_empty)
//{
//	TStack<int> stack(5);
//	ASSERT_ANY_THROW(stack.Top());
//}
//
//TEST(TStack, throws_when_pop_element_is_empty)
//{
//	TStack<int> stack(5);
//	ASSERT_ANY_THROW(stack.Pop());
//}
//
//TEST(TStack, can_top_and_push_elements)
//{
//	TStack<int> stack(1);
//	stack.Push(-100);
//	EXPECT_EQ(-100, stack.Top());
//}
//
//TEST(TStack, can_memory_reallocation)
//{
//	TStack<int> stack(1);
//	stack.Push(2);
//	ASSERT_NO_THROW(stack.Push(1));
//}
//
//TEST(TStack, correct_order_of_return_values)
//{
//	TStack <int> stack(5);
//	stack.Push(1);
//	stack.Push(2);
//	stack.Push(3);
//	stack.Push(4);
//	stack.Push(5);
//	ASSERT_EQ(5, stack.Pop());
//	ASSERT_EQ(4, stack.Pop());
//	ASSERT_EQ(3, stack.Pop());
//	ASSERT_EQ(2, stack.Pop());
//	ASSERT_EQ(1, stack.Pop());
//}
