#pragma once
#include <iostream>
#include "Lattice.h"

// enum State (1,0)
enum State {ZERO = 0, ONE = 1};
typedef int Position;

class Lattice;

class Cell {
 public:
  Cell(const Position&, const State&);

  State getState() const;
  Position getPos() const;

  void setState(State);
  void setPosition (const Position& pos);

  State nextState(const Lattice&);
  void updateState ();

 private:
  Position pos_;
  State state_;
  State next_state_;
};

std::ostream& operator<<(std::ostream&, const Cell&);