#include <vector>
#include <memory>
#include <ostream>
#include "../include/dispersionfunction.h"
#include "../include/explorationfunction.h"
#include "../include/sequence.h"

#pragma once

template<class Key, class Container = StaticSequence<Key>>
class HashTable {
 public:
  HashTable(unsigned tableSize, DispersionFunction<Key>* hashFunction, ExplorationFunction<Key>* explorationFunction, unsigned blockSize);
  HashTable(unsigned tableSize, DispersionFunction<Key>* hashFunction);

  bool search(const Key& key) const;
  bool insert(const Key& key);

 private:
  unsigned blockSize_; // Solo usado en dispersión cerrada
  unsigned tableSize_;
  // Se usa un puntero a la interfaz Sequence para poder usar tanto contenedores estáticos como dinámicos (StaticSequence y DynamicSequence)
  // En el caso de dispersión cerrada, cada slot de la tabla es un contenedor de tamaño blockSize_
  // En el caso de dispersión abierta, cada slot de la tabla es un contenedor dinámico
  Sequence<Key>** table_;
  DispersionFunction<Key>* fd_;
  ExplorationFunction<Key>* fe_;  // Solo usado en dispersión cerrada
};

/**
 * @brief Constructor de la clase HashTable para dispersión cerrada.
 * 
 * @tparam Key 
 * @tparam Container 
 * @param tableSize 
 * @param hashFunction 
 * @param explorationFunction 
 * @param blockSize 
 */
template<class Key, class Container>
HashTable<Key, Container>::HashTable(unsigned tableSize, DispersionFunction<Key>* hashFunction, ExplorationFunction<Key>* explorationFunction, unsigned blockSize) {
  tableSize_ = tableSize;
  blockSize_ = blockSize;
  fd_ = hashFunction;
  fe_ = explorationFunction;
  table_ = new Sequence<Key>*[tableSize_];
  // Inicializamos cada slot de la tabla con un contenedor de tamaño blockSize
  for (unsigned i = 0; i < tableSize_; i++) {
    table_[i] = new StaticSequence<Key>(blockSize_);
  }
}

/**
 * @brief Constructor sobrecargado para dispersión abierta (sin explorationFunction y blockSize).
 * 
 * @tparam Key 
 * @tparam Container 
 * @param tableSize 
 * @param hashFunction 
 */
template<class Key, class Container>
HashTable<Key, Container>::HashTable(unsigned tableSize, DispersionFunction<Key>* hashFunction) {
  tableSize_ = tableSize;
  fd_ = hashFunction;
  table_ = new Sequence<Key>*[tableSize_];
  // Inicializamos cada slot de la tabla con un contenedor vacío
  for (unsigned i = 0; i < tableSize_; ++i) {
    table_[i] = new DynamicSequence<Key>;
  }
}

/**
 * @brief Implementa search siguiendo la interfaz Sequence<Key>.
 * 
 * @tparam Key 
 * @tparam Container 
 * @param key 
 * @return true 
 * @return false 
 */
template<class Key, class Container>
bool HashTable<Key, Container>::search(const Key& key) const {
  // Aplicamos la función de dispersión al key para obtener el índice
  unsigned index = (*fd_)(key);
  return table_[index]->search(key);
}

/**
 * @brief Implementa insert siguiendo la interfaz Sequence<Key>.
 * 
 * @tparam Key 
 * @tparam Container 
 * @param key 
 * @return true 
 * @return false 
 */
template<class Key, class Container>
bool HashTable<Key, Container>::insert(const Key& key) {
  // Aplicamos la función de dispersión al key para obtener el índice
  unsigned index = (*fd_)(key);
  // Insertamos el key en el contenedor correspondiente
  return table_[index]->insert(key);
}