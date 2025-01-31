#include "nodoB.h"
#include <iostream>
#include <ostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#define BOLD "\033[1m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"

#pragma once

/**
 * @brief Clase arbolB
 * Representa un árbol binario.
 */
template <class Key>
class ArbolB {
 public: 
  ArbolB();
  ArbolB(const NodoB<Key>*);
	ArbolB(const std::vector<Key>&);
  ~ArbolB();

	void podar(NodoB<Key>*);
	bool esVacio(const NodoB<Key>*) const;
	bool esHoja(const NodoB<Key>*) const;
	bool insertarHoja(const Key&);
	bool insertarHojaRama(NodoB<Key>*&, const Key&);
	bool insertarRaiz(const Key&);

  void recorrerInorden(const NodoB<Key>*) const;
  void recorrerPreorden(const NodoB<Key>*, std::vector<Key>&) const;
  void recorrerPostorden(const NodoB<Key>*) const;
	std::ostream& recorrerNiveles(NodoB<Key>*, std::ostream& os) const;

	NodoB<Key>* getRaiz() const;
	NodoB<Key>** getRaizPtr(); 
	int getTamano() const;
	int getTamanoRama(NodoB<Key>*) const;
	int getAltura() const;
	int getAlturaNodo(NodoB<Key>*) const;

	void setRaiz(NodoB<Key>*);

 private:
  NodoB<Key>* nodo;
};

/**
 * @brief Constructor de la clase arbolB vacío
 */
template <class Key>
ArbolB<Key>::ArbolB() : nodo(nullptr) {}

/**
 * @brief Constructor de la clase arbolB equilibrado
 * 
 * @tparam Key Dato a insertar
 * @param nodo Nodo a insertar
 */
template <class Key>
ArbolB<Key>::ArbolB(const NodoB<Key>* nodo_raiz) : nodo(nodo_raiz) {}

/**
 * @brief Constructor de la clase arbolB equilibrado
 * 
 * @tparam Key Dato a insertar
 * @param datos Vector de datos a insertar
 */
template <class Key>
ArbolB<Key>::ArbolB(const std::vector<Key>& datos) : nodo(nullptr) {
	for (const Key& dat : datos) insertar(dat);
}

/**
 * @brief Destructor de la clase arbolB
 */
template <class Key>
ArbolB<Key>::~ArbolB() { podar(nodo); }

/**
 * @brief Función que poda un árbol
 * 
 * @tparam Key Dato a procesar
 * @param nodo Nodo a podar
 */
template <class Key>
void ArbolB<Key>::podar(NodoB<Key>* nodo) {
	// Si el nodo es nullptr, no se poda.
	if (nodo == nullptr) return;
	// Poda de los nodos hijos.
	if (nodo->getIzdo() != nullptr) podar(nodo->getIzdo());
	if (nodo->getDcho() != nullptr) podar(nodo->getDcho());
	// Poda del nodo actual.
	delete nodo;
	nodo = nullptr;
}

/**
 * @brief Función que comprueba si un árbol está vacío
 * 
 * @tparam Key Dato a procesar
 * @return true Si el árbol está vacío
 * @return false Si el árbol no está vacío
 */
template <class Key>
bool ArbolB<Key>::esVacio(const NodoB<Key>* nodo) const { return nodo == nullptr; }

/**
 * @brief Función que comprueba si un árbol es una hoja
 * 
 * @tparam Key Dato a procesar
 * @return true Si el árbol es una hoja
 * @return false Si el árbol no es una hoja
 */
template <class Key>
bool ArbolB<Key>::esHoja(const NodoB<Key>* nodo) const { return nodo != nullptr && nodo->getIzdo() == nullptr && nodo->getDcho() == nullptr; }



/**
 * @brief Función que inserta un dato en el árbol de forma balanceada
 * 
 * @tparam Key Dato a insertar
 */
template <class Key>
bool ArbolB<Key>::insertarHoja(const Key& dat) {
	// Si el dato ya existe, no se inserta.
	if (buscar(dat)) return false;
	// Si el árbol está vacío, insertamos el nodo en la raíz.
	if (nodo == nullptr) {
		nodo = new NodoB<Key>(dat);
		return true;
	} else insertarHojaRama(nodo, dat); // Insertamos el nodo en una rama.
}

/**
 * @brief Función que inserta un dato en una rama de forma balanceada
 * 
 * @tparam Key Dato a insertar
 * @param nodo Nodo a procesar
 * @param dat Dato a insertar
 */
template <class Key>
bool ArbolB<Key>::insertarHojaRama(NodoB<Key>*& nodo, const Key& dat) {
	// Si el nodo izquierdo es nullptr, insertamos el nodo a la izquierda.
	if (nodo->getIzdo() == nullptr) {
		nodo->izdo = new NodoB<Key>(dat);
		return true;
	}
	// Si el nodo derecho es nullptr, insertamos el nodo a la derecha.
	else if (nodo->getDcho() == nullptr) {
		nodo->dcho = new NodoB<Key>(dat);
		return true;
	}
	// Si el tamaño de la rama izquierda es menor o igual que el de la derecha, insertamos a la izquierda.
	else if (getTamanoRama(nodo->getIzdo()) <= getTamanoRama(nodo->getDcho())) insertarHojaRama(nodo->getIzdo(), dat);
	// Si el tamaño de la rama derecha es mayor que el de la izquierda, insertamos a la derecha.
	else insertarHojaRama(nodo->getDcho(), dat);
}

/**
 * @brief Función que inserta un dato en el árbol de forma balanceada
 * 
 * @tparam Key Dato a insertar
 */
template <class Key>
bool ArbolB<Key>::insertarRaiz(const Key& dat) {
	// Si el dato ya existe, no se inserta.
	if (buscar(dat)) return false;
	// Si el árbol está vacío, insertamos el nodo en la raíz.
	if (nodo == nullptr) {
		nodo = new NodoB<Key>(dat);
		return true;
	}	else { 
		// Creamos un nuevo nodo con el dato a insertar.
		NodoB<Key>* nuevo = new NodoB<Key>(dat);
		// Si el tamaño de la rama izquierda es menor o igual que el de la derecha, insertamos a la izquierda.
		if (getTamanoRama(nodo->getIzdo()) <= getTamanoRama(nodo->getDcho())) {
			nuevo->izdo = nodo->getIzdo();
			nodo->izdo = nuevo;
		} else {
			nuevo->dcho = nodo->getDcho();
			nodo->dcho = nuevo;
		}
		return true;
	}
}

/**
 * @brief Función que recorre el árbol en inorden
 * 
 * @tparam Key Dato a procesar
 * @param nodo Nodo a procesar
 */
template <class Key>
void ArbolB<Key>::recorrerInorden(const NodoB<Key>* nodo) const {
	// Si el nodo es nullptr, no se recorre.
  if (nodo == nullptr) return;
	// Recorremos el árbol en inorden de forma recursiva (izquierda, raíz, derecha).
  recorrerInorden(nodo->getIzdo());
  std::cout << nodo->getDato() << " ";
  recorrerInorden(nodo->getDcho());
}

/**
 * @brief Función que recorre el árbol en preorden
 * 
 * @tparam Key Dato a procesar
 * @param nodo Nodo a procesar
 */
template <class Key>
void ArbolB<Key>::recorrerPreorden(const NodoB<Key>* nodo, std::vector<Key>& aux) const {
	// Si el nodo es nullptr, no se recorre.
  if (nodo == nullptr) return;
	// Recorremos el árbol en preorden de forma recursiva (raíz, izquierda, derecha).
	aux.push_back(nodo->getDato());
  recorrerPreorden(nodo->getIzdo(), aux);
  recorrerPreorden(nodo->getDcho(), aux);
}

/**
 * @brief Función que recorre el árbol en postorden
 * 
 * @tparam Key Dato a procesar
 * @param nodo Nodo a procesar
 */
template <class Key>
void ArbolB<Key>::recorrerPostorden(const NodoB<Key>* nodo) const {
	// Si el nodo es nullptr, no se recorre.
	if (nodo == nullptr) return;  
	// Recorremos el árbol en postorden de forma recursiva (izquierda, derecha, raíz).
	recorrerPostorden(nodo->getIzdo());
	recorrerPostorden(nodo->getDcho());
	std::cout << nodo->getDato() << " ";
}

/**
 * @brief Función que recorre el árbol por niveles
 * 
 * @tparam Key Dato a procesar
 * @param nodo Nodo a procesar
 * @param os Stream de salida
 */
template <class Key>
std::ostream& ArbolB<Key>::recorrerNiveles(NodoB<Key>* nodo, std::ostream& os) const {
	// Manejo explícito del árbol vacío.
	if (nodo == nullptr) {
    os << "Nivel " << BOLD << MAGENTA << "0" << RESET << ": [.] " << std::endl;
		return os;
  } 

	// Usamos una cola para recorrer los nodos por niveles.
	std::queue<std::pair<NodoB<Key>*, int>> Q;
	int nivelActual = 0;

	os << "Nivel " << BOLD << MAGENTA << nivelActual << RESET << ": ";

	// Insertamos la raíz del árbol en la cola con nivel 0.
	Q.push({nodo, 0});

	// Mientras la cola no esté vacía, procesamos los nodos.
	while (!Q.empty()) {
		// Extraemos y eliminamos el nodo de la cola.
		std::pair<NodoB<Key>*, int> nodoInfo = Q.front();
		Q.pop();

		// Extraemos el nodo y el nivel del nodo.
		NodoB<Key>* nodo_aux = nodoInfo.first;
		int nivel = nodoInfo.second;

		// Si estamos en un nuevo nivel, actualizamos nivelActual.
		if (nivel > nivelActual) {
			os << "\nNivel " << BOLD << MAGENTA << nivel << RESET << ": ";
			nivelActual = nivel;
		}

		// Si el nodo no es nullptr, lo procesamos.
		if (nodo_aux != nullptr) {
			os << nodo_aux->getDato() << " ";
			// Insertar hijo izquierdo y derecho en la cola, incluso si son nullptr.
			Q.push({nodo_aux->getIzdo(), nivel + 1});
			Q.push({nodo_aux->getDcho(), nivel + 1});
		} else {
			os << "[.] ";
		}
	}
	os << std::endl;
	return os;
}

/**
 * @brief Función que devuelve la raíz del árbol
 * 
 * @tparam Key Dato a procesar
 * @return NodoB<Key>* Raíz del árbol
 */
template <class Key>
NodoB<Key>* ArbolB<Key>::getRaiz() const { return nodo; }

/**
 * @brief Función que devuelve un puntero a la raíz del árbol
 * 
 * @tparam Key Dato a procesar
 * @return NodoB<Key>** Puntero a la raíz del árbol
 */
template <class Key>
NodoB<Key>** ArbolB<Key>::getRaizPtr() { return &nodo; }

/**
 * @brief Función que devuelve el tamaño del árbol
 * 
 * @tparam Key Dato a procesar
 * @return const int Tamaño del árbol
 */
template <class Key>
int ArbolB<Key>::getTamano() const { return getTamanoRama(nodo); }

/**
 * @brief Función que devuelve el tamaño de una rama del árbol
 * De forma recursiva, calcula el tamaño de una rama del árbol, es decir, el número de nodos que contiene la rama.
 * @tparam Key Dato a procesar
 * @param nodo Nodo a procesar
 * @return const int Tamaño de la rama
 */
template <class Key>
int ArbolB<Key>::getTamanoRama(NodoB<Key>* nodo) const {
	if (nodo == nullptr) return 0;
	return (1 + getTamanoRama(nodo->getIzdo()) + getTamanoRama(nodo->getDcho()));
}

/**
 * @brief Función que devuelve la altura del árbol
 * 
 * @tparam Key Dato a procesar
 * @return const int Altura del árbol
 */
template <class Key>
int ArbolB<Key>::getAltura() const { return getAlturaNodo(nodo); }

/**
 * @brief Función que devuelve la altura de un nodo del árbol
 * De forma recursiva, calcula la altura de un nodo del árbol, es decir, la longitud del camino más largo desde el nodo hasta una hoja.
 * @tparam Key Dato a procesar
 * @param nodo Nodo a procesar
 * @return const int Altura del nodo
 */
template <class Key>
int ArbolB<Key>::getAlturaNodo(NodoB<Key>* nodo) const {
	// Si el nodo es nullptr, la altura es 0.
	if (nodo == nullptr) return 0;
	// Calculamos la altura del nodo.
	int alturaIzq = getAlturaNodo(nodo->getIzdo());
	int alturaDcha = getAlturaNodo(nodo->getDcho());
	// Devolvemos la altura del nodo.
	return (alturaIzq > alturaDcha) ? alturaIzq + 1 : alturaDcha + 1;
}

/**
 * @brief Función que establece la raíz del árbol
 * 
 * @tparam Key Dato a procesar
 * @param nodo Raíz del árbol
 */
template <class Key>
void ArbolB<Key>::setRaiz(NodoB<Key>* nodo) { this->nodo = nodo; }

/**
 * @brief Sobrecarga del operador de inserción
 * 
 * @tparam Key Dato a procesar
 * @param os Stream de salida
 * @param arbol Árbol a procesar
 * @return std::ostream& Stream de salida
 */
template <class Key>
std::ostream& operator<<(std::ostream& os, const ArbolB<Key>& arbol) {
	// Recorremos el árbol por niveles.
	std::cout << std::endl;
	return arbol.recorrerNiveles(arbol.getRaiz(), os);
}