#ifndef _LIST_H
#define _LIST_H
#include "node.h"

	template <typename T>
	class TList {
	protected:
		TNode<T>* pFirst;
		TNode<T>* pCurrent;
		TNode<T>* pStop;
		TNode<T>* pLast;
	public:
		TList();
		TList(TNode<T>* _pFirst);
		TList(const TList<T>& list);
		virtual ~TList();

		virtual void insert_first(const T& data);
		virtual void remove(const T& data);
		void insert_before(const T& data, const T& nextdata);
		virtual void insert_last(const T& data);
		void insert_after(const T& data, const T& beforedata);
		TNode<T>* search(const T& _data);
		TNode<T>* GetCurrent() const;
		void Clear();
		int GetSize() const;
		bool IsEmpty() const;
		bool IsFull() const;
		bool IsEnded()const;
		void next();
		void reset();
		void insert_sort(const T& data);
		void Sort(); //????
	};

template <typename T>
TList<T>::TList() {
	pFirst = nullptr;
	pLast = nullptr;
	pCurrent = nullptr;
	pStop = nullptr;
}

template <typename T>
TList<T>::TList(const TList& list) {
	if (list.IsEmpty()) //если список пуст 
	{
		pFirst = nullptr;//то указатели
		pLast = nullptr;//становятся нулями
		pCurrent = nullptr;//
		pStop = nullptr;
		return;
	}

	pFirst = new TNode<T>(list.pFirst->data);//создание первого узла нового списка с данными исходного
	TNode<T>* node_tmp = pFirst;//созддание переменноц узла для копирования
	TNode<T>* list_tmp = list.pFirst->pNext;//Инициализируется указатель на следующиц элдемент
	while (list_tmp != list.pStop)
	{//через tmp проиходит копированеие элементов одного списка в другой
		node_tmp->pNext = new TNode<T>(list_tmp->data);
		node_tmp = node_tmp->pNext;
		list_tmp = list_tmp->pNext;
	}
	pLast = node_tmp;
	pCurrent = pFirst;
	pStop = nullptr;//конец списка
}

template <typename T>
TList<T>::TList(TNode<T>* pNode) {
	pFirst = pNode;
	TNode<T>* tmp = pNode; //tmp тут для перемещения по списку
	while (tmp->pNext != nullptr)
		tmp = tmp->pNext;
	//в коннце цикла мы получаем что tmp указывает на полседний элемент в переданном списке.
	pLast = tmp;
	pCurrent = pFirst;
	pStop = nullptr;
}

template <typename T>
void TList<T>::Clear()
	{
	TNode<T>* curr_in_cl = pFirst;
	while (curr_in_cl != pStop)
	{
		if (pFirst == nullptr) return;
		pFirst = pFirst->pNext;//кидает ошибку при диффернцировании pFirst = nullptr
		delete curr_in_cl;
		curr_in_cl = pFirst;
	}
	pCurrent = pStop = pLast = nullptr;
}

template <typename T>
TList<T>::~TList() {
	Clear();
}

template <typename T>
bool TList<T>::IsFull() const {
	return !IsEmpty;
	//bool TList<T>::IsFull() const {
	//	TNode<T>* tmp = new TNode<T>();
	//	if (tmp == nullptr)
	//		return true;
	//	delete tmp;
	//	return false;
	//}
}

template <typename T>
bool TList<T>::IsEmpty() const {
	return (pFirst == nullptr);
}

template <typename T>
bool TList<T>::IsEnded()const {
	return (pCurrent == pStop);
}

template <typename T>
TNode<T>* TList<T>::search(const T& _data) {
	TNode<T>* Current = pFirst;
	while (Current != pStop && Current->data != _data) {
		Current = Current->pNext;
	}
	if (Current == pStop) {
		return nullptr;
	}
	return Current;
}

template <typename T> //https://disk.yandex.ru/i/dr-qOv5r8HLjWw
void TList<T>::insert_first(const T& data) { 
	TNode<T>* new_first = new TNode<T>(data, pFirst);
	pFirst = new_first;
	if (pLast == nullptr) {
		pLast = pFirst;
	}
	pCurrent = pFirst;
}

template <typename T>//https://disk.yandex.ru/i/vBT6jwjoL8N0Sw
void TList<T>::insert_last(const T& data) {
	if (IsEmpty()) {
		insert_first(data);
		return;
	}
	TNode<T>* new_last = new TNode<T>(data, pStop);
	pLast->pNext = new_last;
	pLast = new_last;
	pCurrent = new_last;//обеспечивает доступ к последнему узлу для операций, которые этого требуют
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
	TNode<T>* pPrev = pFirst;
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
		throw "Element not found"; // Throw an exception if the element is not found
	}
	if (pWhere == pLast) {
		insert_last(who);
		return;
	}
	TNode<T>* new_node = new TNode<T>(who, pWhere->pNext);
	pWhere->pNext = new_node;
}

template <typename T>
void TList<T>::remove(const T& data_) { //https://disk.yandex.ru/i/coSxaWOPWEQDbQ
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

template <typename T>//обновление указателя текуцщего указателя
void TList<T>::reset() {
	pCurrent = pFirst;//теперь текуцщий указатель указывает на первый элемент
}

template <typename T>
void TList<T>::next() {
	if (pCurrent == pStop)
		throw "List is ended";
	pCurrent = pCurrent->pNext;
}

template<typename T>
int TList<T>::GetSize() const {
	if (pFirst == nullptr) 
		return 0;
	int size = 0;
	TNode<T>* count_node = pFirst;
	while (count_node != pStop) {
		size++;
		count_node = count_node->pNext;
	}
	return size;
}

template<typename T>
TNode<T>* TList<T>::GetCurrent()const {
	return pCurrent;
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
	if (tmp->data == data) {
		tmp->data = tmp->data + data;
		return;
	}
	insert_after(data, tmp->data);
}
template <typename T>
bool operator < (const T& node1, const T& node2) {
	return node1 < node2;
}
template <typename T>
bool operator > (const T& node1, const T& node2) {
	return node1 > node2;
}

template <typename T>
void TList<T>::Sort() {
	if (IsEmpty() || GetSize() == 1) {
		return;
	}

	TNode<T>* current = pFirst;
	TNode<T>* prev = nullptr;

	bool sorted = false;
	while (!sorted) {
		sorted = true;
		current = pFirst;
		prev = nullptr;

		while (current->pNext != nullptr && current->pNext != pStop) {
			TNode<T>* next = current->pNext;

			if (current->data < next->data) { // Используем пользовательскую функцию сравнения
				// Поменяйте узлы местами
				if (prev == nullptr) {
					// Если current является первым узлом
					pFirst = next;
				}
				else {
					prev->pNext = next;
				}

				current->pNext = next->pNext;
				next->pNext = current;

				// Обновление указателей
				prev = next;
				sorted = false;
			}
			else {
				prev = current;
				current = current->pNext;
			}
		}
	}

	pCurrent = pFirst;
}
#endif