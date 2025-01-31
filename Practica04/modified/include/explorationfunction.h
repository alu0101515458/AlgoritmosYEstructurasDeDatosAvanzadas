#include "dispersionfunction.h"
#pragma once

/**
 * @brief Clase abstracta que representa una función de exploración.
 * 
 * @tparam Key. Tipo de dato de la clave.
 */
template<class Key>
class ExplorationFunction {
 public:
  virtual unsigned operator()(const Key&, unsigned) const = 0;
};

/**
 * @brief Clase que representa una función de exploración Lineal. g(k, i) = i
 * 
 * @tparam Key. Tipo de dato de la clave.
 */
template<class Key>
class LinearExploration : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key&, unsigned) const override;
};

/**
 * @brief Función de exploración Lineal. g(k, i) = i
 * 
 * @tparam Key 
 * @param key 
 * @param i 
 * @return unsigned 
 */
template<class Key>
unsigned LinearExploration<Key>::operator()(const Key&, unsigned i) const {
  // Aplicamos la función de exploración
  return i;
}

/**
 * @brief Clase que representa una función de exploración Cuadrática. g(k, i) = i^2
 * 
 * @tparam Key. Tipo de dato de la clave.
 */
template<class Key>
class QuadraticExploration : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key&, unsigned) const override;
};

/**
 * @brief Función de exploración Cuadrática. g(k, i) = i^2
 * 
 * @tparam Key 
 * @param key 
 * @param i 
 * @return unsigned 
 */
template<class Key>
unsigned QuadraticExploration<Key>::operator()(const Key&, unsigned i) const {
  // Aplicamos la función de exploración
  return (i * i);
}

/**
 * @brief Clase que representa una función de exploración Doble Hashing. g(k, i) = i * secondHash(key)
 * 
 * @tparam Key. Tipo de dato de la clave.
 */
template<class Key>
class DoubleHashing : public ExplorationFunction<Key> {
 public:
  DoubleHashing(DispersionFunction<Key>*);

  unsigned operator()(const Key&, unsigned) const override;

 private:
  DispersionFunction<Key>* fd_; // Segunda función de dispersión
};

/**
 * @brief Constructor de la clase DoubleHashing.
 * 
 * @tparam Key 
 * @param hashFunction 
 */
template<class Key>
DoubleHashing<Key>::DoubleHashing(DispersionFunction<Key>* hashFunction) {
  fd_ = hashFunction;
}

/**
 * @brief Función de exploración Doble Hashing. g(k, i) = i * secondHash(key)
 * 
 * @tparam Key 
 * @param key 
 * @param i 
 * @return unsigned 
 */
template<class Key>
unsigned DoubleHashing<Key>::operator()(const Key& key, unsigned i) const {
  // Aplicamos la segunda función de dispersión al key para obtener el nuevo valor de dispersión.
  return i * (*fd_)(key);
}

/**
 * @brief Clase que representa una función de exploración Rehashing. g(k, i) = i * secondHash(key)
 * 
 * @tparam Key. Tipo de dato de la clave.
 */
template<class Key>
class Rehashing : public ExplorationFunction<Key> {
 public:
  Rehashing(const unsigned& size);
  unsigned operator()(const Key&, unsigned) const override;
 private:
  unsigned tableSize_;
};

/**
 * @brief Constructor de la clase Rehashing.
 * 
 * @tparam Key 
 * @param size 
 */
template<class Key>
Rehashing<Key>::Rehashing(const unsigned& size) {
  tableSize_ = size;
}

/**
 * @brief Función de exploración Rehashing. g(k, i) = hashFunction^i(k)
 * 
 * @tparam Key 
 * @param key 
 * @param i 
 * @return unsigned 
 */
template<class Key>
unsigned Rehashing<Key>::operator()(const Key& key, unsigned i) const {
  // Usamos la clave como semilla para la función pseudoaleatoria
  srand(key);
  unsigned result = 0;
  for (unsigned j = 0; j <= i; ++j) {
    result = rand(); // Generamos un nuevo valor en cada iteración
  }
  return 1 + (result % (tableSize_ - 1));
}
