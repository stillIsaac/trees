#include "ArbolAvl.h"
#include <queue>
#include <list>
#include "NodoAvl.h"
#define SPACE 10
template < class T >
ArbolAvl<T>::ArbolAvl() {

    this->raiz = NULL;
}



template < class T >
int ArbolAvl<T>::altura(NodoAvl<T> *nodo) {

    if(nodo == NULL) {

        return -1;
    }

    else {
        
        int lheight = altura(nodo->hijoIzq);
        int rheight = altura(nodo->hijoDer);

        if(lheight > rheight) {

            return (lheight + 1);
        }

        else {

            return (rheight+1);
        }
    }
}



template < class T > 
bool ArbolAvl<T>::esVacio() {

    return this->raiz == NULL;
}





template < class T >
bool ArbolAvl<T>::buscar(T val) {

    NodoAvl<T> * nodo = this->raiz;
    bool encontrado = false;
 //   std::cout << "buscanding" << std::endl;
    while(nodo != NULL && !encontrado) {

        if(val < nodo->dato) {

            nodo = nodo->hijoIzq;
        }

         else if( val > nodo->dato) {

                nodo = nodo->hijoDer;
        }

        else {

            encontrado = true;
        }
    }
 //   std::cout << "valor encontrado: " << encontrado << std::endl;
    return encontrado;
}


template < class T >
NodoAvl<T> * ArbolAvl<T>::minValue(NodoAvl<T> *nodo) {
    NodoAvl<T> * current = nodo;
    while(current->hijoIzq != NULL) {

        current = current->hijoIzq;
    }

    return current;
}


template < class T >
void ArbolAvl<T>::nivelOrden() {

    if(!this->esVacio()) {

        std::queue < NodoAvl<T> *> cola;
        cola.push(this->raiz);
        NodoAvl<T>*nodo;

        while(!cola.empty()) {

            nodo = cola.front();
            cola.pop();
            std::cout << nodo->dato << " ";

            if(nodo->hijoIzq() != NULL) {

                cola.push(nodo->hijoIzq);
            }

            if(nodo->hijoder != NULL) {

                cola.push(nodo->hijoDer);
            }
        }
    }

}


template < class T >
int ArbolAvl<T>::factorDeBalance(NodoAvl<T> * nodo) {

    if(nodo == NULL) {

        return -1;
    }
   // std::cout << "altura del nodo balance" << nodo->dato<<std::endl;
    //std::cout << "altura izq" << altura(nodo->hijoIzq) << "altura der" <<altura(nodo->hijoDer) << std::endl;
    return altura(nodo->hijoIzq) - altura(nodo->hijoDer); 
}


template < class T >
NodoAvl<T>* ArbolAvl<T>::rotacionDerecha(NodoAvl<T> * y) {
  //  std::cout << "rotar derecha" <<std::endl;
    NodoAvl<T> * x = y->hijoIzq;
    NodoAvl<T> * T2 = x->hijoDer;

    // Se hace la rotación
    x->hijoDer = y;
    y->hijoIzq = T2;

    return x;
}


template < class T >
NodoAvl<T>* ArbolAvl<T>::rotacionIzquierda(NodoAvl<T> * x) {
 //   std::cout << "rotar izquierda" <<std::endl;
    NodoAvl<T> * y = x->hijoDer;
    NodoAvl<T> * T2 = y->hijoIzq;
    //std::cout << "valor y rotacion izquierda: " << std::endl;
    // Se hace la rotación
    y->hijoIzq = x;
    x->hijoDer = T2;

    return y;

}

template < class T >
void ArbolAvl<T>::insertar(T val)  {

    if(this->esVacio()) {

        NodoAvl<T> * nodo = new NodoAvl<T>;
        nodo->dato = val;
        this->raiz = nodo;
    }

    else {


        NodoAvl<T> * nodo = new NodoAvl<T>;
        nodo->dato = val;
        this->insertar(this->raiz, nodo);
    }
}


template < class T >
NodoAvl<T>* ArbolAvl<T>::insertar(NodoAvl<T>* nodo, NodoAvl<T>* nodoNuevo) {

    if(nodo == NULL) {

           nodo = nodoNuevo;
    //    std::cout << "Valor insertado: "  << nodo->dato<< std::endl;
        return nodo;
    }



    if(nodoNuevo->dato < nodo->dato) {
     //   std::cout << "es menor" << std::endl;
        nodo->hijoIzq = insertar(nodo->hijoIzq, nodoNuevo);
    }

    else if( nodoNuevo->dato > nodo->dato) {

        nodo->hijoDer = insertar(nodo->hijoDer, nodoNuevo);
    }

    else {

        return nodo;
    }



    int fb = this->factorDeBalance(nodo);


     // Izquierda Izquierda
    if(fb > 1 && (nodoNuevo->dato < (nodo->hijoIzq)->dato)) {
       // std::cout << "rota derecha con " << nodoNuevo->dato << (nodo->hijoIzq)->dato;
        return this->rotacionDerecha(nodo);
    }

    //Derecha Derecha
    if(fb < -1 && (nodoNuevo->dato > (nodo->hijoDer)->dato)) {

        return this->rotacionIzquierda(nodo);
    }


    // Izquierda derecha
    if(fb  > 1 && (nodoNuevo->dato > (nodo->hijoIzq)->dato)) {

        nodo->hijoIzq = this->rotacionIzquierda(nodo->hijoIzq);
        return this->rotacionDerecha(nodo);
    }

    // Derecha Izquierda
    if(fb < -1 && (nodoNuevo->dato < (nodo->hijoDer)->dato )) {

        nodo->hijoDer = this->rotacionDerecha(nodo->hijoDer);
        return this->rotacionIzquierda(nodo); 
    }

    return nodo;

}


template < class T >
NodoAvl<T>* ArbolAvl<T>::eliminar(NodoAvl<T>* nodo, T val) {
    
 //   std::cout << "valor nodo a eliminar sdfsj: " << nodo->dato << std::endl;
    if(nodo == NULL) {

        return NULL;
    }

    if(!this->buscar(val)) {
        
   //     std::cout << "entra, no entiendo" << std::endl;
        return nodo;
    }

    else if( val < nodo->dato) {

      //  std::cout << "quiubo el valor es " << nodo->dato << std::endl;
        nodo->hijoIzq = eliminar(nodo->hijoIzq, val);
      //  std::cout << "Aqui se muere " << nodo->dato << std::endl;
    }

    else if (val > nodo->dato) {

        nodo->hijoDer = eliminar(nodo->hijoDer, val);
    }
    

    else {

        if(nodo->hijoIzq == NULL) {

            NodoAvl<T> * temp = nodo->hijoDer;
            delete nodo;
            return temp;
        }

        else if(nodo->hijoDer == NULL) { 

            NodoAvl<T> * temp = nodo->hijoIzq;
            delete nodo;
            return temp;
        }

        else {

            NodoAvl<T> * temp = minValue(nodo->hijoDer);
            nodo->dato = temp->dato;
            nodo->hijoDer = eliminar(nodo->hijoDer, temp->dato);
        }
    }


    int fb = this->factorDeBalance(nodo);

    //Izquierda izquierda desbalance o rotar a la derecha
  //  std::cout << "aqui todo bien con nodo" << nodo->dato << std::endl;
    if(fb == 2 && (this->factorDeBalance(nodo->hijoIzq) >= 0)) {

        return this->rotacionDerecha(nodo);
    }

    // Desbalance izquierda derecha o rotar izquierda
    else if(fb == 2 && (this->factorDeBalance(nodo->hijoIzq) == -1)) {

        nodo->hijoIzq = this->rotacionIzquierda(nodo->hijoIzq);
        return this->rotacionDerecha(nodo);
    }

    // Desbalance derecha derecha o rotacion izquierda
    else if(fb == -2 && (this->factorDeBalance(nodo->hijoDer) <= -0)) {
       // std::cout << "derecha derecha" << std::endl;
     //   std::cout << "valor nodo: " << nodo->dato <<std::endl;
        return this->rotacionIzquierda(nodo);
    }

    // Desbalance derecha izquierda o rotar derecha
    else if(fb == -2 && (this->factorDeBalance(nodo->hijoDer) == 1)) {

        nodo->hijoDer = this->rotacionDerecha(nodo->hijoDer);
        return this->rotacionIzquierda(nodo);
    }

    return nodo;
}

template <class T>
void ArbolAvl<T>::inOrden(NodoAvl<T> * root) {

    if(root == NULL) {

        return;
    }

    this->inOrden(root->hijoIzq);

    std::cout << root->dato << " ";

    this->inOrden(root->hijoDer);


}

template <class T>
void ArbolAvl<T>::imprimirArbol(NodoAvl<T> * nodo, int espacio){

    if(nodo == NULL){

        return;
    }

    espacio += SPACE;
    imprimirArbol(nodo->hijoDer, espacio);
    std::cout << std::endl;
    for(int i = SPACE; i < espacio; i++) {

        std::cout << " ";
    }
    std::cout << nodo->dato << "\n";
    imprimirArbol(nodo->hijoIzq, espacio);

}


template <class T>
void ArbolAvl<T>::listaInOrden(NodoAvl<T> * root, std::list<T> lista) {

    if(root == NULL) {

        return;
    }

    this->inOrden(root->hijoIzq);
    std::cout << "el dato: " << root->dato << std::endl;
    lista.push_back(root->dato);

    this->inOrden(root->hijoDer);


}
