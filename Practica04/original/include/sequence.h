#include <list>
#include <vector>
#include <algorithm>
#pragma once

/**
 * @brief Clase abstracta que representa una secuencia.
 * 
 * @tparam Key 
 */
template<class Key> 
class Sequence {
 public:
  virtual bool search(const Key& k) const = 0;
  virtual bool insert(const Key& k) = 0;
  virtual bool isFull() const = 0;
};

/**
 * @brief Clase que representa una secuencia estática (Dispersión Cerrada).
 * 
 * @tparam Key 
 */
template<class Key>
class StaticSequence : public Sequence<Key> {
 public:
  StaticSequence(unsigned blockSize_);

  virtual bool search(const Key& k) const override;
  virtual bool insert(const Key& k) override;
  bool isFull() const override;
 
 private:
  std::vector<Key> keys_;
  unsigned blockSize_;
};

/**
 * @brief Constructor de la clase StaticSequence.
 * 
 * @tparam Key 
 * @param blockSize_ 
 */
template<class Key>
StaticSequence<Key>::StaticSequence(unsigned blockSize) {
  blockSize_ = blockSize;
  keys_ = std::vector<Key>(blockSize_, -1);
}

/**
 * @brief Busca una clave en la secuencia.
 * 
 * @tparam Key 
 * @param k 
 * @return true Si la clave se encuentra en la secuencia.
 * @return false Si la clave no se encuentra en la secuencia.
 */
template<class Key>
bool StaticSequence<Key>::search(const Key& k) const {
  // Buscamos la clave en la secuencia y retornamos el resultado de la búsqueda
  return std::find(keys_.begin(), keys_.end(), k) != keys_.end();
}

/**
 * @brief Inserta una clave en la secuencia.
 * 
 * @tparam Key 
 * @param k 
 * @return true Si la clave se insertó correctamente.
 * @return false Si la clave no se insertó correctamente.
 */
template<class Key>
bool StaticSequence<Key>::insert(const Key& k) {
  // Verificamos que la clave no esté ya en la secuencia
  if (std::find(keys_.begin(), keys_.end(), k) == keys_.end()) {
    // Buscamos un slot vacío en la secuencia
    for (unsigned i = 0; i < blockSize_; i++) {
      if ((int)keys_[i] == -1) {
        keys_[i] = k;
        return true;
      }
    }
  }
  return false;
}

/**
 * @brief Verifica si la secuencia está llena.
 * 
 * @tparam Key 
 * @return true Si la secuencia está llena.
 * @return false Si la secuencia no está llena.
 */
template<class Key>
bool StaticSequence<Key>::isFull() const {
  // Verificamos si el tamaño de la secuencia es igual al tamaño del bloque
  return ((int)keys_[blockSize_ - 1] == -1);
}


/**
 * @brief Clase que representa una secuencia dinámica (Dispersión Abierta).
 * 
 * @tparam Key 
 */
template<class Key>
class DynamicSequence : public Sequence<Key> {
 public:
  DynamicSequence();

  virtual bool search(const Key& k) const override;
  virtual bool insert(const Key& k) override;
  bool isFull() const override;

 private:
  std::list<Key> keys_; // Usamos std::list para una secuencia dinámica
};

/**
 * @brief Constructor de la clase DynamicSequence.
 * 
 * @tparam Key 
 */
template<class Key>
DynamicSequence<Key>::DynamicSequence() {}

/**
 * @brief Busca una clave en la secuencia.
 * 
 * @tparam Key 
 * @param k 
 * @return true Si la clave se encuentra en la secuencia.
 * @return false Si la clave no se encuentra en la secuencia.
 */
template<class Key>
bool DynamicSequence<Key>::search(const Key& k) const {
  // Buscamos la clave en la secuencia y retornamos el resultado de la búsqueda
  return std::find(keys_.begin(), keys_.end(), k) != keys_.end();
}

/**
 * @brief Inserta una clave en la secuencia.
 * 
 * @tparam Key 
 * @param k 
 * @return true Si la clave se insertó correctamente.
 * @return false Si la clave no se insertó correctamente.
 */
template<class Key>
bool DynamicSequence<Key>::insert(const Key& k) {
  // Verificamos que la clave no esté ya en la secuencia
  if (std::find(keys_.begin(), keys_.end(), k) == keys_.end()) {
    keys_.push_back(k);
    return true;
  }
  return false;
}

/**
 * @brief Verifica si la secuencia está llena.
 * 
 * @tparam Key 
 * @return false Las secuencias dinámicas nunca están llenas.
 */
template<class Key>
bool DynamicSequence<Key>::isFull() const {
  return false;
}