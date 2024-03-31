#include "../include/Lattice.h"
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

/**
 * @brief Constructor de la clase Lattice.
 * 
 */
Lattice::Lattice(int tamagnio) {
  // Inicializa la generación en 0.
  gen_ = 0;
  // Inicializa el vector de células con el tamaño dado.
  cells_.resize(tamagnio);
  // Inicializa cada posición con un objeto Cell por defecto.
  for (int i = 0; i < tamagnio; ++i) {
    cells_[i] = new Cell(i, ZERO);  // Inicializa cada posición con un objeto Cell por defecto.
  }
}

/**
 * @brief Destructor de la clase Lattice.
 * 
 */
Lattice::~Lattice() {
  // Libera la memoria de cada célula.
  if (!getPeriodic() && !getReflector()) {
    for (auto cell : cells_) {
      delete cell;
    }
  } else {
    for (long unsigned i = 1; i < cells_.size()-1; ++i) {
      delete cells_[i];
    }
  }
}

/**
 * @brief Método que establece las condiciones de frontera.
 * 
 * @param tamagnio 
 * @param opcion 
 */
void Lattice::setBorder(int opcion) {
  // Añade dos células a los extremos del retículo.
  cells_.emplace(cells_.begin(), new Cell(0, (State)0));
  cells_.push_back(new Cell(cells_.size(), (State)0));
  // Establece las condiciones de frontera. 
  if (opcion == 3) { // Reflectora.
    cells_[0] = cells_[1];
    cells_[cells_.size()-1] = cells_[cells_.size()-2];
  } else if (opcion == 2) { // Periódica.
    cells_[0] = cells_[cells_.size()-2];
    cells_[cells_.size()-1] = cells_[1];
  } else if (opcion == 1) { // Abierta.
    cells_[0]->setState(ONE);
    cells_[cells_.size()-1]->setState(ONE);
  } else if (opcion == 0) { // Abierta.
    cells_[0]->setState(ZERO);
    cells_[cells_.size()-1]->setState(ZERO);
  }
}

/**
 * @brief Método que establece el vector de células.
 * 
 * @param cells 
 */
void Lattice::setVectorCells(const std::vector<Cell*>& cells) {
  // Libera la memoria de cada célula.
  for (auto cell : cells_) {
    delete cell;
  }
  // Establece el vector de células con el vector dado sumando 1 a la posición
  // La suma es necesaria pues añadiremos dos células a los extremos del retículo.
  for (unsigned i = 0; i < cells_.size(); ++i) {
    cells_[i] = new Cell(i+1, cells[i]->getState());
  }
}

/**
 * @brief Método que establece si el retículo es periódico.
 * 
 * @param is_periodic 
 */
void Lattice::setPeriodic(bool is_periodic) { is_periodic_ = is_periodic; }

/**
 * @brief Método que establece si el retículo es reflector.
 * 
 * @param is_reflector 
 */
void Lattice::setReflector(bool is_reflector) { is_reflector_ = is_reflector; }

/**
 * @brief Método que construye el retículo por defecto.
 * 
 * @param tamagnio 
 */
void Lattice::ConstructLattice(int tamagnio, int opcion) {
  // Construye el retículo por defecto.
  for (int i = 0; i < tamagnio; ++i) {
    delete cells_[i];
    // Si la posición es la mitad, la célula es 1, en caso contrario es 0.
    if (i == tamagnio/2) cells_[i] = new Cell(i+1, ONE);
    else cells_[i] = new Cell(i+1, ZERO);
  }
  // Establece las condiciones de frontera.
  this->setBorder(opcion);
}

/**
 * @brief Método que devuelve la célula de la posición dada.
 * 
 * @param pos 
 * @return const Cell&
 */
const Cell& Lattice::getCell(const Position& pos) const { return *cells_[pos]; }

/**
 * @brief Método que devuelve el vector de células.
 * 
 * @return const std::vector<Cell*>& 
 */
const std::vector<Cell*>& Lattice::getCells() const { return cells_; }

/**
 * @brief Método que devuelve si el retículo es periódico.
 * 
 * @return bool 
 */
bool Lattice::getPeriodic() const { return is_periodic_; }

/**
 * @brief Método que devuelve si el retículo es reflector.
 * 
 * @return bool 
 */
bool Lattice::getReflector() const { return is_reflector_; }

/**
 * @brief Método que devuelve la generación actual.
 * 
 * @return const Generation& 
 */
const Generation& Lattice::getGeneration() const { return gen_; }

/**
 * @brief Método que avanza una generación.
 * 
 */
void Lattice::nextGeneration() {
  // Calcula el estado siguiente de cada célula del retículo.
  for (long unsigned i = 1; i < cells_.size()-1; ++i) {
    cells_[i]->nextState(*this);
  }
  // Actualiza el estado de cada célula del retículo.
  for (long unsigned i = 1; i < cells_.size()-1; ++i) {
    cells_[i]->updateState();
  }

  ++gen_;
}

/**
 * @brief Método que muestra el retículo
 * 
 */
void Lattice::Show() {
  std::string input;
  while (true) {
    // Muestra el retículo.
    std::cout << *this << std::endl;
    // Avanza una generación.
    this->nextGeneration();
    // Captura la entrada del usuario
    std::getline(std::cin, input);
    // Sale del bucle si el usuario ingresa 'q' o 'Q' o 'quit' o 'Quit' o 'QUIT'
    if (input == "q" || input == "Q" || input == "quit" || input == "Quit" || input == "QUIT") {
      break;
    }
    // std::this_thread::sleep_for(100ms); // Espera 100ms antes de mostrar la siguiente generación
  }
  std::cout << "Simulación finalizada." << std::endl;
}

/**
 * @brief Sobrecarga del operador de salida para la clase Lattice
 * 
 * @param os 
 * @param lattice 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  // Muestra el retículo.
  for (long unsigned i = 1; i < lattice.getCells().size()-1; ++i) {
    os << *lattice.getCells()[i];
  }
  return os;
}