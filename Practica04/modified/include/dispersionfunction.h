#include <cstdlib>
#pragma once

/**
 * @brief Clase abstracta que representa una función de dispersión.
 * 
 * @tparam Key. Tipo de dato de la clave.
 */
template<class Key>
class DispersionFunction {
 public:
  virtual unsigned operator()(const Key&) const = 0;
};

/**
 * @brief Función de dispersión Módulo. h(k) = k % tableSize
 * 
 * @tparam Key. Tipo de dato de la clave.
 */
template<class Key>
class Module : public DispersionFunction<Key> {
 public:
  Module(unsigned size);

  unsigned operator()(const Key& key) const override;

 private:
  unsigned tableSize_;
};

/**
 * @brief Constructor de la clase Modulo.
 * 
 * @tparam Key. Tipo de dato de la clave.
 * @param size. Tamaño de la tabla.
 */
template<class Key>
Module<Key>::Module(unsigned size) : tableSize_(size) {}

/**
 * @brief Función de dispersión Módulo. h(k) = k % tableSize
 * 
 * @tparam Key. Tipo de dato de la clave.
 * @param key. Clave a dispersar.
 * @return unsigned. Valor de dispersión.
 */
template<class Key>
unsigned Module<Key>::operator()(const Key& key) const {
  // Aplicamos la función de dispersión
  return (key % tableSize_);
}

/**
 * @brief Función de dispersión Basada en la Suma de dígitos. h(k) = sum(ki) % tableSize
 * 
 * @tparam Key. Tipo de dato de la clave.
 */
template<class Key>
class Sum : public DispersionFunction<Key> {
 public:
  Sum(unsigned size);

  unsigned operator()(const Key& key) const override;
   
 private:
  unsigned tableSize_;
};

/**
 * @brief Constructor de la clase Sum.
 * 
 * @tparam Key. Tipo de dato de la clave.
 * @param size. Tamaño de la tabla.
 */
template<class Key>
Sum<Key>::Sum(unsigned size) : tableSize_(size) {}

/**
 * @brief Función de dispersión Basada en la Suma de dígitos. h(k) = sum(ki) % tableSize
 * 
 * @tparam Key. Tipo de dato de la clave.
 * @param key. Clave a dispersar.
 * @return unsigned. Valor de dispersión.
 */
template<class Key>
unsigned Sum<Key>::operator()(const Key& key) const {
  // Variable para almacenar la suma de los dígitos
  unsigned sum = 0;
  // Variable temporal para no modificar la clave original
  Key temp = key;
  // Mientras la clave tenga dígitos
  while ((int)temp > 0) {
    sum += temp % 10; // Suma los dígitos.
    temp /= 10; // Avanza al siguiente dígito.
  }
  // Devolvemos el valor de dispersión entre 1 y tableSize-1
  return (sum % tableSize_);
}

/**
 * @brief Función de dispersión Pseudoaleatoria. h(k) = {srand(k); rand()} % tableSize.
 * 
 * @tparam Key. Tipo de dato de la clave.
 */
template<class Key>
class Pseudo : public DispersionFunction<Key> {
 public:
  Pseudo(unsigned size);

  unsigned operator()(const Key& key) const override;

 private:
  unsigned tableSize_;
};

/**
 * @brief Constructor de la clase Pseudo.
 * 
 * @tparam Key. Tipo de dato de la clave.
 * @param size. Tamaño de la tabla.
 */
template<class Key>
Pseudo<Key>::Pseudo(unsigned size) : tableSize_(size) {}

/**
 * @brief Función de dispersión Pseudoaleatoria. h(k) = {srand(k); rand()} % tableSize.
 * 
 * @tparam Key. Tipo de dato de la clave.
 * @param key. Clave a dispersar.
 * @return unsigned. Valor de dispersión.
 */
template<class Key>
unsigned Pseudo<Key>::operator()(const Key& key) const {
  // Generamos la semilla para la función de dispersión
  srand(key);
  // Devolvemos el valor de dispersión entre 1 y tableSize-1 haciendo uso de la función rand()
  return (rand() % tableSize_);
}