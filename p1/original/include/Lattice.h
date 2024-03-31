#pragma once
#include <iostream>
#include <vector>
#include "Cell.h"

typedef int Generation;
typedef int Position;

class Cell;

class Lattice {
 public:
  Lattice(int);
  ~Lattice();

  const Cell& getCell(const Position&) const;
  const std::vector<Cell*>& getCells() const;
  bool getPeriodic() const;
  bool getReflector() const;

  void setBorder(int);
  void setVectorCells(const std::vector<Cell*>&);
  void setPeriodic(bool);
  void setReflector(bool);

  void ConstructLattice(int, int);
  const Generation& getGeneration() const;
  void nextGeneration();

  void Show();

 private:
  Generation gen_;
  std::vector<Cell*> cells_;
  bool is_periodic_ = false;
  bool is_reflector_ = false;
};

std::ostream& operator<<(std::ostream&, const Lattice&);