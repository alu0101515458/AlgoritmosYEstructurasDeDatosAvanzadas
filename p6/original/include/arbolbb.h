#include <vector>
#include "arbolB.h"
#include "nodoB.h"

#pragma once

/**
 * @brief Clase árbol binario de búsqueda
 * Representa un árbol binario de búsqueda.
 */
template <class Key>
class ArbolBB {
 public:
  ArbolBB();
  ArbolBB(const ArbolB<Key>&);
	ArbolBB(const ArbolBB<Key>&);
	ArbolBB(const std::vector<Key>&);
  ~ArbolBB();

  bool insertar(const Key&);
	bool buscar(const Key&) const;

	ArbolB<Key>* getArbolB() const;
  
 private:
  ArbolB<Key>* arbolB;
};

/**
 * @brief Constructor de la clase árbol binario de búsqueda
 */
template <class Key>
ArbolBB<Key>::ArbolBB() : arbolB(new ArbolB<Key>()) {}

/**
 * @brief Constructor de copia de la clase árbol binario de búsqueda
 * @param arbol Árbol a copiar
 */
template <class Key>
ArbolBB<Key>::ArbolBB(const ArbolB<Key>& arbol) : arbolB(new ArbolB<Key>(arbol)) {}

/**
 * @brief Constructor de copia de la clase árbol binario de búsqueda
 * @param arbol Árbol a copiar
 */
template <class Key>
ArbolBB<Key>::ArbolBB(const ArbolBB<Key>& arbol) : arbolB(new ArbolB<Key>(*(arbol.arbolB))) {}

/**
 * @brief Constructor de la clase árbol binario de búsqueda
 * @param datos Vector de datos a insertar
 */
template <class Key>
ArbolBB<Key>::ArbolBB(const std::vector<Key>& datos) : arbolB(new ArbolB<Key>()) {
	for (const Key& dat : datos) insertar(dat);
}

/**
 * @brief Destructor de la clase árbol binario de búsqueda
 */
template <class Key>
ArbolBB<Key>::~ArbolBB() { delete arbolB; }

/**
 * @brief Método que inserta un dato en el árbol
 * @param dat Dato a insertar
 */
template <class Key>
bool ArbolBB<Key>::insertar(const Key& dat) { 
  // Verificar si el dato ya está en el árbol.
  if (buscar(dat)) return false;
	// Obtenemos un puntero al puntero de la raíz para poder modificar el árbol.
  NodoB<Key>** aux = arbolB->getRaizPtr();
	// Recorremos el árbol hasta encontrar la posición donde insertar el nuevo nodo.
  while (*aux != nullptr) {
		// Si el dato es menor que el dato del nodo actual, vamos a la izquierda.
    if (dat < (*aux)->getDato()) aux = (*aux)->getIzdoPtr();
		// Si no, vamos a la derecha.
    else aux = (*aux)->getDchoPtr();
  }
	// Insertar el nuevo nodo.
  *aux = new NodoB<Key>(dat); // Insertar el nuevo nodo.
  return true; // La inserción fue exitosa.
}

/**
 * @brief Método que busca un dato en el árbol
 * @param dat Dato a buscar
 */
template <class Key>
bool ArbolBB<Key>::buscar(const Key& dat) const { 
  if (arbolB->getRaiz() == nullptr) return false; // Si el árbol está vacío, retornamos false.
  NodoB<Key>* aux = arbolB->getRaiz(); // Empezamos en la raíz.
  while (aux != nullptr) {
    // Si el dato es igual al dato del nodo actual, retornamos true.
    if (dat == aux->getDato()) return true;
    // Si el dato es menor que el dato del nodo actual, vamos a la izquierda.
    if (dat < aux->getDato()) aux = aux->getIzdo();
    // Si no, vamos a la derecha.
    else aux = aux->getDcho();
  }
  return false; // El dato no está en el árbol.
}

/**
 * @brief Método que devuelve el árbol binario subyacente
 * @return Árbol binario subyacente
 */
template <class Key>
ArbolB<Key>* ArbolBB<Key>::getArbolB() const { return arbolB; }