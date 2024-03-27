#ifndef _THEADRINGLIST_H
#define _THEADRINGLIST_H
#include <iostream>
#include "list.h"
using namespace std;

template <typename T>
class THeadRingList : public TList<T> 
{
private:
	TNode<T>* pHead;
public:
	THeadRingList();
	THeadRingList(const THeadRingList& ringL);
	~THeadRingList();
};

template <typename T>
THeadRingList<T>::THeadRingList<T>() : TList<T>() {
	pHead = nullptr;
}

template <typename T>
THeadRingList<T>::THeadRingList<T>(const THeadRingList<T>& ringL) : TList<T>() {
	pHead = new TNode<T>(ringL.pHead->data);
	if (ringL.IsEmpty()) {
		pHead->pNext = pHead;
	}
	else {
		pHead->pNext = pFirst;
	}
	pLast->pNext = pHead;
	pStop = pHead;
}

template <typename T>
THeadRingList<T>::~THeadRingList<T>(){
	delete pHead;
}

#endif 