#include "CellLife.h"

class CellLife23_3: public CellLife {
 public:
  CellLife23_3(const Position&, const State&);
  State nextState(const Lattice&);
};