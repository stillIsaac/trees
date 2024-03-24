#ifndef _ARBOLAVL_H_
#define _ARBOLAVL_H_

#include "NodoAvl.h"

template< class T >
class ArbolAvl {

    public:
        ArbolAvl();

        NodoAvl<T> *raiz;
        bool esVacio();
        int altura();
        int altura(NodoAvl<T> *nodo);
        int tamano();
        NodoAvl<T>* rotacionDerecha(NodoAvl<T> * nodo);
        NodoAvl<T>* rotacionIzquierda(NodoAvl<T> * nodo);
        void insert(T val);
        NodoAvl<T> * insertar(NodoAvl<T>* nodo, NodoAvl<T>* nodoNuevo);
        void erase(T val);
        NodoAvl<T> * eliminar(NodoAvl<T> *nodo, T val);
        NodoAvl<T> * minValue(NodoAvl<T> *nodo);
        bool buscar(T val);
        int factorDeBalance(NodoAvl<T> * nodo);
        bool preOrden();
        void posOrden(NodoAvl<T> * root);
        void inOrden();
        void inOrden(NodoAvl <T> *nodo);
        std::list<T> listaInOrden(NodoAvl<T> * root);
        void nivelOrden();
        void imprimirArbol(NodoAvl<T> * nodo, int espacio);



};

#include "ArbolAvl.hxx"



#endif
