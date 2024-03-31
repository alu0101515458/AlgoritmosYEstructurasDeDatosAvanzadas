#include <vector>
#include <memory>
#include "../include/dispersionfunction.h"
#include "../include/explorationfunction.h"
#include "../include/sequence.h"

#pragma once

template<class Key, class Container = StaticSequence<Key>>
class HashTableStatic {
 public:
  HashTableStatic(unsigned tableSize, DispersionFunction<Key>* hashFunction, ExplorationFunction<Key>* explorationFunction, unsigned blockSize);

  bool search(const Key& key) const;
  bool insert(const Key& key, int& count);

 private:
  unsigned blockSize_; // Solo usado en dispersión cerrada
  unsigned tableSize_;
  // Se usa un puntero a la interfaz Sequence para poder usar tanto contenedores estáticos como dinámicos (StaticSequence y DynamicSequence)
  // En el caso de dispersión cerrada, cada slot de la tabla es un contenedor de tamaño blockSize_
  // En el caso de dispersión abierta, cada slot de la tabla es un contenedor dinámico
  std::vector<Container*> table_;
  DispersionFunction<Key>* fd_;
  ExplorationFunction<Key>* fe_;  // Solo usado en dispersión cerrada
  int count_ = 0;
};

template<class Key, class Container = DynamicSequence<Key>>
class HashTableDynamic {
 public:
  HashTableDynamic(unsigned tableSize, DispersionFunction<Key>* hashFunction);

  bool search(const Key& key) const;
  bool insert(const Key& key, int& count);

 private:
  unsigned blockSize_; // Solo usado en dispersión cerrada
  unsigned tableSize_;
  // Se usa un puntero a la interfaz Sequence para poder usar tanto contenedores estáticos como dinámicos (StaticSequence y DynamicSequence)
  // En el caso de dispersión cerrada, cada slot de la tabla es un contenedor de tamaño blockSize_
  // En el caso de dispersión abierta, cada slot de la tabla es un contenedor dinámico
  Sequence<Container*>** table_;
  DispersionFunction<Key>* fd_;
  int count_ = 0;
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
HashTableStatic<Key, Container>::HashTableStatic(unsigned tableSize, DispersionFunction<Key>* hashFunction, ExplorationFunction<Key>* explorationFunction, unsigned blockSize) {
  tableSize_ = tableSize;
  blockSize_ = blockSize;
  fd_ = hashFunction;
  fe_ = explorationFunction;
  table_ = std::vector<Container*>(tableSize_);
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
HashTableDynamic<Key, Container>::HashTableDynamic(unsigned tableSize, DispersionFunction<Key>* hashFunction) {
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
bool HashTableStatic<Key, Container>::search(const Key& key) const {
  // Aplicamos la función de dispersión al key para obtener el índice
  unsigned index = (*fd_)(key);
  return table_[index]->search(key);
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
bool HashTableDynamic<Key, Container>::search(const Key& key) const {
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
bool HashTableStatic<Key, Container>::insert(const Key& key, int& count) {
  // Aplicamos la función de dispersión al key para obtener el índice
  unsigned index = (*fd_)(key);
  // Insertamos el key en el contenedor correspondiente
  return table_[index]->insert(key);
  ++count;
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
bool HashTableDynamic<Key, Container>::insert(const Key& key, int& count) {
  // Aplicamos la función de dispersión al key para obtener el índice
  unsigned index = (*fd_)(key);
  // Insertamos el key en el contenedor correspondiente
  return table_[index]->insert(key);
  ++count;
}