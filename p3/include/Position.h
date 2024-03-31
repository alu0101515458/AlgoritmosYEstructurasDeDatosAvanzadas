#pragma once
#include <iostream>

typedef int Coor_t;

class Position {
 public:
  // Método Abstracto
  virtual Coor_t operator[](unsigned int) const = 0;
};