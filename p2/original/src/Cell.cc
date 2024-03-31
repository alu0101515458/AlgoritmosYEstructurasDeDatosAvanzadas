#include "../include/Cell.h"

/**
 * @brief Constructor de la clase Cell.
 * 
 * @param pos 
 * @param state 
 */
Cell::Cell(const Position& pos, const State& state) : pos_(pos), state_(state) {}

/**
 * @brief Método que devuelve el estado de la célula.
 * 
 * @return State 
 */
State Cell::getState() const { return state_; }

/**
 * @brief Método que devuelve la posición de la célula.
 * 
 * @return Position 
 */
Position Cell::getPos() const { return pos_; }

/**
 * @brief Método que establece el estado de la célula.
 * 
 * @param state 
 */
void Cell::setState(State state) { state_ = state; }

/**
 * @brief Método que establece la posición de la célula.
 * 
 * @param pos 
 */
void Cell::setPosition(const Position& pos) {
  pos_ = pos;
}

/**
 * @brief Método que devuelve el estado siguiente de la célula.
 * 
 * C(G+1)=(C(G)+R(G)+C(G)*R(G)+L(G)*C(G)*R(G))%2
 * 
 * @param lattice 
 * @return int 
 */
State Cell::nextState(const Lattice& lattice) {
  State result;
  int count = 0;
  State cell_ai_pos = lattice.getCell({pos_.first-1, pos_.second-1}).getState();
  State cell_a_pos = lattice.getCell({pos_.first-1, pos_.second}).getState();
  State cell_ad_pos = lattice.getCell({pos_.first-1, pos_.second+1}).getState();
  State cell_ci_pos = lattice.getCell({pos_.first, pos_.second-1}).getState();
  State cell_cr_pos = lattice.getCell({pos_.first, pos_.second+1}).getState();
  State cell_bi_pos = lattice.getCell({pos_.first+1, pos_.second-1}).getState();
  State cell_b_pos = lattice.getCell({pos_.first+1, pos_.second}).getState();
  State cell_bd_pos = lattice.getCell({pos_.first+1, pos_.second+1}).getState();

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

/**
 * @brief Método que actualiza el estado de la célula.
 * 
 */
void Cell::updateState () {
  state_ = next_state_;
}

/**
 * @brief Sobrecarga del operador de salida para la clase Cell.
 * 
 * @param os 
 * @param cell 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  // Si el estado de la célula es 0, se imprime un espacio en blanco, si no, una X.
  if (cell.getState() == DEAD) os << " ";
  else os << "X";
  return os;
}