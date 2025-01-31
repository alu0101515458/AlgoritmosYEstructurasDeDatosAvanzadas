#include "CellACE.h"

class CellACE30: public CellACE {
 public:
  CellACE30(const Position&, const State&);
  State nextState(const Lattice&);
};

