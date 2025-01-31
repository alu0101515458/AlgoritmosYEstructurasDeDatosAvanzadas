#include "../include/Lattice.h"

/**
 * @brief Función que devuelve la generación actual
 * 
 * @return const Generation& 
 */
const Generation& Lattice::getGeneration() const {
  return gen_;
}