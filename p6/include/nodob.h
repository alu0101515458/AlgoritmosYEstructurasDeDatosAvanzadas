#pragma once

/**
 * @brief Clase nodoB
 * Representa un nodo de un árbol binario.
 */
template <class Key>
class NodoB { 
 public:
  NodoB(const Key& dat, NodoB<Key>* izq = nullptr, NodoB<Key>* der = nullptr);

  const Key& getDato() const;
  NodoB<Key>* getIzdo() const;
  NodoB<Key>* getDcho() const;
  NodoB<Key>** getIzdoPtr();
  NodoB<Key>** getDchoPtr();

  void SetIzdo(NodoB<Key>*);
  void SetDcho(NodoB<Key>*);

 protected:
  Key dato;
  NodoB<Key>* izdo;
  NodoB<Key>* dcho;
};

/**
 * @brief Constructor de la clase nodoB
 * @param dat Dato del nodo
 * @param izq Puntero al hijo izquierdo
 * @param der Puntero al hijo derecho
 */
template <class Key>
NodoB<Key>::NodoB(const Key& dat, NodoB* izq, NodoB* der) : dato(dat), izdo(izq), dcho(der) {}

/**
 * @brief Método que devuelve el dato del nodo
 * @return Dato del nodo
 */
template <class Key>
const Key& NodoB<Key>::getDato() const { return dato; }

/**
 * @brief Método que devuelve el hijo izquierdo del nodo
 * @return Puntero al hijo izquierdo
 */
template <class Key>
NodoB<Key>* NodoB<Key>::getIzdo() const { return izdo; }

/**
 * @brief Método que devuelve el hijo derecho del nodo
 * @return Puntero al hijo derecho
 */
template <class Key>
NodoB<Key>* NodoB<Key>::getDcho() const { return dcho; }

/**
 * @brief Método que devuelve el puntero al hijo izquierdo del nodo
 * @return Puntero al hijo izquierdo
 */
template <class Key>
NodoB<Key>** NodoB<Key>::getIzdoPtr() { return &izdo; }

/**
 * @brief Método que devuelve el puntero al hijo derecho del nodo
 * @return Puntero al hijo derecho
 */
template <class Key>
NodoB<Key>** NodoB<Key>::getDchoPtr() { return &dcho; }

/**
 * @brief Método que modifica el hijo izquierdo del nodo
 * @param izq Nuevo hijo izquierdo
 */
template <class Key>
void NodoB<Key>::SetIzdo(NodoB<Key>* izq) { izdo = izq; }

/**
 * @brief Método que modifica el hijo derecho del nodo
 * @param der Nuevo hijo derecho
 */
template <class Key>
void NodoB<Key>::SetDcho(NodoB<Key>* der) { dcho = der; }