#include <algorithm>
#include <list>
#include <vector>
#include <optional>
#pragma once

typedef int Position;

/**
 * @brief Clase abstracta que representa una secuencia.
 *
 * @tparam Key
 */
template <class Key>
class Sequence {
 public:
  virtual bool search(const Key& k) const = 0;
  virtual bool insert(const Key& k) = 0;
  virtual bool isFull() const = 0;

  virtual Key& operator[](const Position&) = 0;
};

/**
 * @brief Clase que representa una secuencia estática (Dispersión Cerrada).
 *
 * @tparam Key
 */
template <class Key>
class StaticSequence : public Sequence<Key> {
 public:
  StaticSequence(size_t, Key, bool);

  size_t getSize() const;
  bool getTrace() const;

  void setTrace(bool);

  bool search(const Key&) const override;
  bool insert(const Key&) override;
  bool isFull() const override;
  void countComparisons();
  int getComparisons() const;
  void resetComparisons();

  void print() const;

  Key& operator[](const Position&) override;

 private:
  size_t size_; // Tamaño de la secuencia.
  std::vector<Key> keys_; // Usamos std::optional para representar una posición vacía.
  Key emptyValue_; // Valor que representa una posición vacía.
  bool trace_; // Indica si se debe mostrar la secuencia.
  int comparisons_ = 0; // Número de comparaciones realizadas.
};

/**
 * @brief Constructor de la clase StaticSequence.
 *
 * @tparam Key
 * @param size_
 * @param emptyValue
 */
template <class Key>
StaticSequence<Key>::StaticSequence(size_t size, Key emptyValue, bool trace) : size_(size), keys_(size, emptyValue), emptyValue_(emptyValue), trace_(trace) {}

/**
 * @brief Retorna el tamaño de la secuencia.
 *
 * @tparam Key
 * @return size_t
 */
template <class Key>
size_t StaticSequence<Key>::getSize() const { return size_; }

/**
 * @brief Retorna si se debe mostrar la secuencia.
 *
 * @tparam Key
 * @return true Si se debe mostrar la secuencia.
 * @return false Si no se debe mostrar la secuencia.
 */
template <class Key>
bool StaticSequence<Key>::getTrace() const { return trace_; }

/**
 * @brief Establece si se debe mostrar la secuencia.
 *
 * @tparam Key
 * @param trace
 */
template <class Key>
void StaticSequence<Key>::setTrace(bool trace) { trace_ = trace; }

/**
 * @brief Busca una clave en la secuencia.
 *
 * @tparam Key
 * @param k
 * @return true Si la clave se encuentra en la secuencia.
 * @return false Si la clave no se encuentra en la secuencia.
 */
template <class Key>
bool StaticSequence<Key>::search(const Key& k) const {
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
template <class Key>
bool StaticSequence<Key>::insert(const Key& k) {
  // Si la secuencia está llena, no se puede insertar.
  if (isFull()) {
    return false;
  }

  // Si la clave ya está en la secuencia, no se puede insertar.
  if (search(k)) {
    return false;
  }

  // Buscamos la primera posición vacía.
  for (size_t i = 0; i < size_; i++) {
    if (keys_[i] == emptyValue_) {
      keys_[i] = k;
      return true;
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
template <class Key>
bool StaticSequence<Key>::isFull() const {
  return std::find(keys_.begin(), keys_.end(), emptyValue_) == keys_.end();
}

/**
 * @brief Método que incrementa el número de comparaciones realizadas.
 *
 * @tparam Key
 */
template <class Key>
void StaticSequence<Key>::countComparisons() { comparisons_++; }

/**
 * @brief Método que retorna el número de comparaciones realizadas.
 *
 * @return int
 */
template <class Key>
int StaticSequence<Key>::getComparisons() const { return comparisons_; }

/**
 * @brief Método que reinicia el número de comparaciones realizadas.
 *
 * @tparam Key
 */
template <class Key>
void StaticSequence<Key>::resetComparisons() { comparisons_ = 0; }

/**
 * @brief Función que imprime la secuencia.
 * 
 */
template <class Key>
void StaticSequence<Key>::print() const {
  for (size_t i = 0; i < size_; i++) {
    std::cout << "> " << this->keys_[i] << " ";
  }
  std::cout << std::endl;
}

/**
 * @brief Retorna la clave en la posición p.
 *
 * @tparam Key
 * @param p
 * @return Key
 */
template <class Key>
Key& StaticSequence<Key>::operator[](const Position& position) {
  if (position < 0 || position >= static_cast<int>(size_)) {
    throw std::out_of_range("Índice fuera de rango");
  }
  return keys_[position];
}