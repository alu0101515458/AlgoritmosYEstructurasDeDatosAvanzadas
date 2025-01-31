#include <iostream>
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
  // Recorremos los argumentos.
  // Comenzamos en 1 para omitir el nombre del programa.
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-h" || arg == "--help") {
      std::cout << "Opción 1:" << std::endl;
      std::cout << "Uso: ./program -size <n> <m> -border <reflective|noborder>" << std::endl;
      std::cout << "Opción 2:" << std::endl;
      std::cout << "Uso: ./program -init <fichero> -border <reflective|noborder>" << std::endl;
      std::cout << "Opciones:" << std::endl;
      std::cout << "-size <n> <m> : Tamaño del retículo." << std::endl;
      std::cout << "-border reflector|noborder: Condiciones de frontera." << std::endl;
      std::cout << "-init <fichero>: Fichero de inicialización con la configuración inicial de la matriz." << std::endl;
      exit(EXIT_SUCCESS);
    } else if (arg == "-size") {
      if (i + 2 >= argc) { // Asegurarse de que hay suficientes argumentos
        std::cout << "No se han introducido suficientes argumentos para '-size'." << std::endl;
        exit(EXIT_FAILURE);
      } try {
        int N = std::stoi(argv[i + 1]);
        int M = std::stoi(argv[i + 2]);
        if (N <= 0 || M <= 0) { // Verificamos que ambos números sean mayores que 0
          std::cout << "Los valores para '-size' deben ser mayores que 0." << std::endl;
          exit(EXIT_FAILURE);
        }
        sizeFound = true;
        i += 2; // Avanzamos más allá de los argumentos numéricos
      } catch (const std::invalid_argument& ia) {
        std::cout << "Uno o ambos valores para '-size' no son números válidos." << std::endl;
        exit(EXIT_FAILURE);
      } catch (const std::out_of_range& oor) {
        std::cout << "Uno o ambos valores para '-size' están fuera de rango." << std::endl;
        exit(EXIT_FAILURE);
      }
    } else if (arg == "-border") {
      if (i + 1 >= argc || (std::string(argv[i + 1]) != "reflective" && std::string(argv[i + 1]) != "noborder")) {
        std::cout << "No se ha introducido un tipo de frontera válido para '-border'." << std::endl;
        exit(EXIT_FAILURE);
      } else {
        borderFound = true;
        ++i;
      }
    } else if (arg == "-init") {
      if (i + 1 >= argc) {
        std::cout << "No se ha introducido un fichero para '-init'." << std::endl;
        exit(EXIT_FAILURE);
      } else {
        ++i;
      }
    }
  }
  if (argc == 6) {
    if (!sizeFound || !borderFound) {
      std::cout << "Faltan argumentos obligatorios." << std::endl;
      exit(EXIT_FAILURE);
    }
  } else if (argc == 5) {
    if (!borderFound) {
      std::cout << "Faltan argumentos obligatorios." << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

int main(int argc, char *argv[]) {
  // Comprobamos que los argumentos sean válidos.
  Usage(argc, argv);
  if (argc < 5) {
    std::cout << "No se han introducido suficientes argumentos." << std::endl;
    exit(EXIT_FAILURE);
  }
  // Si argc es 5 contiene: './program -init <fichero> -border reflective/noborder'
  if (argc == 5) {
    Lattice lattice(argv[2]);
    if ((std::string)argv[4] == "reflective") {
      lattice.setReflective(true);
    } else if ((std::string)argv[4] == "noborder") {
      lattice.setNoBorders(true);
    } else {
      std::cout << argv[4] << " es una opción no válida." << std::endl;
      exit(EXIT_FAILURE);
    }
    lattice.setBorder();
    lattice.Show();
  }
  // Si argc es 6 contiene: './program -size <n> <m> -border reflective/noborder'
  if (argc == 6) {
    Lattice lattice(atoi(argv[2]), atoi(argv[3]));
    if ((std::string)argv[5] == "reflective") {
      lattice.setReflective(true);
    } else if ((std::string)argv[5] == "noborder") {
      lattice.setNoBorders(true);
    } else {
      std::cout << argv[5] << " es una opción no válida." << std::endl;
      exit(EXIT_FAILURE);
    }
    lattice.setBorder();
    lattice.Show();
  }
  return 0;
}