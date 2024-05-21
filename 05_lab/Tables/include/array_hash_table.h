#ifndef _ARRAY_HASH_TABLE_H
#define _ARRAY_HASH_TABLE_H

#include "hash_table.h"

template<typename TKey, typename TData>
class ArrayHashTable : public HashTable<TKey, TData> {
private:
    TabRecord<TKey, TData>** recs;
    TabRecord<TKey, TData>* pMark;
    int freePos;
    int hashStep;
    int GetNextPos(int h_val);

public:
    ArrayHashTable(int n, int step);
    ArrayHashTable(const ArrayHashTable& ahtable);
    ~ArrayHashTable();
    TabRecord<TKey, TData>* Search(const TKey& key);
    void Insert(const TKey& key, TData* data);
    void Remove(const TKey& key);
    void Reset();
    void Next();
    TabRecord<TKey, TData>* GetCurrent() const;

    friend std::ostream& operator<<(std::ostream& out, const ArrayHashTable<TKey, TData>& t) {
        if (t.IsEmpty()) {
            out << "Table is empty" << std::endl;
            return out;
        }
        ArrayHashTable<TKey, TData> table(t);
        table.Reset();
        while (!table.IsEnded()) {
            out << *table.GetCurrent();
            table.Next();
        }
        return out;
    }
};


template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::ArrayHashTable(int n, int step) : HashTable<TKey, TData>(n) {
	maxSize = n;
	hashStep = step;
	recs = new TabRecord<TKey, TData>* [n];
	pMark = new TabRecord<TKey, TData>();

	for (int i = 0; i < n; ++i) {
		recs[i] = nullptr;
	}

	freePos = -1;
	count = 0;
	currPos = 0;
}
