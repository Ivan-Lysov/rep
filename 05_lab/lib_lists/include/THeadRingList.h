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
        // Если удаляемый элемент был головой списка, обновляем pHead на новую голову
        pHead = this->pFirst;
    }
    // Обновляем pCurrent
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
//    TList<T>::Clear(); // Вызываем базовую реализацию
//
//    if (pHead != nullptr) {
//        delete pHead; // Удаляем головной узел
//        pHead = nullptr; // Устанавливаем указатель на головной узел в nullptr
//    }
//
//    // Обновляем указатель на остановку
//    this->pStop = nullptr; // Это нужно, если pStop был установлен на узел списка, который был удален базовым методом Clear()
//}

//template <typename T>
//const THeadRingList<T>& THeadRingList<T>::operator=(const THeadRingList& other) {
//    if (this == &other) {
//        return *this;
//    }
//
//    // Вызываем оператор присваивания базового класса для копирования данных
//    TList<T>::operator=(other);
//
//    // Очищаем старый кольцевой список
//    if (pHead) {
//        delete pHead;
//        pHead = nullptr;
//    }
//
//    // Если список other не пустой, копируем его элементы
//    if (other.pFirst) {
//        pHead = new TNode<T>(other.pHead->data);
//        TNode<T>* curr = other.pHead->pNext;
//        TNode<T>* thisCurr = pHead;
//
//        // Копируем остальные элементы кольцевого списка
//        while (curr != other.pHead) {
//            thisCurr->pNext = new TNode<T>(curr->data);
//            thisCurr = thisCurr->pNext;
//            curr = curr->pNext;
//        }
//
//        // Замыкаем кольцевой список
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