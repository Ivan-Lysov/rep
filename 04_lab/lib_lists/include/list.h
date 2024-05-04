#ifndef _LIST_H
#define _LIST_H
#include "node.h"

template <typename T>
class TList {
protected:
	TNode<T>* pFirst;
	TNode<T>* pLast;
    TNode<T>* pCurrent;
    TNode<T>* pStop = nullptr;
public:
	TList();
	TList(const TList<T>& list);
    TList(TNode<T>* _pFirst);
	virtual ~TList();

	TNode<T>* search(const T& _data) const;

	virtual void insert_first(const T& data);
    virtual void insert_last(const T& data);

	void insert_before(const T& data, const T& nextdata);
	void insert_after(const T& data, const T& beforedata);

    virtual void remove(const T& data);

	int GetSize() const;
    void Clear(); // virtual
	void reset();
    void next();
    bool IsEnded() const;
    T& GetCurrent() const;

	bool IsEmpty() const;
	bool IsFull() const;

	void insert_sort(const T& data);
	virtual void Sort();

    const TList<T>& operator=(const TList<T>& other);
};

template <typename T>
TList<T>::TList() {
	pFirst = nullptr;
	pLast = nullptr;
	pCurrent = nullptr;
}

template <typename T>
TList<T>::TList(const TList& list) {
	if (list.IsEmpty())  
	{
		pFirst = nullptr;
		pLast = nullptr;
		pCurrent = nullptr;
		return;
	}

	pFirst = new TNode<T>(list.pFirst->data);
	TNode<T>* node_tmp = pFirst;
	TNode<T>* list_tmp = list.pFirst->pNext;
	while (list_tmp != list.pStop)
	{
		node_tmp->pNext = new TNode<T>(list_tmp->data);
		node_tmp = node_tmp->pNext;
		list_tmp = list_tmp->pNext;
	}
	pLast = node_tmp;
	pCurrent = pFirst;
}

template <typename T>
TList<T>::TList(TNode<T>* pNode) {
    pFirst = pNode;
    TNode<T>* tmp = pNode;
    while (tmp->pNext != nullptr) {
        tmp = tmp->pNext;
    }
    pLast = tmp;
    pCurrent = pFirst;
}

template <typename T>
TList<T>::~TList() {
    Clear();
}

template <typename T>
void TList<T>::Clear() {
    TNode<T>* tmp;
    for (TNode<T>* node = pFirst; node && node != pStop; node = tmp) {
        tmp = node->pNext;
        delete node;
    }
	pFirst = pLast = nullptr;
    pCurrent = nullptr;
}

template <typename T>
bool TList<T>::IsFull() const {
	TNode<T>* tmp = new TNode<T>();
	if (tmp == nullptr)
		return true;
	delete tmp;
	return false;
}
	//return !IsEmpty();

template <typename T>
bool TList<T>::IsEmpty() const {
	return (pFirst == nullptr);
}

template <typename T>
bool TList<T>::IsEnded() const {
	return !pCurrent || (pCurrent == pStop);
}

template <typename T>
TNode<T>* TList<T>::search(const T& _data) const { // prev
	TNode<T>* Current = pFirst;
	while (Current != pStop && Current->data != _data) {
		Current = Current->pNext;
	}
	if (Current == pStop) {
		return nullptr;
	}
	return Current;
}

template <typename T>
void TList<T>::insert_first(const T& data) { 
	TNode<T>* new_first = new TNode<T>(data, pFirst);
	pFirst = new_first;
	if (pLast == nullptr) {
		pLast = pFirst;
	}
	pCurrent = pFirst;
}

template <typename T>
void TList<T>::insert_last(const T& data) {
	if (IsEmpty()) {
		insert_first(data);
		return;
	}
	TNode<T>* new_last = new TNode<T>(data, pStop);
	pLast->pNext = new_last;
	pLast = new_last;
	pCurrent = new_last;
}

template <typename T>
void TList<T>::insert_before(const T& what, const T& where) {
	TNode<T>* pWhere = search(where);
	if (pWhere == nullptr) {
		throw "Element not found"; // Throw an exception if the element is not found
	}
	if (pWhere == pFirst) {
		insert_first(what);
		return;
	}
	TNode<T>* pPrev = pFirst;// search
	while (pPrev->pNext != pWhere) {
		pPrev = pPrev->pNext;
	}
	TNode<T>* new_node = new TNode<T>(what, pWhere);
	pPrev->pNext = new_node;
}


template <typename T>
void TList<T>::insert_after(const T& who, const T& where) {
	TNode<T>* pWhere = search(where);
	if (pWhere == nullptr) {
		throw "Element not found"; 
	}
	if (pWhere == pLast) {
		insert_last(who);
		return;
	}
	TNode<T>* new_node = new TNode<T>(who, pWhere->pNext);
	pWhere->pNext = new_node;
}

template <typename T>
void TList<T>::remove(const T& data_) { 
	if (IsEmpty()) 
		throw "List is empty!";
	TNode<T>* rem_elem = pFirst;
	TNode<T>* pPrevious = nullptr;
	while (rem_elem != pStop && rem_elem->data != data_)
	{
		pPrevious = rem_elem;
		rem_elem = rem_elem->pNext;
	}
	if (rem_elem == pFirst){
		pFirst = pFirst->pNext;
		delete rem_elem;
		return;
	}
	if (rem_elem == pStop)
		throw "Data not found!";
	pPrevious->pNext = rem_elem->pNext;
	delete rem_elem;
}

template <typename T>
void TList<T>::reset() {
	pCurrent = pFirst;
}

template <typename T>
void TList<T>::next() {
    if (IsEnded()) {
        throw std::range_error("List is ended");
    }
	pCurrent = pCurrent->pNext;
}

template<typename T>
int TList<T>::GetSize() const {
	if (pFirst == nullptr) 
		return 0;

	int size = 0;
    for (TNode<T>* node = pFirst; node != pStop; node = node->pNext) {
        ++size;
    }
	return size;
}

template<typename T>
T& TList<T>::GetCurrent() const {
	return pCurrent->data;
}

template <typename T>
void TList<T>::insert_sort(const T& data) {
	if (IsEmpty() || data < pFirst->data) {
		insert_first(data);
		return;
	}
	TNode<T>* tmp = pFirst;
	while (tmp->pNext != pStop && tmp->pNext->data <= data) {
		tmp = tmp->pNext;
	}
	insert_after(data, tmp->data); 
}

template <typename T>
void TList<T>::Sort() {
	if (IsEmpty() || GetSize() == 1) {
		return;
	}

	TNode<T>* Current = pFirst;
	TNode<T>* Previous = nullptr;

	bool sorted = false;
	while (!sorted) {
		sorted = true;
		Current = pFirst;
		Previous = nullptr;

		while (Current->pNext != nullptr && Current->pNext != pStop) {
			TNode<T>* next = Current->pNext;

			if (Current->data < next->data) { // Используем пользовательскую функцию сравнения
				// Поменяйте узлы местами
				if (Previous == nullptr) {
					// Если current является первым узлом
					pFirst = next;
				}
				else {
					Previous->pNext = next;
				}

				Current->pNext = next->pNext;
				next->pNext = Current;

				// Обновление указателей
				Previous = next;
				sorted = false;
			}
			else {
				Previous = Current;
				Current = Current->pNext;
			}
		}
	}

	pCurrent = pFirst;
}

template<typename T>
const TList<T> &TList<T>::operator=(const TList<T>& other) {
    if (this == &other)
        return *this;

    // copy-and-swap
    //
    // 1) создается временная копия other
    // 2) происходит обмен данных текущего экземпляра и tmp
    // 3) вызывается деструктор tmp - он удаляет наши бывшие данные
    // 4) PROFIT
    //
    // если просто присвоить полям текущего экземпляра значения полей
    // временного, то при вызове деструктора tmp они удалятся, и мы останемся
    // с мусором, память же выделенная под "наши" данные просто утечет

    TList<T> tmp(other); // todo
    std::swap(pFirst, tmp.pFirst);
    std::swap(pLast, tmp.pLast);
    std::swap(pCurrent, tmp.pCurrent);
    std::swap(pStop, tmp.pStop);

    return *this;
}

#endif