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

    void insert(std::string value);
    void removeTop();
    T top() ;
    bool isEmpty() ;
    int size() ;
    std::vector<T> getSort();
    void erase(std::string valor);
};

#include "Heap.hxx"



#endif
