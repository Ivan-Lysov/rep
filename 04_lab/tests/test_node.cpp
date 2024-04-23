#include "node.h"
#include <gtest.h>
#include <limits.h>	
TEST(TNode, can_create_node) 
{
	ASSERT_NO_THROW(TNode<int>*node = new TNode<int>);
}

TEST(TNode, can_create_node_with_data) 
{
	ASSERT_NO_THROW(TNode<int>*node = new TNode<int>(0));
}

TEST(TNode, data_working_is_correct) 
{
	TNode<int>* node = new TNode<int>(10);
	EXPECT_EQ(10, node->data);
}

TEST(TNode,node_work_correct) 
{
	TNode<int>* node = new TNode<int>;
	EXPECT_EQ(nullptr, node->pNext);
}

TEST(TNode, can_create_copied_node) 
{
	TNode<int>* copy_node = new TNode<int>;
	ASSERT_NO_THROW(TNode<int>*node = new TNode<int>(copy_node));
}

TEST(TNode, copied_node_is_equal) 
{
	TNode<int>* node = new TNode<int>;
	TNode<int>* copy_node = new TNode<int>(node);
	EXPECT_EQ(node, copy_node->pNext);
}

TEST(TNode, copied_node_have_equal_data) 
{
	TNode<int>* tmp = new TNode<int>(0);
	TNode<int>* node = new TNode<int>(tmp);
	EXPECT_EQ(0, node->pNext->data);
}

TEST(TNode, can_create_node_with_max_int_value)
{
	ASSERT_NO_THROW(TNode<int>*node = new TNode<int>(INT_MAX));
}

TEST(TNode, can_create_node_with_min_int_value)
{
	ASSERT_NO_THROW(TNode<int>*node = new TNode<int>(INT_MIN));
}

TEST(TNode, can_create_node_with_max_double_value)
{
	ASSERT_NO_THROW(TNode<double>*node = new TNode<double>(DBL_MAX));
}

TEST(TNode, can_create_node_with_min_double_value)
{
	ASSERT_NO_THROW(TNode<double>*node = new TNode<double>(DBL_MIN));
}

TEST(TNode, can_create_node_with_nullptr)
{
	ASSERT_NO_THROW(TNode<int>*node = new TNode<int>(nullptr));
}
