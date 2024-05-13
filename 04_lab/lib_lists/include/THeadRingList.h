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
    const THeadRingList& operator=(const THeadRingList& other);
};

template <typename T>
THeadRingList<T>::THeadRingList() : TList<T>(), pHead(nullptr) {}

template <typename T>
THeadRingList<T>::THeadRingList(const THeadRingList& ringL) : TList<T>(ringL), pHead(nullptr) {
    if (!ringL.IsEmpty()) {
        pHead = new TNode<T>(ringL.pHead->data);
        TNode<T>* curr = ringL.pHead->pNext;
        TNode<T>* thisCurr = pHead;
        while (curr != ringL.pHead) {
            thisCurr->pNext = new TNode<T>(curr->data);
            thisCurr = thisCurr->pNext;
            curr = curr->pNext;
        }
        thisCurr->pNext = pHead;
    }
}

template <typename T>
THeadRingList<T>::~THeadRingList() {
    if (this->pFirst) {
        this->Clear();
        delete pHead;
    }
}

template <typename T>
void THeadRingList<T>::insert_first(const T& data) {
    TList<T>::insert_first(data);
    if (!pHead) {
        pHead = new TNode<T>(data);
        pHead->pNext = pHead; // ������ ��������� �� ����
    }
}

template <typename T>
void THeadRingList<T>::remove(const T& data) {
    if (!this->pFirst) {
        return;
    }

    if (this->pFirst->data == data) {
        TNode<T>* tmp = this->pFirst;
        this->pFirst = this->pFirst->pNext;
        delete tmp;

        if (this->pFirst == pHead) {
            delete pHead;
            pHead = nullptr;
        }
        return;
    }

    TList<T>::remove(data);

    if (!this->pFirst) {
        delete pHead;
        pHead = nullptr;
    }
}

template <typename T>
const THeadRingList<T>& THeadRingList<T>::operator=(const THeadRingList& other) {
    if (this == &other) {
        return *this;
    }
    TList<T>::operator=(other);
    // �������� ������� ���������� ������
    if (pHead) {
        delete pHead;
        pHead = nullptr;
    }
    // �������� �� ������ ������
    if (!other.pFirst) {
        return *this;
    }
    // ����������� ������ ���������� ������
    pHead = new TNode<T>(other.pHead->data);
    TNode<T>* curr = other.pHead->pNext;
    TNode<T>* thisCurr = pHead;

    // ����������� ��������� ���������� ������
    while (curr != other.pHead) {
        thisCurr->pNext = new TNode<T>(curr->data);
        thisCurr = thisCurr->pNext;
        curr = curr->pNext;
    }
    // ��������� ���������� ������
    thisCurr->pNext = pHead;
    return *this;
}


template <typename T>
void THeadRingList<T>::Clear() {
    TList<T>::Clear(); // �������� ������� ����������
    delete pHead; // ������� �������� ����
    pHead = nullptr; // ������������� ��������� �� �������� ���� � nullptr
    this->pStop = nullptr; // ��������� ��������� �� ���������
}



//template <typename T>
//THeadRingList<T>::THeadRingList() : TList<T>() {
//    pHead = new TNode<T>();
//    this->pStop = pHead;
//}
//
//template <typename T>
//THeadRingList<T>::THeadRingList(const THeadRingList<T>& ringL) : TList<T>(ringL) {
//    pHead = new TNode<T>(ringL.pHead->data, this->pFirst);
//    if (!ringL.IsEmpty()) {
//        this->pLast->pNext = pHead;
//    }
//    this->pStop = pHead;
//}
//
//template <typename T>
//THeadRingList<T>::~THeadRingList() {
//    delete pHead;
//}
//
////template <typename T>
////void THeadRingList<T>::insert_first(const T& data) {
////    TList<T>::insert_first(data);
////    pHead = new TNode<T>(data, this->pFirst); // ������� ����� ���� ��� pHead
////    this->pStop = pHead;
////    this->pLast->pNext = pHead;
////}
//
//
//template<typename T>
//void THeadRingList<T>::remove(const T& data) {
//    if (this->pFirst == nullptr) {
//        throw std::exception("List is empty");
//    }
//    TNode<T>* Current = this->pFirst;
//    if (Current->data == data) {
//        if (Current->pNext == pHead) {
//            this->pFirst = nullptr;
//            this->pCurrent = nullptr;
//            this->pLast = nullptr;
//            pHead->pNext = nullptr;
//            delete Current;
//            return;
//        }
//        this->pFirst = this->pFirst->pNext;
//        pHead->pNext = this->pFirst;
//        delete Current;
//        return;
//    }
//    TList<T>::remove(data);
//}
//
//
//
//template <typename T>
//void THeadRingList<T>::insert_first(const T& data) {
//    TList<T>::insert_first(data);
//    pHead = new TNode<T>(data, this->pFirst); // ������� ����� ���� ��� pHead
//    this->pStop = pHead;
//    this->pLast->pNext = pHead;
//}
//
//
//template<typename T>
//THeadRingList<T>& THeadRingList<T>::operator=(const THeadRingList& other) {
//    if (this == &other) { return *this; }
//    TList<T>::Clear(); // ������� ������� ������
//    TList<T>::operator=(other); // �������� ������ �� ������� �������
//    delete pHead; // ������� ���������� pHead
//    pHead = new TNode<T>(other.pHead->data, this->pFirst); // ������� ����� ���� ��� pHead
//    this->pStop = pHead; // ��������� ��������� �� ���������
//    return *this;
//}
//

////�������� � ����������
//template <typename T>
//THeadRingList<T>::THeadRingList() : TList<T>() {
//    pHead = new TNode<T>();
//    pStop = pHead;
//}


//template <class T>
//void THeadRingList<T>::Clear() {
//    TList<T>::Clear(); // ����� ������ Clear �� �������� ������ ��� ������� ������
//    pHead->pNext = pHead; // ��������� pNext ������ �� ���� ����, ����� ���������� ������ ������
//}

#endif 