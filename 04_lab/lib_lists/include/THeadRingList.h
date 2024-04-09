#ifndef _THEADRINGLIST_H
#define _THEADRINGLIST_H
#include <iostream>
#include <algorithm> 
#include "list.h"
using namespace std;

template <typename T>
class THeadRingList : public TList<T> {
private:
    TNode<T>* pHead;
public:
    THeadRingList();
    THeadRingList(const THeadRingList& ringL);
    ~THeadRingList();
    void InsertFirst(const T& data);
    void insert_sort(const T& data);
    void Clear();
};

template <typename T>
THeadRingList<T>::THeadRingList() : TList<T>() {
    pHead = new TNode<T>();
    pStop = pHead;
}

template <typename T>
THeadRingList<T>::THeadRingList(const THeadRingList<T>& ringL) : TList<T>(ringL) {
    pHead = new TNode<T>(ringL.pHead->data, pFirst);
    if (!ringL.IsEmpty()) {
        pLast->pNext = pHead;
    }
    pStop = pHead;
}

template <typename T>
THeadRingList<T>::~THeadRingList() {
    Clear();
    delete pHead;
}

template <typename T>
void THeadRingList<T>::InsertFirst(const T& data) {
    TList<T>::insert_first(data);
    pHead->pNext = pFirst;
    pStop = pHead;
    pLast->pNext = pHead;
}

template <typename T>
void THeadRingList<T>::insert_sort(const T& data) {
    if (IsEmpty() || data < pFirst->data) {
        InsertFirst(data);
        return;
    }
    TNode<T>* tmp = pFirst;
    while (tmp->pNext != pStop && tmp->pNext->data <= data) {
        tmp = tmp->pNext;
    }
    if (tmp->data == data) {
        tmp->data = tmp->data + data;
        return;
    }
    insert_after(data, tmp->data);
}

template <typename T>
void THeadRingList<T>::Clear() {
    if (pHead == nullptr) return; 
    TNode<T>* curr = pHead->pNext;
    while (curr != pHead && curr != nullptr) { 
        TNode<T>* next = curr->pNext;
        delete curr;
        curr = next;
    }
    pHead = nullptr;
    pFirst = nullptr;
    pLast = nullptr;
}

#endif 