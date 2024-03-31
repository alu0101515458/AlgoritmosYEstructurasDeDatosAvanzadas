#pragma once
#include <iostream>
#include <utility>
#include "Lattice.h"

enum State {DEAD = 0, ALIVE = 1};
typedef std::pair<int, int> Position;

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