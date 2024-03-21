#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include <list>
#include <set>
// TODO #1: incluir cabecera arbol AV
#include "ArbolAvl.h"

// -------------------------------------------------------------------------
typedef std::list< std::string > TList;
typedef std::set< std::string >  TSet;
// TODO #2: definir arbol AVL de tipo std::string
 typedef ArbolAvl< std::string > TAVL;

// -------------------------------------------------------------------------
template< class TArbol >
bool LeerArbol( TArbol& arbol, const std::string& nomArch );
template <class T> 
bool leerAvl(ArbolAvl<T> elArbol, const std::string& nomArch);
bool leerHeap(std::vector<int> heap, char* argv[]);
// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  if( argc < 2 )
  {
    std::cerr << "Uso: " << argv[ 0 ] << " archivo_entrada" << std::endl;
    return( -1 );

  } // fi

  //Heap
  // Crear un vector vacío para almacenar los datos del archivo
  std::vector<TSet> datosHeap;
  // Llenar el montículo y calcular el tiempo empleado  
 

  // Crea un vector para almacenar los elementos del heap
  std::vector<int> heap;
  std::clock_t inicioLecturaHeap = std::clock( );
  bool elHeap = leerHeap(heap, argv);

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
  

  // Obtener el recorrido en inorden del arbol AVL
  TList inordenAVL;
  // TODO #6: llamar funcion que genera el recorrido en inorden
  miArbolAVL.listaInOrden( miArbolAVL.raiz,inordenAVL );
  std::cout << "Tam avl" << inordenAVL.size() << "Tam rn" << miArbolRN.size() << std::endl;
  if( inordenAVL.size( ) != miArbolRN.size( ) )
  {
    std::cout << "Cantidad de elementos en los arboles no coinciden." << std::endl;
    return( -1 );

  } // fi

  // Comparar los arboles
  TSet::const_iterator rnIt = miArbolRN.begin( );
  TList::const_iterator avlIt = inordenAVL.begin( );
  bool iguales = true;
  for( ; rnIt != miArbolRN.end( ); rnIt++, avlIt++ )
    iguales &= ( *rnIt == *avlIt );

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
  entrada.close( );
  return( true );
}


bool leerHeap(std::vector<int> heap, char* argv[]) {
   
  std::ifstream archivo(argv[1]);
  std::string linea;

  if (archivo.is_open()) {

      while (std::getline(archivo, linea)) {
          std::istringstream ss(linea);
          std::string operacion;
          int valor;

          // Lee la operación y el valor del nodo de la línea
          ss >> operacion >> valor;

          // Inserta o elimina el valor del nodo en el vector según la operación
          if (operacion == "add") {
              heap.push_back(valor);
              std::push_heap(heap.begin(), heap.end(), std::greater<int>());
          } else if (operacion == "del") {
              // Busca el valor en el vector y lo elimina
              std::vector<int>::iterator it = std::find(heap.begin(), heap.end(), valor);
              if (it != heap.end()) {
                  std::iter_swap(it, heap.end() - 1);
                  heap.pop_back();
                  std::make_heap(heap.begin(), heap.end(), std::greater<int>());
              }
          }
      }
      std::clock_t finLecturaHeap = std::clock( );
      archivo.close();

      // Imprime los elementos del heap (en orden ascendente)
      std::cout << "Elementos del heap:" << std::endl;
      for (std::vector<int>::iterator it = heap.begin(); it != heap.end(); ++it) {
          std::cout << *it << std::endl;
      }
  } 
  else {

      std::cerr << "No se pudo abrir el archivo." << std::endl;
      std::clock_t finLecturaHeap = std::clock( );
  }

  return( true );
}
// eof - taller_3_ordenamiento_busqueda.cxx
