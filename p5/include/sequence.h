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

  virtual Key operator[](const Position&) const = 0;
};

/**
 * @brief Clase que representa una secuencia estática (Dispersión Cerrada).
 *
 * @tparam Key
 */
template <class Key>
class StaticSequence : public Sequence<Key> {
 public:
  StaticSequence(size_t size);

  bool search(const Key& k) const override;
  bool insert(const Key& k) override;
  bool isFull() const override;
  Key operator[](const Position&) const override;

 private:
  std::vector<std::optional<Key>> keys_;
  size_t size_;
};

/**
 * @brief Constructor de la clase StaticSequence.
 *
 * @tparam Key
 * @param size_
 */
template <class Key>
StaticSequence<Key>::StaticSequence(size_t size) : size_(size), keys_(size) {}

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
  // std::any_of: Devuelve true si existe al menos k en la secuencia.
  return std::any_of(keys_.begin(), keys_.end(),
                     [&k](const std::optional<Key>& key) {
                       return key.has_value() && *key == k;
                     });
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

  // std::find_if: Busca la primera posición vacía en la secuencia.
  auto it = std::find_if(
      keys_.begin(), keys_.end(),
      [](const std::optional<Key>& key) { return !key.has_value(); });

  // Si se encontró una posición vacía, se inserta la clave.
  if (it != keys_.end()) {
    *it = k;
    return true;
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
  // std::none_of: Devuelve true si no existe ninguna posición vacía en la secuencia.
  return std::none_of(
      keys_.begin(), keys_.end(),
      [](const std::optional<Key>& key) { return !key.has_value(); });
}

/**
 * @brief Retorna la clave en la posición p.
 *
 * @tparam Key
 * @param p
 * @return Key
 */
template <class Key>
Key StaticSequence<Key>::operator[](const Position& position) const {
  // Si la posición es mayor o igual al tamaño de la secuencia o la posición está vacía, se lanza una excepción.
  if (position >= size_ || !keys_[position].has_value()) {
    throw std::out_of_range("La posición a la que se quiere acceder no existe o está vacía.");
  }
  // Se retorna la clave en la posición p.
  return *keys_[position];
}