#ifndef _THEADRINGLIST_H
#define _THEADRINGLIST_H
#include "list.h"

#define THeadRingList THeadRingList_

template <typename T>
class THeadRingList : public TList<T> {
private:
    TNode<T>* pHead;
public:
    THeadRingList();
    THeadRingList(const THeadRingList& ringL);
    virtual ~THeadRingList();
    void insert_first(const T& data);
    TNode<T>* GetHead() const;
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
    this->Clear();
}

template <typename T>
void THeadRingList<T>::insert_first(const T& data) {
    TList<T>::insert_first(data);
    pHead->pNext = pFirst;
    pStop = pHead;
    pLast->pNext = pHead;
}

template <class T>
TNode<T>* THeadRingList<T>::GetHead() const {
    return pHead;
}

#undef THeadRingList
template<typename T>
using THeadRingList = TList<T>;

#endif 