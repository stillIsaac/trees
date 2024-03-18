#ifndef  _NODOAVL_H_
#define _NODOAVL_H_

template < class T >
class NodoAvl {

    public: 
        T dato;
        NodoAvl<T> *hijoIzq;
        NodoAvl<T> *hijoDer;
     
        NodoAvl(): dato(T()), hijoIzq(nullptr), hijoDer(nullptr) {
            
        }

        NodoAvl(T val) {
            dato = val;
            hijoDer = NULL;
            hijoIzq = NULL;
        }
};

#include "NodoAvl.hxx"



#endif