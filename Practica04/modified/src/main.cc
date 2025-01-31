#include "../include/dispersionfunction.h"
#include "../include/explorationfunction.h"
#include "../include/hashtable.h"
#include "../include/nif.h"
#include "../include/sequence.h"
#include <iostream>

/**
 * @brief Función que muestra el uso del programa.
 * 
 * @param argc Número de argumentos.
 * @param argv Argumentos.
 */
void Usage(int argc, char *argv[]) {
  // Comprobamos que el segundo argumento sea -h o --help
  if (argc == 2 && ((std::string)argv[1] == "-h" || (std::string)argv[1] == "--help")) {
    std::cout << "Uso:" << argv[0] << " -ts <s> -fd <f> -hash <open|close> [-bs <s> -fe <f>]" << std::endl;
    std::cout << "Donde:" << std::endl;
    std::cout << "  -ts <s>: Tamaño de la tabla." << std::endl;
    std::cout << "  -fd <f>: Código que identifica a una función de dispersión." << std::endl;
    std::cout << "  -hash <open|close>: Técnica de dispersión a utilizar." << std::endl;
    std::cout << "  -bs <s>: Tamaño del bloque. Sólo para dispersión cerrada." << std::endl;
    std::cout << "  -fe <f>: Código que identifica a una función de exploración. Sólo para dispersión cerrada." << std::endl;
    exit(EXIT_SUCCESS);
  }
  // Comprobamos que el número de argumentos sean 11 (dispersión cerrada) o 7 (dispersión abierta)
  if ((argc != 13 && (std::string)argv[6] == "close") || (argc != 7 && (std::string)argv[6] == "open")) {
    std::cerr << "Número de argumentos incorrecto." << std::endl;
    std::cerr << "Use " << argv[0] << " -h para más información." << std::endl;
    exit(EXIT_FAILURE);
  }
  // Comprobamos que existen los argumentos necesarios
  if ((std::string)argv[1] != "-ts" || (std::string)argv[3] != "-fd" || (std::string)argv[5] != "-hash") {
    std::cerr << "Argumentos incorrectos." << std::endl;
    std::cerr << "Use " << argv[0] << " -h para más información." << std::endl;
    exit(EXIT_FAILURE);
  }
  // Comprobamos que el tamaño de la tabla es un número mayor que 0
  if (std::stoi(argv[2]) <= 0) {
    std::cerr << "Tamaño de la tabla incorrecto." << std::endl;
    std::cerr << "Use " << argv[0] << " -h para más información." << std::endl;
    exit(EXIT_FAILURE);
  }
  // Comprobamos que el código de la función de dispersión es "module", "sum" o "pseudo"
  if ((std::string)argv[4] != "module" && (std::string)argv[4] != "sum" && (std::string)argv[4] != "pseudo") {
    std::cerr << "Código de la función de dispersión incorrecto." << std::endl;
    std::cerr << "Use " << argv[0] << " -h para más información." << std::endl;
    exit(EXIT_FAILURE);
  }
  // Comprobamos el parámetro hash
  if ((std::string)argv[5] != "-hash") {
    std::cerr << "Argumento " << argv[5] << " incorrecto." << std::endl;
    std::cerr << "Use " << argv[0] << " -h para más información." << std::endl;
    exit(EXIT_FAILURE);
  }
  // Comprobamos que el código hash es "open" o "close"
  if ((std::string)argv[6] != "open" && (std::string)argv[6] != "close") {
    std::cerr << "Técnica de dispersión incorrecta." << std::endl;
    std::cerr << "Use " << argv[0] << " -h para más información." << std::endl;
    exit(EXIT_FAILURE);
  }
  // Comprobamos el caso de dispersión cerrada
  if (argc == 12) {
    // Comprobamos que existen los argumentos necesarios
    if ((std::string)argv[7] != "-bs" || (std::string)argv[9] != "-fe") {
      std::cerr << "Argumentos incorrectos." << std::endl;
      std::cerr << "Use " << argv[0] << " -h para más información." << std::endl;
      exit(EXIT_FAILURE);
    }
    // Comprobamos que el tamaño del bloque es un número mayor que 0
    if (std::stoi(argv[8]) <= 0) {
      std::cerr << "Tamaño del bloque incorrecto." << std::endl;
      std::cerr << "Use " << argv[0] << " -h para más información." << std::endl;
      exit(EXIT_FAILURE);
    }
    // Comprobamos que el código de la función de exploración es "lineal", "cuadrática" o "doble"
    if ((std::string)argv[10] != "lineal" && (std::string)argv[10] != "cuadrática" && (std::string)argv[10] != "doble" && (std::string)argv[10] != "rehashing") {
      std::cerr << "Código de la función de exploración incorrecto." << std::endl;
      std::cerr << "Use " << argv[0] << " -h para más información." << std::endl;
      exit(EXIT_FAILURE);
    }
    // MODIFICACIÓN
    if ((std::string)argv[11] != "num") {
      std::cerr << "Argumento " << argv[11] << " incorrecto." << std::endl;
      std::cerr << "Use " << argv[0] << " -h para más información." << std::endl;
      exit(EXIT_FAILURE);
    }
    if (std::stoi(argv[12]) <= 0) {
      std::cerr << "Número de datos NIF incorrecto." << std::endl;
      std::cerr << "Use " << argv[0] << " -h para más información." << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

/**
 * @brief Función que comprueba si un NIF es válido.
 * 
 * @param nif NIF a comprobar.
 * @return true Si el NIF es válido.
 * @return false Si el NIF no es válido.
 */
bool ProveNIF(int nif) {
  if (nif < 10000000 || nif > 99999999) {
    return false;
  }
  return true;
}

/**
 * @brief Función que comprueba si un número es primo.
 * Esta función es necesaria para que no hayan tantas colisiones.
 * 
 * @param number Número a comprobar.
 * @return true Si el número es primo.
 * @return false Si el número no es primo.
 */
bool IsPrime (int number) {
  // Si el número es menor que 2, no es primo
  if (number < 2) return false;
  // Si el número es 2, es primo
  if (number == 2) return true;
  // Si el número es par, no es primo
  if (number % 2 == 0) return false;
  // Comprobamos si el número es divisible por algún número impar
  for (int i = 3; (i * i) <= number; i+=2) {
    // Si el número es divisible por i, no es primo
    if (number % i == 0) return false;
  }
  return true;
}

/**
 * @brief Función que muestra el menú de operaciones.
 * 
 * @param hash_table Tabla Hash. 
 */
void Insert(HashTableStatic<Nif>& hash_table, unsigned numNif) {
  // Insertamos los NIFS aleatorios en la tabla (numNif)
  std::cout << "Procedemos a insertar " << numNif << " NIFs aleatorios en la tabla." << std::endl;
  int count = 0;
  for (unsigned i = 0; i < numNif; i++) {
    Nif key;
    key = Nif();
    hash_table.insert(key, count);
    std::cout << "NIF " << key << " insertado." << std::endl;
  }
  std::cout << "Número de colisiones: " << count << std::endl;
}

int main(int argc, char *argv[]) {
  Usage(argc, argv);
  // Almacenamos el tamaño de la tabla
  unsigned tableSize = std::stoi(argv[2]);
  // MODIFICACIÓN
  // Almacenamos el número de datos NIF
  unsigned numNif = std::stoi(argv[12]);
  // Asignamos un numero primo al tamaño de la tabla si no lo es
  while (!IsPrime(tableSize)) {
    --tableSize;
  }
  // Almacenamos el código de la función de dispersión
  std::string dispersionFunctionCode = argv[4];
  DispersionFunction<Nif>* dispersion_function = nullptr;
  if ((std::string)argv[4] == "module") {
    // Creamos función de dispersión módulo
    dispersion_function = new Module<Nif>(tableSize);
  } else if ((std::string)argv[4] == "sum") {
    // Creamos función de dispersión suma
    dispersion_function = new Sum<Nif>(tableSize);
  } else {
    // Creamos función de dispersión pseudoaleatoria
    dispersion_function = new Pseudo<Nif>(tableSize);
  }
  std::string hashType = argv[6];
  // Almacenamos el tamaño del bloque
  unsigned blockSize = std::stoi(argv[8]);
  // Almacenamos el código de la función de exploración
  std::string explorationFunctionCode = argv[10];
  ExplorationFunction<Nif>* exploration_function = nullptr;
  if ((std::string)argv[10] == "lineal") {
    // Crear función de exploración lineal
    exploration_function = new LinearExploration<Nif>;
  } else if ((std::string)argv[10] == "cuadrática") {
    // Crear función de exploración cuadrática
    exploration_function = new QuadraticExploration<Nif>;
  } else if ((std::string)argv[10] == "doble") {
    // Crear función de exploración doble
    exploration_function = new DoubleHashing<Nif>(dispersion_function);
  } else {
    // Crear función de exploración rehashing
    exploration_function = new Rehashing<Nif>(tableSize);
  }
  // Crear tabla de dispersión cerrada
  HashTableStatic<Nif> hash_table(tableSize, dispersion_function, exploration_function, blockSize);
  // Insertamos los NIFs aleatorios en la tabla
  Insert(hash_table, numNif);
  return 0;
}