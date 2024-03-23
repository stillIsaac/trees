#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <list>
#include <set>
#include <string>
// TODO #1: incluir cabecera arbol AV
#include "ArbolAvl.h"
#include "Heap.h"

// -------------------------------------------------------------------------
typedef std::list< std::string > TList;
typedef std::set< std::string >  TSet;
// TODO #2: definir arbol AVL de tipo std::string
 typedef ArbolAvl< std::string > TAVL;
 typedef Heap <int> THeap ;

// -------------------------------------------------------------------------
template< class TArbol >
bool LeerArbol( TArbol& arbol, const std::string& nomArch );
template <class T> 
bool leerAvl(ArbolAvl<T> elArbol, const std::string& nomArch);
bool leerHeap(std::vector<int> heap, char* argv[]);
std::list<std::string> listaInOrden(ArbolAvl<std::string> elArbol, const std::string& nomArch); 
// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  if( argc < 2 )
  {
    std::cerr << "Uso: " << argv[ 0 ] << " archivo_entrada" << std::endl;
    return( -1 );

  } // fi

  THeap heap;
  std::clock_t inicioLecturaHeap = std::clock( );
  bool elHeap = LeerArbol(heap, argv[ 1 ]);
    std::clock_t finLecturaHeap = std::clock( );
  // Declarar arboles a usar
  TSet miArbolRN; // arbol rojinegro
  // TODO #3: arbol AVL 
  TAVL miArbolAVL;

  // Llenar arbol rojinegro y calcular el tiempo empleado
  std::clock_t inicioLecturaRN = std::clock( );
  bool lecturaRN = LeerArbol( miArbolRN, argv[ 1 ] );
  std::clock_t finLecturaRN = std::clock( );
  double tiempoLecturaRN = ( finLecturaRN - inicioLecturaRN ) / double( CLOCKS_PER_SEC );
  if( lecturaRN )
    std::cout
      << "Tiempo de llenado arbol RN = "
      << tiempoLecturaRN << "segs."
      << std::endl;
  else
    std::cout
      << "Error al leer \"" << argv[ 1 ]
      << "\" para llenar el arbol RN."
      << std::endl;
  
  // Llenar arbol AVL y calcular el tiempo empleado
  std::clock_t inicioLecturaAVL = std::clock( );
  // TODO #4: usar el archivo para llenar el arbol AVL 
  bool lecturaAVL = leerAvl( miArbolAVL, argv[ 1 ] );
  std::clock_t finLecturaAVL = std::clock( );
  double tiempoLecturaAVL = ( finLecturaAVL - inicioLecturaAVL ) / double( CLOCKS_PER_SEC );
  // TODO #5: informar tiempo de llenado del arbol AVL
     if( lecturaAVL )
     std::cout
     << "Tiempo de llenado arbol AVL = "
     << tiempoLecturaAVL << "segs."
     << std::endl;
     else
     std::cout
     << "Error al leer \"" << argv[ 1 ]
     << "\" para llenar el arbol AVL."
     << std::endl;
  
  if(elHeap) {
    std::cout << "El tiempo de llenado del HEAP = " << (finLecturaHeap - inicioLecturaHeap)/double( CLOCKS_PER_SEC )  << "segs." << std::endl;
  }
  else {
    std::cout
     << "Error al leer \"" << argv[ 1 ]
     << "\" para llenar el arbol Heap."
     << std::endl;
  }
  // Obtener el recorrido en inorden del arbol AVL
  TList inordenAVL;
  // TODO #6: llamar funcion que genera el recorrido en inorden
  inordenAVL = listaInOrden(miArbolAVL, argv[ 1 ]);
  std::vector<int> inOrdenHeap = heap.getSort();
  
  if( (inordenAVL.size( ) != miArbolRN.size( )))
  {

    std::cout << "Cantidad de elementos en los arboles no coinciden." << std::endl;
    return( -1 );
  } 

  if( (inordenAVL.size( ) != inOrdenHeap.size())) 
  {

    std::cout << "Cantidad de elementos en los arboles no coinciden." << std::endl;
    return( -1 );
  } 

  // Comparar los arboles
  TSet::const_iterator rnIt = miArbolRN.begin( );
  TList::const_iterator avlIt = inordenAVL.begin( );
  std::vector<int>::iterator heapIt = inOrdenHeap.begin();
  bool iguales = true;
  for( ; rnIt != miArbolRN.end( ); rnIt++, avlIt++ )
    iguales &= ( *rnIt == *avlIt );

  for( ; rnIt != miArbolRN.end( ); rnIt++, heapIt++ )
    iguales &= ( stoi(*rnIt) == *heapIt );
  
  // Informar si los arboles coinciden o no
  std::cout << "Los arboles ";
  if( !iguales )
    std::cout << "no ";
  std::cout << "coinciden." << std::endl;
  
  return( 0 );
}

// -------------------------------------------------------------------------
template< class TArbol >
bool LeerArbol( TArbol& arbol, const std::string& nomArch )
{
  std::ifstream entrada( nomArch.c_str( ) );
  if( !entrada )
    return( false );
  while( !entrada.eof( ) )
  {
    std::string codigo, valor;
    entrada >> codigo >> valor;
    if( codigo == "add" )
      arbol.insert( valor );  // El arbol debe proveer el metodo "insert"
    else if( codigo == "del" )
      arbol.erase( valor );   // El arbol debo proveer el metodo "erase"

  } // elihw
  entrada.close( );
  return( true );
}



template <class T> 
bool leerAvl(ArbolAvl<T> elArbol, const std::string& nomArch) {

  std::ifstream entrada( nomArch.c_str( ) );
  if( !entrada )
    return( false );
  while( !entrada.eof( ) )
  {

    std::string codigo, valor;
    entrada >> codigo >> valor;
   // std::cout << "El valor: "<< valor << std::endl; 
    if( codigo == "add" ) {

      NodoAvl<T> *nodoNuevo = new NodoAvl<T>();
      nodoNuevo->dato = valor;
      elArbol.raiz = elArbol.insertar( elArbol.raiz, nodoNuevo);  // El arbol debe proveer el metodo "insert"
    }
    else if( codigo == "del" ) {
     // std::cout << "El valor2: "<< valor << std::endl; 
      elArbol.raiz =  elArbol.eliminar( elArbol.raiz, valor );   // El arbol debo proveer el metodo "erase"
    }

  } // elihw
  return( true );
}





std::list<std::string> listaInOrden(ArbolAvl<std::string> elArbol, const std::string& nomArch) {

  std::list<std::string> laLista;
  std::ifstream entrada( nomArch.c_str( ) );
  if( !entrada )
    return laLista;
  while( !entrada.eof( ) )
  {

    std::string codigo, valor;
    entrada >> codigo >> valor;
   // std::cout << "El valor: "<< valor << std::endl; 
    if( codigo == "add" ) {

      NodoAvl<std::string> *nodoNuevo = new NodoAvl<std::string>();
      nodoNuevo->dato = valor;
      elArbol.raiz = elArbol.insertar( elArbol.raiz, nodoNuevo);  // El arbol debe proveer el metodo "insert"
    }
    else if( codigo == "del" ) {
     // std::cout << "El valor2: "<< valor << std::endl; 
      elArbol.raiz =  elArbol.eliminar( elArbol.raiz, valor );   // El arbol debo proveer el metodo "erase"
    }

  } // elihw
  
 
  laLista = elArbol.listaInOrden(elArbol.raiz);
  entrada.close( );
  return laLista;
}


// eof - taller_3_ordenamiento_busqueda.cxx
