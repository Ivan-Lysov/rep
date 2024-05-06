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
    void remove(const T& data);

    THeadRingList& operator=(const THeadRingList& other);
};

template <typename T>
THeadRingList<T>::THeadRingList() : TList<T>() {
    pHead = new TNode<T>();
    this->pStop = pHead;
}

template <typename T>
THeadRingList<T>::THeadRingList(const THeadRingList<T>& ringL) : TList<T>(ringL) {
    pHead = new TNode<T>(ringL.pHead->data, this->pFirst);
    if (!ringL.IsEmpty()) {
        this->pLast->pNext = pHead;
    }
    this->pStop = pHead;
}

template <typename T>
THeadRingList<T>::~THeadRingList() {
    delete pHead;
}

template <typename T>
void THeadRingList<T>::insert_first(const T& data) {
    TList<T>::insert_first(data);
    pHead->pNext = this->pFirst;
    this->pStop = pHead;
    this->pLast->pNext = pHead;
}

template<typename T>
void THeadRingList<T>::remove(const T& data) {
    if (this->pFirst == nullptr) {
        throw std::exception("List is empty");
    }
    TNode<T>* Current = this->pFirst;
    if (Current->data == data) {
        if (Current->pNext == pHead) {
            this->pFirst = nullptr;
            this->pCurrent = nullptr;
            this->pLast = nullptr;
            pHead->pNext = nullptr;
            delete Current;
            return;
        }
        this->pFirst = this->pFirst->pNext;
        pHead->pNext = this->pFirst;
        delete Current;
        return;
    }
    TList<T>::remove(data);
}

template<typename T>
THeadRingList<T>& THeadRingList<T>::operator=(const THeadRingList& other) {
    TList<T>::operator=(other);
    pHead = new TNode<T>(other.pHead->data, this->pFirst);
    return *this;
}

#endif 