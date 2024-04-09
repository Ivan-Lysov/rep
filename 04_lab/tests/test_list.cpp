#include "list.h"
#include <gtest.h>

TEST(TList, can_create_new_list)
{
	ASSERT_NO_THROW(TList <int> list);
}

TEST(TList, can_create_list_with_node)
{
	ASSERT_NO_THROW(TList<int>{new TNode<int>});
}

TEST(TList, list_is_empty_check)
{
	TList<int> list;
	ASSERT_TRUE(list.IsEmpty());
}

TEST(TList, can_get_size)
{
	TList<int> list;
	list.insert_last(2);
	EXPECT_EQ(1, list.GetSize());
}

TEST(TList, can_insert_last_in_the_list)
{
	TList<int> list;
	ASSERT_NO_THROW(list.insert_last(1));
}

TEST(TList, can_insert_element_in_not_empty_list) 
{
	TList<int> list;
	list.insert_last(1);
	ASSERT_NO_THROW(list.insert_last(2));
}

TEST(TList, can_remove_element)
{
	TList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.insert_last(3);
	list.remove(3);
	EXPECT_EQ(2, list.GetSize());
}

TEST(TList, can_get_next_elemet)
{
	TList<int> list;
	list.insert_last(1);
	list.next();
	list.insert_last(2);
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(TList, can_clear_list)
{
	TList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.clear();
	EXPECT_EQ(0, list.GetSize());
}

TEST(TList, throw_when_remove_from_empty_list) 
{
	TList<int> list;
	ASSERT_ANY_THROW(list.remove(5));
}

TEST(TList, throw_when_remove_non_exist_elem) 
{
	TList<int> list;
	list.insert_last(4);
	ASSERT_ANY_THROW(list.remove(5));
}

TEST(TList, can_insert_first_element)
{
	TList<int> list;
	list.insert_first(1); 
	ASSERT_NO_THROW(list.insert_first(2));
}

TEST(TList, can_insert_after_element)
{
	TList<int> list;
	list.insert_first(1);
	list.insert_first(2);
	list.reset();
	list.next();
	ASSERT_NO_THROW(list.insert_after(3,2));
}

TEST(TList, next_element)
{
	TList<int> list;
	list.insert_first(1);
	list.insert_first(2);
	list.next();
	TNode<int>* tmp = list.GetCurrent();
	EXPECT_EQ(1, tmp->data);
}

TEST(TList, reset_test) 
{
	TList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.next();
	list.reset();
	TNode<int>* tmp = list.GetCurrent();
	EXPECT_EQ(1, tmp->data);
}