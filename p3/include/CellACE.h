#include "Cell.h"

class CellACE: public Cell {
 public:
  CellACE(const Position&, const State&);
  virtual State nextState(const Lattice&) = 0;
};