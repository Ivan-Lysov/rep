#ifndef _LIST_H
#define _LIST_H
#include "node.h"

template <typename T>
class TList {
protected:
	TNode<T>* pFirst;
	TNode<T>* pLast;
	TNode<T>* pCurrent;
	TNode<T>* pStop;
	TNode<T>* pPrev;
public:
	TList();
	TList(const TList<T>& list);
	TList(TNode<T>* _pFirst);
	virtual ~TList();

	TNode<T>* search(const T& data);

	virtual void insert_first(const T& data);
	void insert_last(const T& data);//

	void insert_before(const T& who, const T& where);
	void insert_after(const T& who, const T& where);

	virtual void remove(const T& data);

	int GetSize() const;
	virtual void Clear();
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
	pPrev = nullptr;
	pStop = nullptr;
}

template <typename T>
TList<T>::TList(const TList& list) {
	if (list.IsEmpty())
	{
		pFirst = nullptr;
		pLast = nullptr;
		pCurrent = nullptr;
		pPrev = nullptr;
		pStop = nullptr;
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
	pStop = pPrev = nullptr;
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
	pStop = pPrev = nullptr;
}

template <typename T>
TList<T>::~TList() {
	Clear();
}

template <typename TData>
void TList<TData>::Clear() {
	if (pFirst == nullptr)
		return;
	TNode<TData>* curr = pFirst;
	TNode<TData>* next = pFirst->pNext;
	while (next != pStop) {
		delete curr;
		curr = next;
		next = curr->pNext;
	}
	delete curr;
	pCurrent = nullptr;
	pFirst = nullptr;
	pPrev = nullptr;
	pLast = nullptr;
}

template <typename T>
bool TList<T>::IsFull() const {
	TNode<T>* tmp = new TNode<T>();
	if (tmp == nullptr)
		return true;
	delete tmp;
	return false;
}

template <typename T>
bool TList<T>::IsEmpty() const {
	return (pFirst == nullptr);
}

template <typename T>
bool TList<T>::IsEnded() const {
	return (pCurrent == pStop);
}

template <typename T>
void TList<T>::insert_first(const T& data) {
	pFirst = new TNode<T>(data, pFirst);
	if (pLast == nullptr) {
		pLast = pFirst;
	}
	pCurrent = pFirst;
	pPrev = nullptr;
}

template <typename T>
void TList<T>::insert_last(const T& data) {
	if (IsEmpty()) {
		insert_first(data);
		return;
	}

	pLast->pNext = new TNode<T>(data, pStop);
	pLast = pLast->pNext;
	pCurrent = pLast;
}

template <typename T>
TNode<T>* TList<T>::search(const T& data) {
	if (IsEmpty())
		return nullptr;

	TNode<T>* prev = nullptr;
	TNode<T>* curr = pFirst;

	while (curr != pStop && curr->data != data) {
		prev = curr;
		curr = curr->pNext;
	}

	if (curr == pStop)
		return nullptr;
	pCurrent = curr;
	pPrev = prev;
	return curr;
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

template <typename T>
void TList<T>::insert_before(const T& who, const T& where) {
	TNode<T>* pWhere = search(where);
	if (pWhere == nullptr) {
		throw std::exception("no elements");
	}

	if (pWhere == pFirst) {
		insert_first(who);
		return;
	}
	TNode<T>* new_node = new TNode<T>(who, pWhere);
	pPrev->pNext = new_node;
	pCurrent = new_node;
}

template <typename T>
void TList<T>::insert_after(const T& who, const T& where) {
	TNode<T>* pWhere = search(where);
	if (pWhere == nullptr) {
		throw std::exception("no elements");
	}
	if (pWhere == pLast) {
		insert_last(who);
		return;
	}
	TNode<T>* new_node = new TNode<T>(who, pWhere->pNext);
	pWhere->pNext = new_node;
	pCurrent = new_node;
	pPrev = pWhere;
}

template <typename TData>
void TList<TData>::remove(const TData& where)
{
	TNode<TData>* pWhere = search(where);
	if (pWhere == nullptr) {
		throw std::exception("no elements");
	}

	if (pWhere == pFirst && pWhere->pNext == pStop)
	{
		Clear();
		return;
	}
	if (pWhere == pFirst)
	{
		TNode<TData>* first = pFirst;
		pFirst = pFirst->pNext;
		delete first;
		pCurrent = pFirst;
		return;
	}
	if (pWhere == pLast)
	{
		pPrev->pNext = pStop;
		pLast = pPrev;
		pCurrent = pStop;
		delete pWhere;
		return;
	}
	pPrev->pNext = pWhere->pNext;
	pCurrent = pWhere->pNext;
	delete pWhere;

}

template <typename T>
void TList<T>::reset() {
	pCurrent = pFirst;
	pPrev = nullptr;
}

template <typename T>
void TList<T>::next() {
	if (IsEnded()) {
		throw std::range_error("List is ended");
	}
	pPrev = pCurrent;
	pCurrent = pCurrent->pNext;
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

			if (Current->data < next->data) { 
				if (Previous == nullptr) {
					pFirst = next;
				}
				else {
					Previous->pNext = next;
				}

				Current->pNext = next->pNext;
				next->pNext = Current;

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



template <typename T>
const TList<T>& TList<T>::operator=(const TList<T>& other)
{
	if (this == &other) { return *this; }
	Clear();
	TNode<T>* otherCurr = other.pFirst;
	while (otherCurr != other.pLast)
	{
		insert_last(otherCurr->data);
		otherCurr = otherCurr->pNext;
	}
	insert_last(otherCurr->data);

	return *this;
}

#endif