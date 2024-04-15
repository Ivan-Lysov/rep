#include "node.h"
#include <gtest.h>

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
	TNode<int>* node = new TNode<int>(0);
	EXPECT_EQ(0, node->data);
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

