#include "../include/CellLife23_3.h"

CellLife23_3::CellLife23_3(const Position& p, const State& s): CellLife(p, s) {}

State CellLife23_3::nextState(const Lattice& l) {
  State result;
  int count = 0;

  for (unsigned i = 0; i < lattice_.size(); ++i) {
    for (unsigned j = 0; j < lattice_[i].size(); ++j) {
      if (i != getPos().first || j != getPos().second) {
        if (lattice_[i][j].getState() == ALIVE) {
          ++count;
        }
      }
    }
  }

  // State cell_ai_pos = lattice.getCell({pos_.first-1, pos_.second-1}).getState();
  // State cell_a_pos = lattice.getCell({pos_.first-1, pos_.second}).getState();
  // State cell_ad_pos = lattice.getCell({pos_.first-1, pos_.second+1}).getState();
  // State cell_ci_pos = lattice.getCell({pos_.first, pos_.second-1}).getState();
  // State cell_cr_pos = lattice.getCell({pos_.first, pos_.second+1}).getState();
  // State cell_bi_pos = lattice.getCell({pos_.first+1, pos_.second-1}).getState();
  // State cell_b_pos = lattice.getCell({pos_.first+1, pos_.second}).getState();
  // State cell_bd_pos = lattice.getCell({pos_.first+1, pos_.second+1}).getState();

  if (cell_ai_pos == ALIVE) ++count;
  if (cell_a_pos == ALIVE) ++count;
  if (cell_ad_pos == ALIVE) ++count;
  if (cell_ci_pos == ALIVE) ++count;
  if (cell_cr_pos == ALIVE) ++count;
  if (cell_bi_pos == ALIVE) ++count;
  if (cell_b_pos == ALIVE) ++count;
  if (cell_bd_pos == ALIVE) ++count;

  if (getState() == ALIVE) {
    if (count == 2 || count == 3) result = ALIVE;
    else result = DEAD;
  } else {
    if (count == 3) result = ALIVE;
    else result = DEAD;
  }
  next_state_ = (State)result;
  return result;
}