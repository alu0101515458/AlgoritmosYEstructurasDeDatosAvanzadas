#pragma once
#include <iostream>
#include <vector>
#include "PositionDim.h"
#include "Cell.h"

typedef Position* Position;
typedef int Generation;

class Lattice {
 public:
  const Generation& getGeneration() const;

  // LATTICE1D:
  // Lattice(int);
  // bool getOpen() const;
  // bool getPeriodic() const;

  // const Cell& getCell(const Position&) const;
  // const std::vector<Cell*>& getCells() const;
  // bool getPeriodic() const;
  // bool getOpen() const;

  // void setVectorCells(const std::vector<Cell*>&);
  // void setPeriodic(bool);
  // void setOpen(bool);

  // void ConstructLattice(int);

  virtual void setBorder() = 0;

  virtual void nextGeneration() = 0;
  virtual void Show() = 0;


 protected:
  Generation gen_=1;

  // LATTICE1D:
  // std::vector<Cell*> lattice_;
  // bool is_open_ = false;
  // bool is_periodic_ = false;
};