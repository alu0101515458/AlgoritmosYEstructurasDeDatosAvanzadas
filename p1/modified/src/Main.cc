#include <iostream>
#include <fstream>
#include <string>
#include "../include/Cell.h"
#include "../include/Lattice.h"

/**
 * @brief Función que muestra el uso del programa.
 * 
 * @param argc 
 * @param argv 
 */
void Usage(int argc, char *argv[]) {
  bool sizeFound = false;
  bool borderFound = false;
  if (argc == 1) {
    std::cout << "No se han introducido argumentos." << std::endl;
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < argc; ++i) { // Comenzamos en 1 para omitir el nombre del programa
    std::string arg = argv[i];
    if (arg == "-h" || arg == "--help") {
      std::cout << "Uso: ./program -size <n> -border <periodic|open [0|1]> -init <fichero>" << std::endl;
      std::cout << "Opciones:" << std::endl;
      std::cout << "-size <n> : Tamaño del retículo. NECESARIO" << std::endl;
      std::cout << "-border reflector|periodic|open [0|1] : Condiciones de frontera. NECESARIO" << std::endl;
      std::cout << "-init <fichero> : Fichero de inicialización. NO ES NECESARIO" << std::endl;
      exit(EXIT_SUCCESS);
    } else if (arg == "-size") {
      if (i + 1 >= argc || std::stoi(argv[i + 1]) <= 0) {
        std::cout << "No se ha introducido un tamaño válido para '-size'." << std::endl;
        exit(EXIT_FAILURE);
      } else {
        sizeFound = true;
        ++i; // Saltamos el valor de este argumento
      }
    } else if (arg == "-border") {
      if (i + 1 >= argc || (std::string(argv[i + 1]) != "periodic" && std::string(argv[i + 1]) != "open" && std::string(argv[i+1]) != "reflector")) {
        std::cout << "No se ha introducido un tipo de frontera válido para '-border'." << std::endl;
        exit(EXIT_FAILURE);
      } else {
        borderFound = true;
        ++i; // Saltamos el valor de este argumento
      }
    } else if (arg == "-init") {
      if (i + 1 >= argc) {
        std::cout << "No se ha introducido un fichero para '-init'." << std::endl;
        exit(EXIT_FAILURE);
      } else {
        ++i; // Saltamos el valor de este argumento
      }
    }
  }
  if (!sizeFound || !borderFound) {
    std::cout << "Faltan argumentos obligatorios." << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Función que procesa el fichero de inicialización.
 * 
 * @param filename 
 * @param lattice 
 * @param expectedSize 
 * @param opcion 
 * @return int 
 */
int processInitFile(const char* filename, Lattice& lattice, unsigned expectedSize, int opcion) {
  // Abrimos el fichero.
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "El fichero no se ha podido abrir." << std::endl;
    exit(EXIT_FAILURE);
  }
  // Leemos el fichero y comprobamos si está vacío.
  std::string line;
  std::getline(file, line);
  if (line.empty()) {
    std::cout << "El fichero está vacío, procedemos con la construcción por defecto." << std::endl;
    return 1;
  }
  // Convertimos el contenido del fichero en un vector de enteros.
  std::vector<int> aux;
  for (char digit : line) {
    if (isdigit(digit)) {
      aux.push_back(digit - '0');
    }
  }
  // Comprobamos que el tamaño del retículo sea el mismo que el del fichero.
  if (aux.size() != expectedSize) {
    std::cout << "El tamaño del retículo no coincide con el tamaño del fichero." << std::endl;
    exit(EXIT_FAILURE);
  }
  // Creamos un vector de células con el contenido del fichero.
  std::vector<Cell*> cells(aux.size());
  for (unsigned int i = 0; i < cells.size(); ++i) {
    cells[i] = new Cell(i, (State)aux[i]);
  }
  // Establecemos el vector de células.
  lattice.setVectorCells(cells);
  // Liberamos la memoria de las células.
  for (unsigned i = 0; i < cells.size(); ++i) {
    delete cells[i];
  }
  // Establecemos las condiciones de frontera.
  lattice.setBorder(opcion);
  return 0;
}

int main(int argc, char *argv[]) {
  // Comprobamos que los argumentos sean válidos.
  Usage(argc, argv);
  Lattice lattice(atoi(argv[2]));
  // Si argc es 5 contiene: './program -size <n> -border periodic/open/reflector'
  if (argc == 5) {
    // Si el usuario introduce 'periodic' como frontera, se establece como verdadero y se construye el retículo.
    if ((std::string)argv[4] == "periodic") {
      lattice.setPeriodic(true);
      lattice.ConstructLattice(atoi(argv[2]), 2);
    } else if ((std::string)argv[4] == "open") { // Si el usuario introduce 'open' como frontera, se construye el retículo por defecto.
      std::cout << argv[4] << " no tiene estados de frontera asignados." << std::endl;
      std::cout << "Procedemos con la construcción por defecto (0)." << std::endl;
      lattice.ConstructLattice(atoi(argv[2]), 0);
    } else if ((std::string)argv[4] == "reflector") { // Si el usuario introduce 'periodic' como frontera, se establece como verdadero y se construye el retículo.
      lattice.setReflector(true);
      lattice.ConstructLattice(atoi(argv[2]), 3);
    } else {
      std::cout << argv[4] << " es una opción no válida." << std::endl;
      exit(EXIT_FAILURE);
    }
  } else if (argc == 6) { // Si argc es 6 contiene: './program -size <n> -border open [0|1]'
    // Si el usuario introduce 'open' como frontera.
    if ((std::string)argv[4] == "open") {
      // Si no se introduce un estado válido, se muestra un mensaje de error.
      if (atoi(argv[5]) != 0 && atoi(argv[5]) != 1) {
        std::cout << argv[5] << " es un estado no válido." << std::endl;
        exit(EXIT_FAILURE);
      }
      lattice.ConstructLattice(atoi(argv[2]), atoi(argv[5]));
    }
  } else if (argc == 7) { // Si argc es 7 contiene: './program -size <n> -border reflector/periodic/open -init <fichero>'
    // Si el usuario introduce 'periodic' como frontera, se establece como verdadero.
    if ((std::string)argv[4] == "periodic") {
      lattice.setPeriodic(true);
      // Si el usuario introduce '-init' como parámetro, se procesa el fichero.
      if ((std::string)argv[5] == "-init") {
        // Si el fichero está vacío, procedemos con la construcción por defecto.
        if (processInitFile(argv[6], lattice, std::stoul(argv[2]), 2) == 1) {
          lattice.ConstructLattice(atoi(argv[2]), 2);
        }
      } else {
        std::cout << "No se ha introducido correctamente el parámetro -init." << std::endl;
        exit(EXIT_FAILURE);
      }
    } else if ((std::string)argv[4] == "open") { // Si el usuario introduce 'open' como frontera.
      // Si el usuario introduce '-init' como parámetro, se procesa el fichero.
      if ((std::string)argv[5] == "-init") {
        // Si el fichero está vacío, procedemos con la construcción por defecto.
        if (processInitFile(argv[6], lattice, std::stoul(argv[2]), 0) == 1) {
          lattice.ConstructLattice(atoi(argv[2]), 0);
        }
      } else {
        std::cout << "No se ha introducido correctamente el parámetro -init." << std::endl;
        exit(EXIT_FAILURE);
      }
    } else if ((std::string)argv[4] == "reflector") { // Si el usuario introduce 'reflector' como frontera, se establece como verdadero.
      lattice.setReflector(true);
      // Si el usuario introduce '-init' como parámetro, se procesa el fichero.
      if ((std::string)argv[5] == "-init") {
        // Si el fichero está vacío, procedemos con la construcción por defecto.
        if (processInitFile(argv[6], lattice, std::stoul(argv[2]), 3) == 1) {
          lattice.ConstructLattice(atoi(argv[2]), 3);
        }
      } else {
        std::cout << "No se ha introducido correctamente el parámetro -init." << std::endl;
        exit(EXIT_FAILURE);
      }
    } else {
      std::cout << argv[4] << " es una opción no válida." << std::endl;
      exit(EXIT_FAILURE);
    }
  } else if (argc == 8) { // Si argc es 8 contiene: ./program -size <n> -border open [0|1] -init <fichero>
    // Si el usuario introduce 'open' como frontera.
    if ((std::string)argv[4] == "open") {
      // Si no se introduce un estado válido, se muestra un mensaje de error.
      if (atoi(argv[5]) != 0 && atoi(argv[5]) != 1) {
        std::cout << argv[5] << " es un estado no válido." << std::endl;
        exit(EXIT_FAILURE);
      }
      // Si el usuario introduce '-init' como parámetro, se procesa el fichero.
      if ((std::string)argv[6] == "-init") {
        // Si el fichero está vacío, procedemos con la construcción por defecto.
        if (processInitFile(argv[7], lattice, std::stoul(argv[2]), atoi(argv[5])) == 1) {
          lattice.ConstructLattice(atoi(argv[2]), atoi(argv[5]));
        }
      } else {
        std::cout << "No se ha introducido correctamente el parámetro -init." << std::endl;
        exit(EXIT_FAILURE);
      }
    } else {
      std::cout << argv[4] << " es una opción no válida." << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  // MOSTRAMOS EL RETÍCULO Y SUS SUCESIVAS GENERACIONES
  lattice.Show();
  return 0;
}