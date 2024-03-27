#ifndef _STACK_H
#define _STACK_H
#include <iostream>
#include <map>
#include <vector>
#include <string>
const int _maxSize = 10;
const int _step = 10;

template <typename T>
class TStack {
private:
	T* elems;
	int maxSize;
	int top;

	void Realloc(int step = _step);
public:
	TStack(int Size = _maxSize);
	TStack(const TStack<T>& stack);
	virtual ~TStack();
	T Pop();
	T Top() const;
	void Push(const T& elm);
	bool IsEmpty(void) const;
	bool IsFull(void) const;
};

template <typename T>
TStack<T>::TStack(int Size) {
	if (Size <= 0) throw "maxSize must be bigger than 0.";
	maxSize = Size;
	top = -1;
	elems = new T[maxSize];
}

template <typename T>
TStack<T>::TStack(const TStack<T>& stack) {
	maxSize = stack.maxSize;
	top = stack.top;
	elems = new T[maxSize];
	for (int i = 0; i <= top; i++) {
		elems[i] = stack.elems[i];
	}
}

template <typename T>
TStack<T>::~TStack() {
	if (elems != NULL) {
		delete[] elems;
		top = -1;
		maxSize = 0;
	}
}

template <class T>
void TStack<T>::Realloc(int step)
{
	if (step <= 0) { throw "Step must be greater than 0"; }
	T* tmp = new T[step + maxSize];
	for (int i = 0; i < maxSize; i++) {
		tmp[i] = elems[i];
	}
	delete[] elems;
	elems = tmp;
	maxSize += step;
}

template <typename T>
bool TStack<T>::IsFull(void) const {
	return (top == maxSize - 1);
}

template <typename T>
bool TStack<T>::IsEmpty(void) const {
	return (top == -1);
}

template <typename T>
T TStack<T>::Top() const {
	if (IsEmpty()) { throw "Stack is empty."; }
	return elems[top];
}

template <typename T>
void TStack<T>::Push(const T& elm) {
	if (IsFull()) { Realloc(_step); }
	elems[++top] = elm;
}

template <typename T>
T TStack<T>::Pop() {
	if (IsEmpty()) {throw "Stack is empty!";}
	return elems[top--];
}


#endif 
