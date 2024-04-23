#ifndef _NODE_H
#define _NODE_H

#include <iostream>
using namespace std;

template <typename T>
struct TNode {
	T data;
	TNode<T>* pNext;

	TNode() : data(), pNext(nullptr) {};
	TNode(const T& data) : data(data), pNext(nullptr) {};
	TNode(TNode<T>* pNext_) : data(), pNext(pNext_) {}; 
	TNode(const T& data, TNode<T>* pNext_) : data(data), pNext(pNext_) {}; 
};

#endif // !_NODE_H