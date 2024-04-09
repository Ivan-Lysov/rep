#include "node.h"
#include <gtest.h>

TEST(TNode, can_create_node) {
	ASSERT_NO_THROW(TNode<int>*node = new TNode<int>);
}

TEST(TNode, can_create_node_with_data) {
	ASSERT_NO_THROW(TNode<int>*node = new TNode<int>(1));
}

TEST(TNode, data_work_correct) {
	TNode<int>* node = new TNode<int>(1);
	EXPECT_EQ(1, node->data);
}

TEST(TNode,node_work_correct) {
	TNode<int>* node = new TNode<int>;
	EXPECT_EQ(nullptr, node->pNext);
}

TEST(TNode, can_create_copied_node) {
	TNode<int>* tmp = new TNode<int>;
	ASSERT_NO_THROW(TNode<int>*node = new TNode<int>(tmp));
}

TEST(TNode, copied_node_is_equal) {
	TNode<int>* tmp = new TNode<int>;
	TNode<int>* node = new TNode<int>(tmp);
	EXPECT_EQ(tmp, node->pNext);
}

TEST(TNode, copied_node_have_equal_data) {
	TNode<int>* tmp = new TNode<int>(1);
	TNode<int>* node = new TNode<int>(tmp);
	EXPECT_EQ(1, node->pNext->data);
}

TEST(TNode, next_node_is_null) {
	TNode<int>* tmp = new TNode<int>;
	TNode<int>* node = new TNode<int>(tmp);
	EXPECT_EQ(nullptr, node->pNext->pNext);
}
