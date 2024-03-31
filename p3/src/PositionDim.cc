#include "../include/PositionDim.h"

/**
 * @brief Constructor de la clase PositionDim.
 * 
 * @tparam Dim 
 * @tparam Coordinate_t 
 * @param sz 
 * @param ... 
 */
template <int Dim, class Coordinate_t>
PositionDim<Dim, Coordinate_t>::PositionDim(int sz, ...) {
  va_list vl;
  va_start(vl, sz);
  for (int d = 0; d < Dim; d++) {
    Coordinates[d] = va_arg(vl, Coordinate_t);
  }
  va_end(vl);
}

/**
 * @brief Sobrecarga del operador [] para obtener las coordenadas de la posición en la dimensión d.
 * 
 * @tparam Dim 
 * @tparam Coordinate_t 
 * @param d 
 * @return Coordinate_t 
 */
template <int Dim, class Coordinate_t>
Coordinate_t PositionDim<Dim, Coordinate_t>::operator[](unsigned int d) const {
  if (d >= Dim) {
    throw ac_exception("Dimension fuera de rango");
  }
  return Coordinates[d];
}