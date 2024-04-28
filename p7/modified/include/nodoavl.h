#include <iostream>
#include "nodob.h"

#pragma once

/**
 * @brief Clase nodo AVL
 * Representa un nodo AVL.
 */
template <class Key>
class NodoAVL : public NodoB<Key> {
 public:
  NodoAVL(Key dat, Key cl, NodoAVL<Key>* iz = nullptr, NodoAVL<Key>* de = nullptr);

  Key getClave() const;
  int getBal() const;
  NodoAVL<Key>* getIzdo();
  NodoAVL<Key>* getDcho();
  NodoAVL<Key>** getIzdoPtr();
  NodoAVL<Key>** getDchoPtr();

  void setClave(int cl);
  void setBal(int bal);
  void setIzdo(NodoAVL<Key>* izdo);
  void setDcho(NodoAVL<Key>* dcho);

 private:
  Key clave_;
  int bal_;
};

/**
 * @brief Constructor de la clase nodo AVL
 */
template <class Key>
NodoAVL<Key>::NodoAVL(Key dat, Key cl, NodoAVL<Key>* iz, NodoAVL<Key>* de)
  : NodoB<Key>(dat, iz, de), clave_(cl), bal_(0) {}

/**
 * @brief Función que devuelve la clave del nodo
 * 
 * @tparam Key 
 * @return int 
 */
template <class Key>
Key NodoAVL<Key>::getClave() const { return clave_; }

/**
 * @brief Función que devuelve el balance del nodo
 * 
 * @tparam Key 
 * @return int 
 */
template <class Key>
int NodoAVL<Key>::getBal() const { return bal_; }

/**
 * @brief Función que establece la clave del nodo
 * 
 * @tparam Key 
 * @param cl 
 */
template <class Key>
void NodoAVL<Key>::setClave(int cl) { clave_ = cl; }

/**
 * @brief Función que establece el balance del nodo
 * 
 * @tparam Key 
 * @param bal 
 */
template <class Key>
void NodoAVL<Key>::setBal(int bal) { bal_ = bal; }

/**
 * @brief Función que devuelve el hijo izquierdo del nodo
 * 
 * @tparam Key 
 * @return NodoAVL<Key>* 
 */
template <class Key>
NodoAVL<Key>* NodoAVL<Key>::getIzdo() { return static_cast<NodoAVL<Key>*>(NodoB<Key>::getIzdo()); }

/**
 * @brief Función que devuelve el hijo derecho del nodo
 * 
 * @tparam Key 
 * @return NodoAVL<Key>* 
 */
template <class Key>
NodoAVL<Key>* NodoAVL<Key>::getDcho() { return static_cast<NodoAVL<Key>*>(NodoB<Key>::getDcho()); }

/**
 * @brief Función que devuelve el puntero al hijo izquierdo del nodo
 * 
 * @tparam Key 
 * @return NodoAVL<Key>** 
 */
template <class Key>
NodoAVL<Key>** NodoAVL<Key>::getIzdoPtr() { return reinterpret_cast<NodoAVL<Key>**>(NodoB<Key>::getIzdoPtr()); }

/**
 * @brief Función que devuelve el puntero al hijo derecho del nodo
 * 
 * @tparam Key 
 * @return NodoAVL<Key>** 
 */
template <class Key>
NodoAVL<Key>** NodoAVL<Key>::getDchoPtr() { return reinterpret_cast<NodoAVL<Key>**>(NodoB<Key>::getDchoPtr()); }

/**
 * @brief Función que establece el hijo izquierdo del nodo
 * 
 * @tparam Key 
 * @param iz 
 */
template <class Key>
void NodoAVL<Key>::setIzdo(NodoAVL<Key>* iz) {
  this->NodoB<Key>::SetIzdo(static_cast<NodoB<Key>*>(iz));
}

/**
 * @brief Función que establece el hijo derecho del nodo
 * 
 * @tparam Key 
 * @param de 
 */
template <class Key>
void NodoAVL<Key>::setDcho(NodoAVL<Key>* de) {
  this->NodoB<Key>::SetDcho(static_cast<NodoB<Key>*>(de));
}