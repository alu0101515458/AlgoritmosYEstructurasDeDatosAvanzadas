#include <vector>
#include "arbolB.h"
#include "nodoB.h"

#pragma once

/**
 * @brief Clase árbol binario de búsqueda
 * Representa un árbol binario de búsqueda.
 */
template <class Key>
class ArbolBB : public ArbolB<Key>{
 public:
  ArbolBB();
  ~ArbolBB();

  bool insertar(const Key&) override;
	bool buscar(const Key&) const override;
};

/**
 * @brief Constructor de la clase árbol binario de búsqueda
 */
template <class Key>
ArbolBB<Key>::ArbolBB() : ArbolB<Key>() {}

/**
 * @brief Destructor de la clase árbol binario de búsqueda
 */
template <class Key>
ArbolBB<Key>::~ArbolBB() {}

/**
 * @brief Método que inserta un dato en el árbol
 * @param dat Dato a insertar
 */
template <class Key>
bool ArbolBB<Key>::insertar(const Key& dat) { 
  // Verificar si el dato ya está en el árbol.
  if (buscar(dat)) return false;
	// Obtenemos un puntero al puntero de la raíz para poder modificar el árbol.
  NodoB<Key>** aux = this->getRaizPtr();
	// Recorremos el árbol hasta encontrar la posición donde insertar el nuevo nodo.
  while (*aux != nullptr) {
		// Si el dato es menor que el dato del nodo actual, vamos a la izquierda.
    if (dat < (*aux)->getDato()) aux = (*aux)->getIzdoPtr();
		// Si no, vamos a la derecha.
    else aux = (*aux)->getDchoPtr();
  }
	// Insertar el nuevo nodo.
  *aux = new NodoB<Key>(dat); // Insertar el nuevo nodo.
  std::cout << *this; // Mostrar el árbol.
  return true; // La inserción fue exitosa.
}

/**
 * @brief Método que busca un dato en el árbol
 * @param dat Dato a buscar
 */
template <class Key>
bool ArbolBB<Key>::buscar(const Key& dat) const { 
  if (this->getRaiz() == nullptr) return false; // Si el árbol está vacío, retornamos false.
  NodoB<Key>* aux = this->getRaiz(); // Empezamos en la raíz.
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