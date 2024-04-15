#ifndef _THEADRINGLIST_H
#define _THEADRINGLIST_H
#include "list.h"

template <typename T>
class THeadRingList : public TList<T> {
private:
    TNode<T>* pHead;
public:
    THeadRingList();
    THeadRingList(const THeadRingList& ringL);
    virtual ~THeadRingList();
    void insert_first(const T& data);
    void insert_before(const T& who, const T& where);
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
    delete pHead;
}

template <typename T>
void THeadRingList<T>::insert_first(const T& data) {
    TList<T>::insert_first(data);
    pHead->pNext = pFirst;
    pStop = pHead;
    pLast->pNext = pHead;
}

template <typename T>
void THeadRingList<T>::insert_before(const T& who, const T& where) {
    TNode<T>* pWhere = search(where);
    if (pWhere == pFirst) {
        insert_first(who);
        return;
    }
    TNode<T>* pPrev = pFirst;
    while (pPrev->pNext != pWhere) {
        pPrev = pPrev->pNext;
    }
    TNode<T>* new_node = new TNode<T>(who, pWhere);
    pPrev->pNext = new_node;
}

#endif 