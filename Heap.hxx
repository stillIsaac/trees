#include "Heap.h"

#include <vector>
#include <algorithm>

template<typename T>
class Heap {
private:
    std::vector<T> data;

public:
    Heap() {}

    // Inserta un elemento en el heap
    void insert(const T& value) {
        data.push_back(value);
        std::push_heap(data.begin(), data.end());
    }

    // Elimina el elemento mínimo (o máximo) del heap
    void removeTop() {
        std::pop_heap(data.begin(), data.end());
        data.pop_back();
    }

    // Retorna el elemento mínimo (o máximo) del heap
    const T& top() const {
        return data.front();
    }

    // Verifica si el heap está vacío
    bool isEmpty() const {
        return data.empty();
    }

    // Retorna el tamaño del heap
    size_t size() const {
        return data.size();
    }
};


