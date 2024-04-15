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
	TNode(TNode<T>* _pNext) : data(), pNext(_pNext) {}; 
	TNode(const T& data, TNode<T>* _pNext) : data(data), pNext(_pNext) {}; 
};

#endif 