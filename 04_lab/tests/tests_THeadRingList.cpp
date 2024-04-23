#include "THeadRingList.h"
#include <gtest.h>

TEST(THeadRingList, can_create_THeadRingList) 
{
	ASSERT_NO_THROW(THeadRingList<int>list);
}

TEST(THeadRingList, list_is_empty_check)
{
	THeadRingList<int> list;
	ASSERT_TRUE(list.IsEmpty());
}

TEST(THeadRingList, can_get_size)
{
	THeadRingList<int> list;
	list.insert_last(2);
	EXPECT_EQ(1, list.GetSize());
}

TEST(THeadRingList, can_get_size_of_empty_list)
{
	THeadRingList<int> list;
	EXPECT_EQ(0, list.GetSize());
}

TEST(THeadRingList, can_copy_list)
{
	THeadRingList<int> list1;
	list1.insert_last(1);
	list1.insert_last(2);
	THeadRingList<int> list2(list1);
	list1.reset();
	EXPECT_EQ(list1.GetCurrent()->data, list2.GetCurrent()->data);
}

TEST(THeadRingList, can_insert_last_in_the_list)
{
	THeadRingList<int> list;
	ASSERT_NO_THROW(list.insert_last(1));
}

TEST(THeadRingList, can_insert_element_in_not_empty_list)
{
	THeadRingList<int> list;
	list.insert_last(1);
	ASSERT_NO_THROW(list.insert_last(2));
}

TEST(THeadRingList, can_remove_element)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.insert_last(3);
	list.remove(3);
	EXPECT_EQ(2, list.GetSize());
}

TEST(THeadRingList, can_remove_first_element)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.remove(1);
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(THeadRingList, throw_when_element_not_found_in_remove)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	ASSERT_ANY_THROW(list.remove(3));
}

TEST(THeadRingList, can_get_next_element)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.next();
	list.insert_last(2);
	EXPECT_EQ(2, list.GetCurrent()->data);
}

//TEST(THeadRingList, can_clear_list)
//{
//	THeadRingList<int> list;
//	list.insert_last(1);
//	list.insert_last(2);
//	list.Clear();
//	EXPECT_EQ(0, list.GetSize());
//}

TEST(THeadRingList, throw_when_remove_from_empty_list)
{
	THeadRingList<int> list;
	ASSERT_ANY_THROW(list.remove(5));
}

TEST(THeadRingList, throw_when_remove_non_exist_elem)
{
	THeadRingList<int> list;
	list.insert_last(4);
	ASSERT_ANY_THROW(list.remove(5));
}

TEST(THeadRingList, can_insert_first_element)
{
	THeadRingList<int> list;
	list.insert_first(1);
	ASSERT_NO_THROW(list.insert_first(2));
}

TEST(THeadRingList, can_find_element_by_value)
{
	TList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.insert_last(3);
	EXPECT_EQ(2, list.search(2)->data);
}

TEST(THeadRingList, can_insert_before_element)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(3);
	list.insert_before(2, 3);
	list.reset();
	list.next();
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(THeadRingList, throw_when_element_not_found_in_insert_before)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	ASSERT_ANY_THROW(list.insert_before(3,4));
}

TEST(THeadRingList, can_insert_after_element)
{
	THeadRingList<int> list;
	list.insert_first(1);
	list.insert_first(2);
	list.insert_after(3, 2);
	list.reset();
	list.next();
	EXPECT_EQ(3, list.GetCurrent()->data);
}

TEST(THeadRingList, throw_when_element_not_found_in_insert_after)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	ASSERT_ANY_THROW(list.insert_before(3, 4));
}

TEST(THeadRingList, reset_test)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.next();
	list.reset();
	EXPECT_EQ(1, list.GetCurrent()->data);
}

TEST(THeadRingList, insert_to_sorted_list_is_right)
{
	THeadRingList<int> list;
	list.insert_sort(6);
	list.insert_sort(4);
	list.insert_sort(2);
	EXPECT_EQ(2, list.GetCurrent()->data);
	list.next();
	EXPECT_EQ(4, list.GetCurrent()->data);
	list.next();
	EXPECT_EQ(6, list.GetCurrent()->data);
}

TEST(THeadRingList, insert_sort_correct_into_empty_list)
{
	THeadRingList<int> list;
	list.insert_sort(10);
	EXPECT_EQ(10, list.GetCurrent()->data);
}

TEST(THeadRingList, check_hr_list_cannot_do_Next_method_at_Head)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.next();
	ASSERT_ANY_THROW(list.next());
}
