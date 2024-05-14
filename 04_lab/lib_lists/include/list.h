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
	TNode<T>* pPrev;
public:
	TList();
	TList(const TList<T>& list);
	TList(TNode<T>* _pFirst);
	virtual ~TList();

	//TNode<T>* search_prev(const T& _data) const;
	TNode<T>* search(const T& data);

	virtual void insert_first(const T& data);
	void insert_last(const T& data);

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
	//const TList<T>& operator=(const TList<T>& other);
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

template <typename T>
void TList<T>::Clear() {
	TNode<T>* tmp;
	for (TNode<T>* node = pFirst; node && node != pStop; node = tmp) {
		tmp = node->pNext;
		delete node;
	}
	pFirst = pPrev = pLast = pCurrent = nullptr;
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

template <typename T>
void TList<T>::insert_before(const T& who, const T& where) {
	TNode<T>* pWhere = search(where);
	if (pWhere == nullptr) {
		throw std::exception("No elements");
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
		throw std::exception("No elements");
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

template <typename T>
void TList<T>::remove(const T& data_) {
	if (IsEmpty())
		throw std::exception("List is empty!");
	TNode<T>* rem_elem = pFirst;
	TNode<T>* pPrev_rem_elem = nullptr; // search
	while (rem_elem != pStop && rem_elem->data != data_)
	{
		pPrev_rem_elem = rem_elem;
		rem_elem = rem_elem->pNext;
	}
	if (rem_elem == pFirst) {
		pFirst = pFirst->pNext;
		delete rem_elem;
		return;
	}
	if (rem_elem == pStop)
		throw std::exception("Data not found!");
	pPrev_rem_elem->pNext = rem_elem->pNext;
	delete rem_elem;
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

template <typename T>
const TList<T>& TList<T>::operator=(const TList<T>& other) {
    if (this == &other) {
        return *this;
    }

    Clear(); // Очищаем текущий список

    TNode<T>* otherCurr = other.pFirst;
    TNode<T>* curr = nullptr; // Указатель на текущий элемент в текущем списке
	// copy other.pFirst, then append

    while (otherCurr != nullptr) {
        // Копируем данные из списка other
        insert_last(otherCurr->data);

        // Если пока не найден эквивалентный элемент в текущем списке и текущий элемент не равен nullptr,
        // то сравниваем данные текущего элемента в текущем списке с данными текущего элемента в списке other
        if (curr == nullptr && pFirst != nullptr && pFirst->data == otherCurr->data) {
            curr = pFirst; // Устанавливаем указатель на текущий элемент в текущем списке
        }

        otherCurr = otherCurr->pNext;
    }

    pCurrent = curr; // Устанавливаем pCurrent на найденный эквивалентный элемент в текущем списке

    return *this;
} 

//template <typename T>
//const  TList<T>& TList<T>::operator=(const TList<T>& other) {
//	if (this == &other) {
//		return *this;
//	}
//	Clear(); // Очищаем текущий объект
//	if (other.IsEmpty()) {
//		return *this;
//	}
//	TNode<T>* otherCurr = other.pFirst;
//	while (otherCurr != nullptr) {
//		insert_last(otherCurr->data);
//		otherCurr = otherCurr->pNext;
//	}
//	// Найдем эквивалент элемента pPrev в новом списке
//	TNode<T>* curr = pFirst;
//	TNode<T>* otherCurrent = other.pFirst;
//	while (otherCurrent != nullptr && curr != nullptr && curr->data != otherCurrent->data) {
//		curr = curr->pNext;
//		otherCurrent = otherCurrent->pNext;
//	}
//	pCurrent = curr;
//
//	return *this;
//}




#endif