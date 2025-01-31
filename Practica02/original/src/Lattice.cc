#include "../include/Lattice.h"

/**
* @brief Método que establece las condiciones de frontera.
 * 
 * @param tamagnio 
 * @param opcion 
 */
void Lattice::setBorder() {
  if (getReflective()) {
    // Creamos un vector de celdas temporales para las celdas de los bordes
    std::vector<Cell*> temp(n_+2, nullptr);
    // Asignamos la primera fila con celdas muertas
    for (int i = 0; i < n_+2; ++i) {
      temp[i] = new Cell({0, i}, DEAD);
    }
    // Añadimos las celdas temporales al principio del vector de celdas
    lattice_.insert(lattice_.begin(), temp);
    // Asignamos la última fila con celdas muertas
    for (int i = 0; i < n_+2; ++i) {
      temp[i]->setPosition({n_+1, i});
    }
    // Añaadimos las celdas temporales al final del vector de celdas
    lattice_.push_back(temp);
    ++n_;
    ++n_;

    // Recorremos la matriz original y asignamos a los bordes las celdas reflejadas
    for (int i = 1; i < n_-1; ++i) {
      // Añadimos una nueva celda al principio de la fila
      lattice_[i].insert(lattice_[i].begin(), new Cell({i,0}, DEAD));
      // Añadimos una nueva celda al final de la fila
      lattice_[i].push_back(new Cell({i,m_+1}, DEAD));
    }
    ++m_;
    ++m_;
    for (int i = 1; i < n_-1; ++i) {
      for (int j = 1; j < m_-1; ++j) {
        lattice_[i][j]->setPosition({i,j});
      }
    }
    // Asignamos esquina superior izquierda
    lattice_[0][0] = lattice_[1][1];
    // Asignamos esquina inferior izquierda
    lattice_[n_-1][0] = lattice_[n_-2][1];
    // Asignamos esquina superior derecha
    lattice_[0][m_-1] = lattice_[1][m_-2];
    // Asignamos esquina inferior derecha
    lattice_[n_-1][m_-1] = lattice_[n_-2][m_-2];
    // Bucle para asignar los bordes superiores e inferiores
    for (int i = 1; i < m_-1; ++i) {
      lattice_[0][i] = lattice_[1][i];
      lattice_[n_-1][i] = lattice_[n_-2][i];
    }
    // Bucle para asignar los bordes izquierdos y derechos
    for (int i = 1; i < n_-1; ++i) {
      lattice_[i][0] = lattice_[i][1];
      lattice_[i][m_-1] = lattice_[i][m_-2];
    }
  } else if (getNoBorders()) {
    for (int i = 0; i < n_; ++i) {
      for (int j = 0; j < m_; ++j) {
        // Si la celda está viva
        if (lattice_[i][j]->getState() == ALIVE) {
          if (i == 0 && j == 0) { // Esquina superior izquierda
            // Creamos un vector de celdas temporales para las celdas de los bordes
            std::vector<Cell*> temp(m_+1, nullptr);
            // Asignamos la primera fila con celdas muertas
            for (int k = 0; k < m_+1; ++k) {
              temp[k] = new Cell({0, k}, DEAD);
            }
            // Añadimos las celdas temporales al principio del vector de celdas
            lattice_.insert(lattice_.begin(), temp);
            ++n_;
            // Añadimos una nueva columna al principio de cada fila
            for (int k = 1; k < n_; ++k) {
              lattice_[k].insert(lattice_[k].begin(), new Cell({k,0}, DEAD));
            }
            ++m_;
            for (int k = 0; k < n_; ++k) {
              for (int l = 0; l < m_; ++l) {
                lattice_[k][l]->setPosition({k,l});
              }
            }
          } else if (i == n_-1 && j == 0) { // Esquina inferior izquierda
            // Añadimos una nueva fila de celdas al final del vector de celdas
            std::vector<Cell*> temp(m_+1, nullptr);
            // Asignamos la primera fila con celdas muertas
            for (int k = 0; k < m_+1; ++k) {
              temp[k] = new Cell({0, k}, DEAD);
            }
            // Añadimos las celdas temporales al principio del vector de celdas
            lattice_.push_back(temp);
            ++n_;
            // Añadimos una nueva columna al principio de cada fila
            for (int k = 0; k < n_-1; ++k) {
              lattice_[k].insert(lattice_[k].begin(), new Cell({k,0}, DEAD));
            } 
            ++m_;
            for (int k = 0; k < n_; ++k) {
              for (int l = 0; l < m_; ++l) {
                lattice_[k][l]->setPosition({k,l});
              }
            }
          } else if (i == 0 && j == m_-1) { // Esquina superior derecha
            // Añadimos una nueva fila de celdas al principio del vector de celdas
            std::vector<Cell*> temp(m_+1, nullptr);
            // Asignamos la primera fila con celdas muertas
            for (int k = 0; k < m_+1; ++k) {
              temp[k] = new Cell({0, k}, DEAD);
            }
            // Añadimos las celdas temporales al principio del vector de celdas
            lattice_.insert(lattice_.begin(), temp);
            ++n_;
            // Añadimos una nueva columna al final de cada fila
            for (int k = 1; k < n_; ++k) {
              lattice_[k].push_back(new Cell({k,m_}, DEAD));
            }
            ++m_;
            for (int k = 0; k < n_; ++k) {
              for (int l = 0; l < m_; ++l) {
                lattice_[k][l]->setPosition({k,l});
              }
            }
          } else if (i == n_-1 && j == m_-1) { // Esquina inferior derecha
            // Añadimos una nueva fila de celdas al final del vector de celdas
            std::vector<Cell*> temp(m_+1, nullptr);
            // Asignamos la primera fila con celdas muertas
            for (int k = 0; k < m_+1; ++k) {
              temp[k] = new Cell({n_+1, k}, DEAD);
            }
            // Añadimos las celdas temporales al principio del vector de celdas
            lattice_.push_back(temp);
            ++n_;
            // Añadimos una nueva columna al final de cada fila
            for (int k = 0; k < n_-1; ++k) {
              lattice_[k].push_back(new Cell({k,m_}, DEAD));
            }
            ++m_;
            for (int k = 0; k < n_; ++k) {
              for (int l = 0; l < m_; ++l) {
                lattice_[k][l]->setPosition({k,l});
              }
            }
          } else {
            if (i == 0) { // Borde superior
              // Añadimos una nueva fila de celdas al principio del vector de celdas
              std::vector<Cell*> temp(m_, nullptr);
              // Asignamos la primera fila con celdas muertas
              for (int k = 0; k < m_; ++k) {
                temp[k] = new Cell({0, k}, DEAD);
              }
              // Añadimos las celdas temporales al principio del vector de celdas
              lattice_.insert(lattice_.begin(), temp);
              ++n_;
              for (int k = 0; k < n_; ++k) {
                for (int l = 0; l < m_; ++l) {
                  lattice_[k][l]->setPosition({k,l});
                }
              }
            } else if (i == n_-1) { // Borde inferior
              // Añadimos una nueva fila de celdas al final del vector de celdas
              std::vector<Cell*> temp(m_, nullptr);
              // Asignamos la primera fila con celdas muertas
              for (int k = 0; k < m_; ++k) {
                temp[k] = new Cell({n_, k}, DEAD);
              }
              // Añadimos las celdas temporales al principio del vector de celdas
              lattice_.push_back(temp);
              ++n_;
              for (int k = 0; k < n_; ++k) {
                for (int l = 0; l < m_; ++l) {
                  lattice_[k][l]->setPosition({k,l});
                }
              }
            } else if (j == 0) { // Borde izquierdo
              // Añadimos una nueva columna al principio de cada fila
              for (int k = 0; k < n_; ++k) {
                lattice_[k].insert(lattice_[k].begin(), new Cell({k,0}, DEAD));
              }
              ++m_;
              for (int k = 0; k < n_; ++k) {
                for (int l = 0; l < m_; ++l) {
                  lattice_[k][l]->setPosition({k,l});
                }
              }
            } else if (j == m_-1) { // Borde derecho
              // Añadimos una nueva columna al final de cada fila
              for (int k = 0; k < n_; ++k) {
                lattice_[k].push_back(new Cell({k,m_}, DEAD));
              }
              ++m_;
              for (int k = 0; k < n_; ++k) {
                for (int l = 0; l < m_; ++l) {
                  lattice_[k][l]->setPosition({k,l});
                }
              }
            }
          }
        }
      }
    }
  }
}

/**
 * @brief Método que devuelve las células vivas iniciales.
 * 
 * @return std::vector<std::pair<int, int>> 
 */
std::vector<std::pair<int, int>> Lattice::InitialAliveCells() {
  std::vector<std::pair<int, int>> aliveCells;
  std::pair<int, int> pos;
  std::string input_ij, input = "s";
  std::cout << "¿Qué células están vivas?" << std::endl;
  while (input != "x") {
    if (input != "s") {
      std::cout << "No se ha introducido una opción válida." << std::endl;
      std::cout << "Construimos la matriz con las células vivas que tenemos." << std::endl;
      break;
    }
    std::cout << "Introduce la posición de la célula viva: " << std::endl;
    std::cout << "Fila: ";
    std::cin >> input_ij;
    if (std::stoi(input_ij) <= 0 || std::stoi(input_ij) > n_) {
      std::cout << "El valor introducido " << input_ij << " no es válido." << std::endl;
      exit(EXIT_FAILURE);
    } else {
      pos.first = std::stoi(input_ij)-1;
      std::cout << "Columna: ";
      std::cin >> input_ij;
      if (std::stoi(input_ij) <= 0 || std::stoi(input_ij) > m_) {
        std::cout << "El valor introducido no es válido." << std::endl;
      } else {
        pos.second = std::stoi(input_ij)-1;
        if (std::find(aliveCells.begin(), aliveCells.end(), pos) != aliveCells.end()) {
          std::cout << "La celda ya está viva." << std::endl;
        } else {
          aliveCells.push_back(pos);
        }
      }
    }
    std::cout << "¿Quieres introducir otra célula viva? (x para salir/s para seguir): ";
    std::cin >> input;
  }
  return aliveCells;
}

/**
 * @brief Constructor de la clase Lattice a partir de un tamaño n y m.
 * 
 * @param n
 * @param m
 * 
 */
Lattice::Lattice(int n, int m) {
  n_ = n;
  m_ = m;
  std::vector<std::pair<int, int>> aliveCells = InitialAliveCells();
  lattice_.resize(n); // Establece el tamaño de las filas (n)
  for(int i = 0; i < n; ++i) {
    lattice_[i].resize(m, nullptr); // Establece el número de columnas (m), inicialmente con nullptrs
    for(int j = 0; j < m; ++j) {
      if (std::find(aliveCells.begin(), aliveCells.end(), std::make_pair(i,j)) != aliveCells.end()) {
        lattice_[i][j] = new Cell({i,j}, ALIVE); // Asigna una nueva instancia de Cell a cada elemento
      } else {
        lattice_[i][j] = new Cell({i,j}, DEAD); // Asigna una nueva instancia de Cell a cada elemento
      }
    }
  }
}

/**
 * @brief Constructor de la clase Lattice a partir de un archivo de texto.
 * 
 * @param filename 
 */
Lattice::Lattice(const char* filename) {
  // Abre el archivo.
  std::ifstream file(filename);
  // Lanza una excepción si no se pudo abrir el archivo.
  if (!file.is_open()) {
    throw std::runtime_error("No se pudo abrir el archivo.");
  }
  // Lee la primera línea del archivo.
  std::string line;
  std::getline(file, line);
  // Lanza una excepción si el archivo está vacío.
  if (line.empty()) {
    throw std::runtime_error("El archivo está vacío, no se puede inicializar el retículo.");
  }
  // Inicialización preliminar del tamaño de las columnas basado en la primera línea leída
  m_ = std::count_if(line.begin(), line.end(), isdigit);
  // Instancia un vector de vectores de Cell para almacenar las celdas leídas
  std::vector<std::vector<Cell*>> tempCells;
  // Inicializamos el número de fila a 0
  int row = 0, col = 0;
  do {
    std::vector<Cell*> rowCells;
    // Itera sobre cada dígito de la línea leída
    for (char digit : line) {
      // Si el dígito es un número, crea una nueva celda y la añade al vector de celdas de la fila
      if (isdigit(digit)) {
        // Convierte el dígito a un entero
        int state = digit - '0';
        rowCells.push_back(new Cell({row, col}, (State)state));
        ++col;
      }
    }
    // Lanza una excepción si el número de celdas leídas en la fila no coincide con el número de columnas
    if (rowCells.size() != (long unsigned)m_) {
      std::cout << "Problema en la fila " << row << ".\n";
      throw std::runtime_error("Inconsistencia en el tamaño de las filas.");
    }
    // Añade el vector de celdas de la fila al vector de vectores de celdas
    tempCells.push_back(rowCells);
    ++row;
    col = 0;
  } while (std::getline(file, line));
  // Establece el número total de filas leídas
  n_ = row;
  // Establece el vector de vectores de celdas como el vector de celdas del retículo
  lattice_ = tempCells;
  // Cierra el archivo
  file.close();
}

/**
 * @brief Destructor de la clase Lattice.
 * 
 */
Lattice::~Lattice() {
  std::set<Cell*> deletedCells;
  for (int i = 0; i < n_; ++i) {
    for (int j = 0; j < m_; ++j) {
      if (deletedCells.find(lattice_[i][j]) == deletedCells.end()) {
        delete lattice_[i][j];
        deletedCells.insert(lattice_[i][j]);
      }
    }
  }
}

/**
 * @brief Método que establece que el retículo no tiene fronteras.
 * 
 * @param is_periodic 
 */
void Lattice::setNoBorders(bool noborders) { noborders_ = noborders; }

/**
 * @brief Método que establece que el retículo es reflector.
 * 
 * @param is_reflector 
 */
void Lattice::setReflective(bool is_reflective) { is_reflective_ = is_reflective; }

/**
 * @brief Método que devuelve la célula de la posición dada.
 * 
 * @param pos 
 * @return const Cell&
 */
const Cell& Lattice::getCell(const Position& pos) const { return (*this)[pos]; }

/**
 * @brief Método que devuelve el vector de células.
 * 
 * @return const std::vector<Cell*>& 
 */
const std::vector<std::vector<Cell*>>& Lattice::getCells() const { return lattice_; }

/**
 * @brief Método que devuelve si el retículo no tiene fronteras.
 * 
 * @return bool 
 */
bool Lattice::getNoBorders() const { return noborders_; }

/**
 * @brief Método que devuelve si el retículo es reflector.
 * 
 * @return bool 
 */
bool Lattice::getReflective() const { return is_reflective_; }

/**
 * @brief Método que devuelve la longitud de las filas.
 * 
 * @return bool 
 */
int Lattice::getRows() const { return n_; }

/**
 * @brief Método que devuelve la longitud de las columnas.
 * 
 * @return bool 
 */
int Lattice::getColumns() const { return m_; }

/**
 * @brief Método que devuelve la generación actual.
 * 
 * @return const Generation& 
 */
const Generation& Lattice::getGeneration() const { return gen_; }

/**
 * @brief Método que devuelve el número de células vivas.
 * 
 * @return const int 
 */
int Lattice::getPopulation() const {
  int population = 0;
  for (int i = 1; i < n_-1; ++i) {
    for (int j = 1; j < m_-1; ++j) {
      if (lattice_[i][j]->getState() == ALIVE) {
        ++population;
      }
    }
  }
  return population;
}

/**
 * @brief Método que avanza una generación.
 * 
 */
void Lattice::nextGeneration() {
  // Calcula el estado siguiente de cada célula del retículo.
  for (int i = 1; i < n_-1; ++i) {
    for (int j = 1; j < m_-1; ++j) {
      lattice_[i][j]->nextState(*this);
    }
  }
  // Actualiza el estado de cada célula del retículo.
  for (int i = 1; i < n_-1; ++i) {
    for (int j = 1; j < m_-1; ++j) {
      lattice_[i][j]->updateState();
    }
  }
  ++gen_;
}

/**
 * @brief Método que muestra el retículo
 * 
 */
void Lattice::Show() {
  // Muestra el retículo inicial.
  std::cout << "Retículo inicial: \n";
  std::cout << *this << std::endl;
  std::string input;
  bool show_population = false;
  while (true) {
    // Captura la entrada del usuario
    std::getline(std::cin, input);
    if (input == "x") {
      break;
    } else if (input == "n") {
      if (show_population) {
        this->nextGeneration();
        if (noborders_) this->setBorder();
        std::cout << "Número de células vivas: " << this->getPopulation() << std::endl;
      } else {
        std::cout << "Mostrando el estado del tablero." << std::endl;
        // Avanza una generación.
        this->nextGeneration();
        if (noborders_) this->setBorder();
        // Muestra el retículo.
        std::cout << *this << std::endl;
      }
    } else if (input == "L") {
      for (int i = 0; i < 5; ++i) {
        // Avanza una generación.
        this->nextGeneration();
        if (noborders_) this->setBorder();
        std::cout << "Número de células vivas: " << this->getPopulation() << std::endl;
      }
      if (show_population) {
        this->nextGeneration();
        if (noborders_) this->setBorder();
        std::cout << "Número de células vivas: " << this->getPopulation() << std::endl;
      } else {
        std::cout << "Mostrando las siguientes 5 generaciones" << std::endl;
        for (int i = 0; i < 5; ++i) {
          // Avanza una generación.
          this->nextGeneration();
          if (noborders_) this->setBorder();
          // Muestra el retículo.
          std::cout << *this << std::endl;
        }
      std::cout << "Generaciones calculadas." << std::endl;
      }
    } else if (input == "c") {
      if (!show_population) {
        std::cout << "'n' y 'L' mostrarán el número de células vivas en lugar del estado del tablero." << std::endl;
        show_population = true;
      } else {
        std::cout << "'n' y 'L' mostrarán el estado del tablero." << std::endl;
        show_population = false;
      }
    } else if (input == "s") {
      std::cout << "Salvando el tablero en un fichero adicional." << std::endl;
      std::ofstream file("salida.txt");
      file << *this;
      file.close();
      break;
    }
  }
  std::cout << "Simulación finalizada." << std::endl;
}

/**
 * @brief Sobrecarga del operador de acceso para la clase Lattice
 * 
 * @param pos 
 * @return Cell& 
 */
const Cell& Lattice::operator[](const Position& pos) const { return *lattice_[pos.first][pos.second]; }
Cell& Lattice::operator[](const Position& pos) { return *lattice_[pos.first][pos.second]; }

/**
 * @brief Sobrecarga del operador de salida para la clase Lattice
 * 
 * @param os 
 * @param lattice 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  if (lattice.getReflective()) {
    for (int i = 1; i < lattice.getRows()-1; ++i) {
    for (int j = 1; j < lattice.getColumns()-1; ++j) {
      os << lattice[{i,j}];
    }
    os << std::endl;
    }
    return os;
  } else if (lattice.getNoBorders()) {
    for (int i = 0; i < lattice.getRows(); ++i) {
      for (int j = 0; j < lattice.getColumns(); ++j) {
        os << lattice[{i,j}];
      }
      os << std::endl;
    }
  }
  return os;
}