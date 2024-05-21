#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
using namespace std;

template <typename T>
struct TNode {
	T data;
	TNode<T>* pNext;

	TNode() : data(), pNext(nullptr) {};
	TNode(const T& data) : data(data), pNext(nullptr) {};
	TNode(TNode<T>* pNext_) : data(), pNext(pNext_) {}; 
	TNode(const T& data_, TNode<T>* pNext_) : data(data_), pNext(pNext_) {};

    bool operator<(const TNode& other) const;
    bool operator>(const TNode& other) const;
};

template<typename T>
bool TNode<T>::operator>(const TNode& other) const {
    return data > other.data;
}

template<typename T>
bool TNode<T>::operator<(const TNode& other) const {
    return data < other.data;
}

#endif // !_NODE_H_