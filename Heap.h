#ifndef  _HEAP_H_
#define _HEAP_H_

#include <vector>
#include <algorithm>

template<typename T>
class Heap {
private:
    std::vector<T> data;

public:
    Heap();

    void insert(const T& value);
    void removeTop();
    const T& top() const;
    bool isEmpty() const;
    size_t size() const;
};

#include "Heap.hxx"



#endif
