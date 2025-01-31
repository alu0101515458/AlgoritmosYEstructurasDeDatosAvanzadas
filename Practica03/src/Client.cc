#include <iostream>
#include "Lattice1D.h"
#include "Lattice2D.h"

/**
 * @brief Función que muestra el uso del programa.
 * 
 * @param argc 
 * @param argv 
 */
int Usage(int argc, char *argv[]) {
  bool dimFound = false;
  bool sizeFound = false;
  bool initFound = false;
  bool cellFound = false;
  bool borderFound = false;
  if (argc == 1) {
    std::cout << "No se han introducido argumentos." << std::endl;
    exit(EXIT_FAILURE);
  }
  // Recorremos los argumentos.
  // Comenzamos en 1 para omitir el nombre del programa.
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-h" || arg == "--help") {
      std::cout << "Opción 1:" << std::endl;
      std::cout << "Uso: ./program -dim <d> -size <N, <...>> -cell <t> -border <open [0|1]|reflective|periodic|noborder" << std::endl;
      std::cout << "Opción 2:" << std::endl;
      std::cout << "Uso: ./program -init <file> -cell <t> -border <open [0|1]|reflective|periodic|noborder" << std::endl;
      std::cout << "Opciones:" << std::endl;
      std::cout << "-dim <d>: d es la dimensión del autómata celular." << std::endl;
      std::cout << "-size <N, <...>>: N es el número de células para cada dimensión." << std::endl;
      std::cout << "-init <file>:(opcional) file es un nombre del fichero que contiene los valores" << std::endl;
      std::cout << "iniciales para el estado de las células del tablero. Si se especifica" << std::endl;
      std::cout << "no es necesario indicar los argumentos -dim y -size." << std::endl;
      std::cout << "-cell <t>: t indica uno de los tipos de célula implementadas en la jerarquía." << std::endl;
      std::cout << "Por ejemplo, t=Ace100 o t=Life23_3. Se utiliza para crear el" << std::endl;
      std::cout << "objeto Factory que se pasa al retículo para crear las células: Condiciones de frontera." << std::endl;
      std::cout << "-border <b> [v]: -border <b> [v] b=open v=[0|1]" << std::endl;
      std::cout << "b=reflective" << std::endl;
      std::cout << "b=periodic" << std::endl;
      std::cout << "b=noborder" << std::endl;
      exit(EXIT_SUCCESS);
    } else if (arg == "-size") {
      if (i + 3 >= argc) { // Asegurarse de que hay suficientes argumentos
        std::cout << "No se han introducido suficientes argumentos para '-size'." << std::endl;
        exit(EXIT_FAILURE);
      }
      int N = std::stoi(argv[i + 1]);
      if (N < 1 || N > 2) { // Verificamos que ambos números sean mayores que 0
        std::cout << "Los valores para '-size' deben ser mayores que 0." << std::endl;
        exit(EXIT_FAILURE);
      }
      for (int j = 0; j < N; ++j) {
        int M = std::stoi(argv[j + 2]);
        if (M < 1) {
          std::cout << "Los valores para '-size' deben ser mayores que 0. Error en: " << M << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      sizeFound = true;
      i += 3; // Avanzamos más allá de los argumentos numéricos
    } else if (arg == "-border") {
      if (i + 1 >= argc || (std::string(argv[i + 1]) != "reflective" && std::string(argv[i + 1]) != "noborder" && std::string(argv[i + 1]) != "periodic" && std::string(argv[i + 1]) != "open")) {
        std::cout << "No se ha introducido un tipo de frontera válido para '-border'." << std::endl;
        exit(EXIT_FAILURE);
      } else {
        if (std::string(argv[i + 1]) == "open" && (i + 2 >= argc || (std::string(argv[i + 2]) != "0" && std::string(argv[i + 2]) != "1"))) {
          std::cout << "No se ha introducido un valor para '-border open'." << std::endl;
          exit(EXIT_FAILURE);
        }
        borderFound = true;
        if (std::string(argv[i + 1]) == "open") {
          ++i;
        }
        ++i;
      }
    } else if (arg == "-init") {
      if (i + 1 >= argc) {
        std::cout << "No se ha introducido un fichero para '-init'." << std::endl;
        exit(EXIT_FAILURE);
      } else {
        initFound = true;
        ++i;
      }
    } else if (arg == "-cell") {
      if (i + 1 >= argc || (std::string(argv[i + 1]) != "Ace100" && std::string(argv[i + 1]) != "Life23_3" && std::string(argv[i + 1]) != "Life51_346" && std::string(argv[i + 1]) != "ACE30")){
        std::cout << "No se ha introducido un tipo de célula para '-cell'." << std::endl;
        exit(EXIT_FAILURE);
      } else {
        cellFound = true;
        ++i;
      }
    } else if (arg == "-dim") {
      if (i + 1 >= argc) {
        std::cout << "No se ha introducido un valor para '-dim'." << std::endl;
        exit(EXIT_FAILURE);
      }
      if (std::string(argv[i + 1]) != "1" && std::string(argv[i + 1]) != "2") {
        std::cout << "El valor para '-dim' debe ser 1 o 2." << std::endl;
        exit(EXIT_FAILURE);
      } else {
        dimFound = true;
        ++i;
      }
    }
  }
  if (sizeFound && borderFound && dimFound && cellFound && !initFound) {
    return 1;
  } else if (initFound && borderFound && cellFound && !sizeFound && !dimFound) {
    return 2;
  } else {
    std::cout << "Error en los argumentos." << std::endl;
    exit(EXIT_FAILURE);
  }
  return 0;
}

int main(int argc, char *argv[]) {
  int result = Usage(argc, argv);
  if (result == 1) {
    int dim = std::stoi(argv[2]);
    
  }
  return 0;
}