#include "CellACE.h"

class CellACE110: public CellACE {
 public:
  CellACE110(const Position&, const State&);
  State nextState(const Lattice&);
};