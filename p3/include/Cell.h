#pragma once
#include <iostream>
#include <utility>
#include "Lattice.h"
#include "PositionDim.h"

enum State {DEAD = 0, ALIVE = 1};

class Lattice;

class Cell {
 public:
  Cell(const Position&, const State&);

  State getState() const;
  Position* getPos() const;

  void setState(State);
  void setPosition(const Position& pos);

  virtual State nextState(const Lattice&) = 0;
  void updateState();

 protected:
  Position* pos_;
  State state_;
  State next_state_;
};