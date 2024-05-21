#ifndef _SORTED_TABLE_H
#define _SORTED_TABLE_H
#include <scan_table.h>

template <typename TKey, typename TData>
class SortedTable : public ScanTable<TKey, TData> {
private:
    void QuickSort(TabRecord<TKey, TData>** arr, int left, int right);
public:
    SortedTable(int maxSize);
    SortedTable(const ScanTable<TKey, TData>& table);

    TabRecord<TKey, TData>* Find(TKey key) override;
    void Insert(TKey key, TData* data) override;
};


template <typename TKey, typename TData>
SortedTable<TKey, TData>::SortedTable(int maxSize) : ScanTable<TKey, TData>(maxSize) {}

template <typename TKey, typename TData>
SortedTable<TKey, TData>::SortedTable(const ScanTable<TKey, TData>& table) : ScanTable<TKey, TData>(table) {
    if (!IsEmpty()) {
        QuickSort(recs, 0, count - 1);
    }
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* SortedTable<TKey, TData>::Find(TKey key) {
    int left = 0;
    int right = count - 1;

    while (left <= right) {
        int middle = (left + right) / 2;
        if (recs[middle]->GetKey() == key) {
            return recs[middle];
        }
        else if (recs[middle]->GetKey() > key) {
            right = middle - 1;
        }
        else {
            left = middle + 1;
        }
    }

    return nullptr;
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::Insert(TKey key, TData* data) {
    if (IsFull()) {
        throw "Table is full";
    }

    if (Find(key) != nullptr) {
        throw "Key already exists";
    }

    int insertIndex = count;
    while (insertIndex > 0 && recs[insertIndex - 1]->GetKey() > key) {
        recs[insertIndex] = recs[insertIndex - 1];
        insertIndex--;
    }

    recs[insertIndex] = new TabRecord<TKey, TData>(key, data);
    count++;
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::QuickSort(TabRecord<TKey, TData>** arr, int left, int right) {
    if (left >= right)  return;

    int i = left;
    int j = right;

    TabRecord<TKey, TData>* middle = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i]->GetKey() < middle->GetKey())
            i++;
        while (arr[j]->GetKey() > middle->GetKey())
            j--;
        if (i <= j) {
            TabRecord<TKey, TData>* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    QuickSort(arr, left, j);
    QuickSort(arr, i, right);
}


template <typename TKey, typename TData>//
void SortedTable<TKey, TData>::Remove(TKey key) {
    if (IsEmpty())
        throw std::exception("");
    TabRecord<TKey, TData>* res = Find(key);
    if (res == nullptr)
        throw std::exception("");
    delete res;
    for (int i = currpos; i < count - 1; i++)
        recs[i] = recs[i++];
    count--;
}

#endif 
