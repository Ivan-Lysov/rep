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

TEST(TList, throw_when_list_no_empty_but_empty_check)
{
	TList<int> list;
	list.insert_first(1);
	ASSERT_FALSE(list.IsEmpty());
}

TEST(TList, is_empty_returns_true_after_removing_all_elements)
{
	TList<int> list;
	list.insert_last(1);
	list.remove(1);
	EXPECT_TRUE(list.IsEmpty());
}

TEST(TList, can_get_size)
{
	TList<int> list;
	list.insert_last(1);
	EXPECT_EQ(1, list.GetSize());
}

TEST(TList, can_copy_list)
{
	TList<int> list1;
	list1.insert_last(1);
	list1.insert_last(2);
	TList<int> list2(list1);
	list1.reset();
	EXPECT_EQ(list1.GetCurrent()->data, list2.GetCurrent()->data);
}

TEST(TList, can_insert_element_in_empty_list)
{
	TList<int> list;
	ASSERT_NO_THROW(list.insert_last(10));
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
	list.remove(1);
	EXPECT_EQ(2, list.GetSize());
}

TEST(TList, size_of_list_after_insertion_is_correct)
{
	TList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.insert_last(3);
	EXPECT_EQ(3, list.GetSize());
}

TEST(TList, size_of_list_after_removal_is_correct)
{
	TList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.insert_last(3);
	list.remove(2); // Удаляем один элемент
	EXPECT_EQ(2, list.GetSize());

	list.remove(1); // Удаляем оставшийся элемент
	EXPECT_EQ(1, list.GetSize());
}

TEST(TList, can_remove_element_if_count_element_1 )
{
	TList<int> list;
	list.insert_last(1);
	list.remove(1);
	EXPECT_TRUE(list.IsEmpty());
}

TEST(TList, throw_when_remove_from_empty_list)
{
	TList<int> list;
	ASSERT_ANY_THROW(list.remove(1));
}

TEST(TList, throw_when_remove_non_exist_elem)
{
	TList<int> list;
	list.insert_first(4);
	ASSERT_ANY_THROW(list.remove(5));
}

TEST(TList, can_get_next_elemet)
{
	TList<int> list;
	list.insert_first(1);
	list.next();
	list.insert_last(2);
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(TList, size_of_empty_list_is_zero)
{
	TList<int> list;
	EXPECT_EQ(0, list.GetSize());
}

TEST(TList, can_clear_all_node_in_list)
{
	TList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.insert_last(3);
	list.insert_last(4);
	list.Clear();
	EXPECT_EQ(0, list.GetSize());
}

TEST(TList, can_insert_first_element)
{
	TList<int> list;
	list.insert_first(1); 
	ASSERT_NO_THROW(list.insert_first(2));
}

TEST(TList, can_find_node_by_data)
{
	TList<int> list;
	list.insert_first(1);
	list.insert_last(2);
	list.insert_last(3);
	EXPECT_EQ(2, list.search(2)->data);
}

TEST(TList, can_insert_before_element)
{
	TList<int> list;
	list.insert_first(1);
	list.insert_last(3);
	list.insert_before(2,3);
	list.reset();
	list.next();
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(TList, throw_when_element_not_found_in_insert_before) {
	TList<int> list;
	list.insert_first(1);
	list.insert_last(2);
	ASSERT_ANY_THROW(list.insert_before(3, 4));
}

TEST(TList, throw_insert_before_when_list_is_empty) {
	TList<int> list;
	ASSERT_ANY_THROW(list.insert_before(1, 1));
}

TEST(TList, can_insert_after_element)
{
	TList<int> list;
	list.insert_first(1);
	list.insert_first(2);
	list.insert_after(3, 2);
	list.reset();
	list.next();
	EXPECT_EQ(3, list.GetCurrent()->data);
}

TEST(TList, throw_when_element_not_found_in_insert_after)
{
	TList<int> list;
	list.insert_first(1);
	list.insert_last(2);
	ASSERT_ANY_THROW(list.insert_after(3, 4));
}

TEST(TList, throw_insert_after_when_list_is_empty) {
	TList<int> list;
	ASSERT_ANY_THROW(list.insert_after(1, 1));
}

TEST(TList, reset_test) 
{
	TList<int> list;
	list.insert_first(1);
	list.insert_last(2);
	list.insert_last(3);
	list.reset();
	EXPECT_EQ(1, list.GetCurrent()->data);
}

TEST(TList, insert_to_sorted_list_is_right)
{
	TList<int> list;
	list.insert_sort(5);
	list.insert_sort(3);
	list.insert_sort(1);
	EXPECT_EQ(1, list.GetCurrent()->data);
	list.next();
	EXPECT_EQ(3, list.GetCurrent()->data);
	list.next();
	EXPECT_EQ(5, list.GetCurrent()->data);
}

TEST(TList, sort_empty_list_does_not_throw)
{
	TList<int> list;
	ASSERT_NO_THROW(list.Sort());
}

TEST(TList, sort_list_with_one_element_does_not_throw)
{
	TList<int> list;
	list.insert_last(1);
	ASSERT_NO_THROW(list.Sort());
}

TEST(TList, insert_sort_correct_into_empty_list)
{
	TList<int> list;
	list.insert_sort(5);
	EXPECT_EQ(5, list.GetCurrent()->data);
}

