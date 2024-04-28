#include "arbolB.h"

#pragma once

/**
 * @brief Clase árbol binario equilibrado
 * Representa un árbol binario equilibrado.
 */
template <class Key>
class ArbolBE : public ArbolB<Key> {
 public:
  ArbolBE();
  ~ArbolBE();

	bool buscar(const Key& dat) const;
	bool insertar(const Key&);
	bool insertarRama(NodoB<Key>**, const Key&);
	bool equilibrado() const;
	bool equilibrioRama(NodoB<Key>*) const;
	bool balanceado() const;
	bool balanceRama(NodoB<Key>*) const;
};

/**
 * @brief Constructor de la clase árbol binario equilibrado
 */
template <class Key>
ArbolBE<Key>::ArbolBE() : ArbolB<Key>() {}

/**
 * @brief Destructor de la clase árbol binario equilibrado
 */
template <class Key>
ArbolBE<Key>::~ArbolBE() {}

/**
 * @brief Función que busca un dato en el árbol
 * 
 * @tparam Key Dato a buscar
 * @param dat Dato a buscar
 * @return true Si el dato está en el árbol
 * @return false Si el dato no está en el árbol
 */
template <class Key>
bool ArbolBE<Key>::buscar(const Key& dat) const { 
	std::vector<Key> datos;
	this->recorrerPreorden(this->getRaiz(), datos);
	for (const Key& dato : datos) if (dato == dat) return true;
	return false;
}

/**
 * @brief Función que inserta un dato en el árbol de forma equilibrada
 * 
 * @tparam Key Dato a insertar
 */
template <class Key>
bool ArbolBE<Key>::insertar(const Key& dat) {
	// Si el dato ya existe, no se inserta.
	if (buscar(dat)) return false;
	// Obtenemos un puntero a puntero hacia la raíz del árbol.
  return insertarRama(this->getRaizPtr(), dat); // Insertamos el nodo en el árbol.
}

/**
 * @brief Función que inserta un dato en una rama de forma equilibrada
 * 
 * @tparam Key Dato a insertar
 * @param nodo Nodo a procesar
 * @param dat Dato a insertar
 */
template <class Key>
bool ArbolBE<Key>::insertarRama(NodoB<Key>** nodo, const Key& dat) {
	// Si el nodo es nullptr, insertamos el nodo en la rama.
	if (*nodo == nullptr) {
    *nodo = new NodoB<Key>(dat);
		std::cout << *this;
    return true;
  } else {
		if (this->getAlturaNodo((*nodo)->getIzdo()) <= this->getAlturaNodo((*nodo)->getDcho())) return insertarRama((*nodo)->getIzdoPtr(), dat);
		else return insertarRama((*nodo)->getDchoPtr(), dat);
  }
	return false;
}

/**
 * @brief Función que comprueba si un árbol está equilibrado
 * 
 * @tparam Key Dato a procesar
 * @return true Si el árbol está equilibrado
 * @return false Si el árbol no está equilibrado
 */
template <class Key>
bool ArbolBE<Key>::equilibrado() const { return equilibrioRama(this->getRaiz()); }

/**
 * @brief Función que comprueba si una rama de un árbol está equilibrada
 * 
 * @tparam Key Dato a procesar
 * @param nodo Nodo a procesar
 * @return true Si la rama está equilibrada
 * @return false Si la rama no está equilibrada
 */
template <class Key>
bool ArbolBE<Key>::equilibrioRama(NodoB<Key>* nodo) const {
	// Si el nodo es nullptr, la rama está equilibrada.
	if (nodo == nullptr) return true;
	// Calculamos el equilibrio de la rama.
	int eq = getTamanoRama(nodo->getIzdo()) - getTamanoRama(nodo->getDcho());
	// Comprobamos si el equilibrio es -1, 0 o 1.
	switch (eq) {
		case -1:
		case 0:
		case 1:
			// Si el equilibrio es -1, 0 o 1, la rama está equilibrada. Llamamos a la función recursivamente para comprobar el resto de la rama.
			return equilibrioRama(nodo->getIzdo()) && equilibrioRama(nodo->getDcho());
		default: return false;
	}
}

/**
 * @brief Función que comprueba si un árbol está balanceado
 * 
 * @tparam Key Dato a procesar
 * @return true Si el árbol está balanceado
 * @return false Si el árbol no está balanceado
 */
template <class Key>
bool ArbolBE<Key>::balanceado() const { return balanceRama(this->getRaiz()); }

/**
 * @brief Función que comprueba si una rama de un árbol está balanceada
 * 
 * @tparam Key Dato a procesar
 * @param nodo Nodo a procesar
 * @return true Si la rama está balanceada
 * @return false Si la rama no está balanceada
 */
template <class Key>
bool ArbolBE<Key>::balanceRama(NodoB<Key>* nodo) const {
	// Si el nodo es nullptr, la rama está balanceada.
	if (nodo == nullptr) return true;
	// Calculamos el balance de la rama.
	int bal = getAlturaNodo(nodo->getIzdo()) - getAlturaNodo(nodo->getDcho());
	// Comprobamos si el balance es -1, 0 o 1.
	switch (bal) {
		case -1:
		case 0:
		case 1:
			// Si el balance es -1, 0 o 1, la rama está balanceada. Llamamos a la función recursivamente para comprobar el resto de la rama.
			return balanceRama(nodo->getIzdo()) && balanceRama(nodo->getDcho());
		default: return false;
	}
}