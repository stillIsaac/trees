#include "Heap.h"

#include <vector>
#include <algorithm>
#include <string>
    template <class T>
    Heap<T>::Heap() {}

// Inserta un elemento en el heap
    template <class T>
    void Heap<T>::insert(std::string value) {

        int intVal = stoi(value);
        data.push_back(intVal);
        std::push_heap(data.begin(), data.end(), std::greater<int>());
    }

    // Elimina el elemento mínimo (o máximo) del heap
    template <class T>
    void Heap<T>::removeTop() {

        std::pop_heap(data.begin(), data.end());
        data.pop_back();
    }

    // Retorna el elemento mínimo (o máximo) del heap
    template <class T>
    T Heap<T>::top() {

        return data.front();
    }

    // Verifica si el heap está vacío
    template <class T>
    bool Heap<T>::isEmpty() {

        return data.empty();
    }

    // Retorna el tamaño del heap
    template <class T>
    int Heap<T>::size() {

        return data.size();
    }

    template <class T> 
    std::vector<T> Heap<T>::getSort() {

        std::vector<T> elVec = this->data;
        std::sort(std::begin(elVec), std::end(elVec));
        return elVec;

    }
    
    template <class T>
    void Heap<T>::erase(std::string valor) {

        int intVal = stoi(valor);
        typename std::vector<T>::iterator it = std::find(this->data.begin(), this->data.end(), intVal);
        if (it != data.end()) {

            std::iter_swap(it, data.end() - 1);
            data.pop_back();
            std::make_heap(data.begin(), data.end(), std::greater<T>());
        }

    }

