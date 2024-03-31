#include "../include/Lattice2D.h"

/**
 * @brief Construct a new Lattice2D::Lattice2D object
 * 
 * @param rows 
 * @param columns 
 */
Lattice2D::Lattice2D(int n, int m) : lattice_(n, std::vector<Cell*>(m, nullptr)) {
  n_ = n;
  m_ = m;
  std::vector<std::pair<int, int>> aliveCells = InitialAliveCells();
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < m; ++j) {
      Position* pos = new Position();
      if (std::find(aliveCells.begin(), aliveCells.end(), std::make_pair(i,j)) != aliveCells.end()) {
        if (CellLife23_3_) lattice_[i][j] = new CellLife23_3(, ALIVE); // Asigna una nueva instancia de Cell a cada elemento
        else if (CellLife51_346_) lattice_[i][j] = new CellLife51_346({i,j}, ALIVE); // Asigna una nueva instancia de Cell a cada elemento
      } else {
        if (CellLife23_3_) lattice_[i][j] = new CellLife23_3({i,j}, DEAD); // Asigna una nueva instancia de Cell a cada elemento
        else if (CellLife51_346_) lattice_[i][j] = new CellLife51_346({i,j}, DEAD); // Asigna una nueva instancia de Cell a cada elemento
      }
    }
  }
}

/**
 * @brief Constructor
 * 
 * @param filename 
 */
Lattice2D::Lattice2D(const char* filename) {
  std::ifstream file(filename);
  if (file.is_open()) {
    file >> n_ >> m_;
    lattice_.resize(n_); // Establece el tamaño de las filas (n)
    for(int i = 0; i < n_; ++i) {
      lattice_[i].resize(m_, nullptr); // Establece el número de columnas (m), inicialmente con nullptrs
      for(int j = 0; j < m_; ++j) {
        int state;
        file >> state;
        lattice_[i][j] = new Cell({i,j}, (State)state); // Asigna una nueva instancia de Cell a cada elemento
      }
    }
  }
  file.close();
}

/**
 * @brief Destructor de la clase Lattice2D
 * 
 */
Lattice2D::~Lattice2D() {
  for(int i = 0; i < n_; ++i) {
    for(int j = 0; j < m_; ++j) {
      delete lattice_[i][j];
    }
  }
}

/**
 * @brief Método que devuelve la célula en la posición dada.
 * 
 * @param pos 
 * @return const Cell& 
 */
const Cell& Lattice2D::getCell(const Position& pos) const {
  return *lattice_[pos.first][pos.second];
}

/**
 * @brief Método que devuelve el vector de células.
 * 
 * @return const std::vector<std::vector<Cell*>>& 
 */
const std::vector<std::vector<Cell*>>& Lattice2D::getCells() const {
  return lattice_;
}

/**
 * @brief Método que devuelve si el tablero tiene bordes o no.
 * 
 * @return bool 
 */
bool Lattice2D::getNoBorders() const {
  return noBorders_;
}

/**
 * @brief Método que devuelve si el tablero es reflectante o no.
 * 
 * @return bool 
 */
bool Lattice2D::getReflective() const {
  return reflective_;
}

/**
 * @brief Método que devuelve el número de filas.
 * 
 * @return int 
 */
int Lattice2D::getRows() const {
  return n_;
}

/**
 * @brief Método que devuelve el número de columnas.
 * 
 * @return int 
 */
int Lattice2D::getColumns() const {
  return m_;
}

/**
 * @brief Método que devuelve el número de células vivas.
 * 
 * @return int 
 */
int Lattice2D::getPopulation() const {
  int population = 0;
  for(int i = 0; i < n_; ++i) {
    for(int j = 0; j < m_; ++j) {
      if (lattice_[i][j]->getState() == ALIVE) {
        population++;
      }
    }
  }
  return population;
}

/**
 * @brief Método que establece si el tablero tiene bordes o no.
 * 
 * @param noBorders 
 */
void Lattice2D::setNoBorders(bool noBorders) {
  noBorders_ = noBorders;
}

/**
 * @brief Método que establece si el tablero es reflectante o no.
 * 
 * @param reflective 
 */
void Lattice2D::setReflective(bool reflective) {
  reflective_ = reflective;
}

/**
 * @brief Método que devuelve un vector con las células vivas iniciales.
 * 
 * @return std::vector<std::pair<int, int>> 
 */
std::vector<std::pair<int, int>> Lattice2D::InitialAliveCells() {
  std::vector<std::pair<int, int>> aliveCells;
  int i, j;
  while (std::cin >> i >> j) {
    aliveCells.push_back(std::make_pair(i,j));
  }
  return aliveCells;
}

/**
 * @brief Método que devuelve la célula en la posición dada.
 * 
 * @param pos 
 * @return const Cell& 
 */
const Cell& Lattice2D::operator[](Position& pos) const {
  return *lattice_[pos[0*]][pos[1]];
}