#pragma once
#include "Lattice.h"
#include "CellLife23_3.h"
#include "CellLife51_346.h"
#include "PositionDim.h"
#include <algorithm>
#include <fstream>

class Lattice2D : public Lattice {
 public:
  Lattice2D(int, int);
  Lattice2D(const char*);
  ~Lattice2D();

  const Cell& getCell(const Position&) const;
  const std::vector<std::vector<Cell*>>& getCells() const;
  bool getNoBorders() const;
  bool getReflective() const;
  int getRows() const;
  int getColumns() const;
  int getPopulation() const;

  virtual void setBorder() = 0;
  void setReflective(bool);
  void setNoBorders(bool);

  std::vector<std::pair<int, int>> InitialAliveCells();
  virtual void nextGeneration() = 0;
  virtual void Show() = 0;

  const Cell& operator[](Position& pos) const; 
  Cell& operator[](const Position& pos);

 protected:
  std::vector<std::vector<Cell*>> lattice_;
  int n_;
  int m_;
  bool noBorders_;
  bool reflective_;
  bool CellLife23_3_;
  bool CellLife51_346_;
};