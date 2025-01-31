#include "../include/Cell.h"

/**
 * @brief Constructor de la clase Cell.
 * 
 * @param pos 
 * @param state 
 */
Cell::Cell(const Position& pos, const State& state) {
  pos_ = const_cast<Position*>(&pos);
  state_ = state;
}

/**
 * @brief Función que devuelve el estado de la célula.
 * 
 * @return State 
 */
State Cell::getState() const {
  return state_;
}

/**
 * @brief Función que devuelve la posición de la célula.
 * 
 * @return Position 
 */
Position* Cell::getPos() const {
  return const_cast<Position*>(pos_);
}

/**
 * @brief Función que cambia el estado de la célula.
 * 
 * @param state 
 */
void Cell::setState(State state) {
  state_ = state;
}

/**
 * @brief Función que cambia la posición de la célula.
 * 
 * @param pos 
 */
void Cell::setPosition(const Position& pos) {
  pos_ = const_cast<Position*>(&pos);
}

/**
 * @brief Función que actualiza el estado de la célula.
 * 
 */
void Cell::updateState() {
  state_ = next_state_;
}
