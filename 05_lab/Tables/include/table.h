#ifndef _TABLE_H
#define _TABLE_H
#include "tab_record.h"

template <typename TKey, typename TData>
class Table {
protected:
    int count;
    int maxSize;
    int currPos;
public:
    Table(int maxSize);
    virtual ~Table() {}

    virtual TabRecord<TKey, TData>* Find(TKey key) = 0;
    virtual void Insert(TKey key, TData* data) = 0;
    virtual void Remove(TKey key) = 0;
    virtual TabRecord<TKey, TData>* GetCurrent() const = 0;

    virtual bool IsFull() const;
    virtual bool IsEmpty() const;
    virtual bool IsEnded() const;

    virtual void Reset();
    virtual void Next();
   
};

template <typename TKey, typename TData>
Table<TKey, TData>::Table(int maxSize) : count(0), maxSize(maxSize), currPos(-1) {}

template <typename TKey, typename TData>
bool Table<TKey, TData>::IsFull() const {
    return (count == maxSize);
}

template <typename TKey, typename TData>
bool Table<TKey, TData>::IsEmpty() const {
    return (count == 0);
}

template <typename TKey, typename TData>
bool Table<TKey, TData>::IsEnded() const {
    return (currPos == maxSize - 1);
}

template <typename TKey, typename TData>
void Table<TKey, TData>::Reset() {
    currPos = 0;
}

template <typename TKey, typename TData>
void Table<TKey, TData>::Next() {
    if (IsEnded()) 
        throw ("Table end");
    currPos++;
}

#endif 
