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
    void Clear();

   const THeadRingList<T>& operator=(const THeadRingList<T>& l);
};


template <typename T>
THeadRingList<T>::THeadRingList() : TList<T>() {
    pHead = new TNode<T>();
    pStop = pHead;
}

template <typename T>
THeadRingList<T>::THeadRingList(const THeadRingList<T>& ringL) : TList<T>(ringL) {
    pHead = new TNode<T>(ringL.pHead->data, pFirst);
    if (!ringL.IsEmpty())
        pLast->pNext = pHead;
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
void THeadRingList<T>::remove(const T& data) {
    if (!this->pFirst) {
        return;
    }
    TList<T>::remove(data);
    if (!this->pFirst) {
        delete pHead;
        pHead = nullptr;
    }
    else if (this->pFirst == pHead) {
        // ���� ��������� ������� ��� ������� ������, ��������� pHead �� ����� ������
        pHead = this->pFirst;
    }
    // ��������� pCurrent
    pCurrent = this->pFirst;
}

template <typename T>
const THeadRingList<T>& THeadRingList<T>::operator=(const THeadRingList<T>& l) {

   
    this->TList<T>::operator=(l);
    this->pHead->pNext = this->pFirst;
    return *(this);
}



template <class T> void THeadRingList<T>::Clear() {
    TList<T>::Clear();
    pHead->pNext = pHead;
}

//template <typename T>
//void THeadRingList<T>::Clear() {
//    TList<T>::Clear(); // �������� ������� ����������
//
//    if (pHead != nullptr) {
//        delete pHead; // ������� �������� ����
//        pHead = nullptr; // ������������� ��������� �� �������� ���� � nullptr
//    }
//
//    // ��������� ��������� �� ���������
//    this->pStop = nullptr; // ��� �����, ���� pStop ��� ���������� �� ���� ������, ������� ��� ������ ������� ������� Clear()
//}

//template <typename T>
//const THeadRingList<T>& THeadRingList<T>::operator=(const THeadRingList& other) {
//    if (this == &other) {
//        return *this;
//    }
//
//    // �������� �������� ������������ �������� ������ ��� ����������� ������
//    TList<T>::operator=(other);
//
//    // ������� ������ ��������� ������
//    if (pHead) {
//        delete pHead;
//        pHead = nullptr;
//    }
//
//    // ���� ������ other �� ������, �������� ��� ��������
//    if (other.pFirst) {
//        pHead = new TNode<T>(other.pHead->data);
//        TNode<T>* curr = other.pHead->pNext;
//        TNode<T>* thisCurr = pHead;
//
//        // �������� ��������� �������� ���������� ������
//        while (curr != other.pHead) {
//            thisCurr->pNext = new TNode<T>(curr->data);
//            thisCurr = thisCurr->pNext;
//            curr = curr->pNext;
//        }
//
//        // �������� ��������� ������
//        thisCurr->pNext = pHead;
//    }
//
//    return *this;
//}\

//template <typename T>
//THeadRingList<T>::THeadRingList(const THeadRingList& ringL) : TList<T>(ringL), pHead(nullptr) {
//    if (!ringL.IsEmpty()) {
//        pHead = new TNode<T>(ringL.pHead->data);
//        TNode<T>* curr = ringL.pHead->pNext;
//        TNode<T>* thisCurr = pHead;
//        thisCurr->pNext = pHead;
//    }
//}


#endif 