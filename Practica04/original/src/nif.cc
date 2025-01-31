#include "../include/nif.h"

/**
 * @brief Constructor por defecto que inicializa el  Nif con un valor aleatorio
 * 
 */
Nif::Nif() {
  // Inicializamos una variable estática para que el generador de números aleatorios se inicialice solo una vez
  static bool initialized = false;
  if (!initialized) {
    // Usamos la hora actual como semilla
    std::srand(std::time(nullptr));
    initialized = true;
  }
  // Ajustamos el rango de std::rand() para asegurar un número de 8 dígitos
  value_ = 10000000 + std::rand() % 90000000;
}

/**
 * @brief Constructor de cambio de tipo a partir de un dato entero long
 * 
 * @param val Valor del  Nif
 */
Nif::Nif(long val) {
  // Aprobamos el valor si es un número de 8 dígitos (aunque sean ceros a la izquierda)
  value_ = val;
}

/**
 * @brief Sobrecarga del operador de comparación de igualdad
 * 
 * @param other  Nif con el que comparar
 * @return true Si los Nif son iguales
 * @return false Si los  Nif son distintos
 */
bool Nif::operator==(const Nif& other) const {
  return this->value_ == other.value_;
}

/**
 * @brief Sobrecarga del operador de comparación de desigualdad
 * 
 * @param other  Nif con el que comparar
 * @return true Si los Nif son distintos
 * @return false Si los  Nif son iguales
 */
bool Nif::operator!=(const int& other) const {
  return this->value_ != other;
}

/**
 * @brief Sobrecarga del operador de comparación de menor que
 * 
 * @param other  Nif con el que comparar
 * @return true Si el  Nif es menor que el otro
 * @return false Si el Nif es mayor o igual que el otro
 */
bool Nif::operator<(const  Nif& other) const {
  return this->value_ < other.value_;
}

/**
 * @brief Sobrecarga del operador de comparación de mayor que
 * 
 * @param other  Nif con el que comparar
 * @return true Si el  Nif es mayor que el otro
 * @return false Si el Nif es menor o igual que el otro
 */
bool Nif::operator>(const  Nif& other) const {
  return this->value_ > other.value_;
}

/**
 * @brief Sobrecarga del operador de comparación de menor o igual que
 * 
 * @param other  Nif con el que comparar
 * @return true Si el  Nif es menor o igual que el otro
 * @return false Si el Nif es mayor que el otro
 */
bool Nif::operator<=(const Nif& other) const {
  return this->value_ <= other.value_;
}

/**
 * @brief Sobrecarga del operador de comparación de mayor o igual que
 * 
 * @param other  Nif con el que comparar
 * @return true Si el  Nif es mayor o igual que el otro
 * @return false Si el Nif es menor que el otro
 */
bool Nif::operator>=(const Nif& other) const {
  return this->value_ >= other.value_;
}

/**
 * @brief Sobrecarga del operador de división
 * 
 * @param other Valor por el que dividir
 * @return Nif& Referencia al  Nif dividido
 */
Nif Nif::operator/=(const int& other) {
  value_ /= other;
  return *this;
}

/**
 * @brief Sobrecarga del operador de cambio de tipo a long
 * 
 * @return long Valor del  Nif
 */
Nif::operator long() const {
  return value_;
}