#pragma once
#include "ac_exception.h"
#include "Position.h"
#include <stdarg.h>

#pragma once

template <int Dim=2, class Coordinate_t=Coor_t>
class PositionDim: public Position {
 private:
  Coordinate_t Coordinates[Dim];
 public:
  // Constructor con lista variable de parámetros
  PositionDim(int sz, ...);
  Coordinate_t operator[](unsigned int) const;
};