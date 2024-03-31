#include "Cell.h"

class CellLife: public Cell {
 public:
  CellLife(const Position&, const State&);
  virtual State nextState(const Lattice&) = 0;
};