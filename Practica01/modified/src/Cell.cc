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
void Cell::setPosition (const Position& pos) {
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
  int result;
  // Obtenemos el estado de las células adyacentes y la propia.
  int cell_c_pos = lattice.getCell(this->pos_).getState();
  int cell_r_pos = lattice.getCell(this->pos_ + 1).getState();
  int cell_l_pos = lattice.getCell(this->pos_ - 1).getState();
  // Calculamos el estado siguiente de la célula con la fórmula dada.
  result = (cell_c_pos + cell_r_pos + cell_c_pos * cell_r_pos + cell_l_pos * cell_c_pos * cell_r_pos) % 2;
  next_state_ = (State)result;
  return (State)result;
}

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
  if (cell.getState() == ZERO) os << " ";
  else os << "X";
  return os;
}

/**
 * MODIFICACIÓN
 * @brief Método que devuelve el estado siguiente de la célula según la regla 30.
 * 
 * @param lattice 
 * @return State 
 */
State Cell::rule30(const Lattice& lattice) {
  int result;
  // Obtenemos el estado de las células adyacentes y la propia.
  int cell_c_pos = lattice.getCell(this->pos_).getState();
  int cell_r_pos = lattice.getCell(this->pos_ + 1).getState();
  int cell_l_pos = lattice.getCell(this->pos_ - 1).getState();
  // Calculamos el estado siguiente de la célula con la fórmula dada.
  result = (cell_l_pos + cell_c_pos + cell_r_pos + cell_c_pos*cell_r_pos) % 2;
  next_state_ = (State)result;
  return (State)result;
}