#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <stdexcept>
#include <set>

#include "Cell.h"

typedef int Generation;
typedef std::pair<int, int> Position;

class Cell;

class Lattice {
 public:
  Lattice(int, int);
  Lattice(const char*);
  ~Lattice();

  const Cell& getCell(const Position&) const;
  const std::vector<std::vector<Cell*>>& getCells() const;
  bool getNoBorders() const;
  bool getReflective() const;
  int getRows() const;
  int getColumns() const;
  const Generation& getGeneration() const;
  int getPopulation() const;

  void setBorder();
  void setNoBorders(bool);
  void setReflective(bool);

  void nextGeneration();
  void Show();
  std::vector<std::pair<int, int>> InitialAliveCells();

  const Cell& operator[](const Position& pos) const;
  Cell& operator[](const Position& pos);

 private:
  Generation gen_=1;
  std::vector<std::vector<Cell*>> lattice_;
  int n_;
  int m_;
  bool noborders_ = false;
  bool is_reflective_ = false;
};

std::ostream& operator<<(std::ostream&, const Lattice&);