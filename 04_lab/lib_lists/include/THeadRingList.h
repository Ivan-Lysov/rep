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
        pHead->pNext = pHead; // Голова указывает на себя
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
    // Удаление старого кольцевого списка
    if (pHead) {
        delete pHead;
        pHead = nullptr;
    }
    // Проверка на пустой список
    if (!other.pFirst) {
        return *this;
    }
    // Копирование головы кольцевого списка
    pHead = new TNode<T>(other.pHead->data);
    TNode<T>* curr = other.pHead->pNext;
    TNode<T>* thisCurr = pHead;

    // Копирование элементов кольцевого списка
    while (curr != other.pHead) {
        thisCurr->pNext = new TNode<T>(curr->data);
        thisCurr = thisCurr->pNext;
        curr = curr->pNext;
    }
    // Замыкание кольцевого списка
    thisCurr->pNext = pHead;
    return *this;
}


template <typename T>
void THeadRingList<T>::Clear() {
    TList<T>::Clear(); // Вызываем базовую реализацию
    delete pHead; // Удаляем головной узел
    pHead = nullptr; // Устанавливаем указатель на головной узел в nullptr
    this->pStop = nullptr; // Обновляем указатель на остановку
}

#endif 