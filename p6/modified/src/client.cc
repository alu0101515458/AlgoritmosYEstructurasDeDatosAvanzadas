#include <iostream>
#include <fstream>
#include <string>
#include "../include/nif.h"
#include "../include/nodoB.h"
#include "../include/arbolB.h"
#include "../include/arbolbb.h"
#include "../include/arbolbe.h"

// Colores para la terminal.
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"

/**
 * @brief Función que muestra el uso del programa.
 * 
 * @param argc 
 * @param argv 
 */
void usage(int argc, char *argv[]) {
  bool ab = false;
  bool initFound = false;
  if (argc == 1) {
    std::cout << BOLD << RED "No se han introducido argumentos." << std::endl;
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < argc; ++i) { // Comenzamos en 1 para omitir el nombre del programa
    std::string arg = argv[i];
    if (arg == "-h" || arg == "--help") {
      std::cout << BOLD << "Uso: ./program -ab <abe|abb> -init <i> [s][f]" << std::endl;
      std::cout << "Opciones:" << std::endl;
      std::cout << "-ab <abe|abb> : Tipo de Árbol. NECESARIO" << std::endl;
      std::cout << "-init <i> [s][f] : Maneras de inicializar el Nif. NECESARIO" << std::endl;
			std::cout << "\ti=manual" << std::endl;
			std::cout << "\ti=random [s], s es el número de elementos a generar" << std::endl;
			std::cout << "\ti==file [s][f], s es el número de elementos a generar, f es nombre del fichero de entrada" << std::endl;
      exit(EXIT_SUCCESS);
    } else if (arg == "-ab") {
      if (i + 1 >= argc) {
        std::cout << BOLD << RED << "No se ha introducido un tamaño válido para '-ab'." << std::endl;
        exit(EXIT_FAILURE);
      } else {
				if (std::string(argv[i + 1]) != "abe" && std::string(argv[i + 1]) != "abb") {
					std::cout << BOLD << RED << "Tipo de árbol no válido." << std::endl;
					exit(EXIT_FAILURE);
				}
        ab = true;
        ++i; // Saltamos el valor de este argumento
      }
    } else if (arg == "-init") {
      if (i + 1 >= argc) {
        std::cout << BOLD << RED << "No se ha introducido una opción para '-init'." << RESET << std::endl;
        std::cout << "Opciones: 'manual' o 'random [s]' o 'file [s] <fichero>'." << std::endl;
        exit(EXIT_FAILURE);
      } else {
				if (std::string(argv[i + 1]) != "manual" && std::string(argv[i + 1]) != "random" && std::string(argv[i + 1]) != "file") {
					std::cout << BOLD << RED << "Opción de inicialización no válida." << std::endl;
					exit(EXIT_FAILURE);
				}
        ++i; // Saltamos el valor de este argumento
        initFound = true;
      }
    }
  }
  if (!ab || !initFound) {
    std::cout << BOLD << "Faltan argumentos obligatorios." << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Función que procesa el fichero de inicialización.
 * 
 * @param filename 
 * @param expectedSize 
 * @return std::vector<Nif> 
 */
std::vector<Nif> processInitFile(const std::string filename, unsigned expectedSize) {
  // Abrimos el fichero.
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << BOLD << RED << "El fichero no se ha podido abrir." << std::endl;
    exit(EXIT_FAILURE);
  }
	// Creamos un vector auxiliar para almacenar los NIFs.
  std::vector<Nif> aux;
  // Si el fichero está vacío, procedemos con la construcción por defecto.
  if (file.eof()) {
		std::cout << BOLD << YELLOW << "El fichero está vacío. Se procederá con la construcción por defecto (random)." << RESET << std::endl;
		for (unsigned i = 0; i < expectedSize; ++i) {
			Nif nif;
			aux.push_back(nif);
		}
		return aux;
	}
  // Insertamos los NIFs en el vector desde el tamaño esperado.
  for (unsigned i = 0; i < expectedSize; ++i) {
		Nif nif;
		file >> nif;
		aux.push_back(nif);
	}
  return aux;
}

/**
 * @brief Función que inserta un NIF en el árbol binario de búsqueda.
 * 
 * @param arbol 
 * @param nif 
 */
void insertar(ArbolBB<Nif>& arbol, Nif& nif) {
	if (arbol.insertar(nif)) {
		std::cout << BOLD << GREEN << "NIF insertado correctamente." << RESET << std::endl;
	} else {
		std::cout << BOLD << YELLOW << "El NIF ya existe." << RESET << std::endl;
	}
}

/**
 * @brief Función que inserta un NIF en el árbol equilibrado.
 * 
 * @param arbol 
 * @param nif 
 */
void insertar(ArbolBE<Nif>& arbol, Nif& nif) {
	if (arbol.insertar(nif)) {
		std::cout << BOLD << GREEN << "NIF insertado correctamente." << RESET << std::endl;
	} else {
		std::cout << BOLD << YELLOW << "El NIF ya existe." << RESET << std::endl;
	}
}

/**
 * @brief Función que busca un NIF en el árbol binario de búsqueda.
 * 
 * @param arbol 
 * @param nif 
 */
void buscar(ArbolBB<Nif>& arbol, Nif& nif) {
	if (arbol.buscar(nif)) {
		std::cout << BOLD << GREEN << "El NIF está en el árbol." << RESET << std::endl;
	} else {
		std::cout << BOLD << YELLOW << "El NIF no está en el árbol." << RESET << std::endl;
	}
}

/**
 * @brief Función que busca un NIF en el árbol equilibrado.
 * 
 * @param arbol 
 * @param nif 
 */
void buscar(ArbolBE<Nif>& arbol, Nif& nif) {
	if (arbol.buscar(nif)) {
		std::cout << BOLD << GREEN << "El NIF está en el árbol." << RESET << std::endl;
	} else {
		std::cout << BOLD << YELLOW << "El NIF no está en el árbol." << RESET << std::endl;
	}
}

/**
 * @brief Función que muestra el árbol binario de búsqueda.
 * 
 * @param arbol 
 */
void mostrar(ArbolBB<Nif>& arbol) {
	int opcion;
	std::cout << std::endl;
	std::cout << BOLD << MAGENTA << "[0]" << RESET << " Niveles" << std::endl;
	std::cout << BOLD << MAGENTA << "[1]" << RESET << " Preorden" << std::endl;
	std::cout << BOLD << MAGENTA << "[2]" << RESET << " Inorden" << std::endl;
	std::cout << BOLD << MAGENTA << "[3]" << RESET << " Postorden" << std::endl << std::endl;
	std::cout << UNDERLINE << "Introduce una opción" << RESET << ": ";
	std::cin >> opcion;
	if (opcion < 0 || opcion > 3) {
		std::cout << BOLD << RED "Opción no válida." << std::endl;
		exit(EXIT_FAILURE);
	}
	if (opcion == 0) {
		std::cout << *(arbol.getArbolB());
	} else if (opcion == 1) {
		std::cout << std::endl;
		std::cout << BOLD << MAGENTA << "Recorrido Preorden" << RESET << std::endl;
		std::vector<Nif> datos;
		arbol.getArbolB()->recorrerPreorden(arbol.getArbolB()->getRaiz(), datos);
		for (const Nif& nif : datos) {
			std::cout << nif << " ";
		}
		std::cout << std::endl;
	} else if (opcion == 2) {
		std::cout << std::endl;
		std::cout << BOLD << MAGENTA << "Recorrido Inorden" << RESET << std::endl;
		arbol.getArbolB()->recorrerInorden(arbol.getArbolB()->getRaiz());
		std::cout << std::endl;
	} else if (opcion == 3) {
		std::cout << std::endl;
		std::cout << BOLD << MAGENTA << "Recorrido Postorden" << RESET << std::endl;
		arbol.getArbolB()->recorrerPostorden(arbol.getArbolB()->getRaiz());
		std::cout << std::endl;
	}
}

/**
 * @brief Función que muestra el árbol equilibrado.
 * 
 * @param arbol 
 */
void mostrar(ArbolBE<Nif>& arbol) {
	int opcion;
	std::cout << std::endl;
	std::cout << BOLD << MAGENTA << "[0]" << RESET << " Niveles" << std::endl;
	std::cout << BOLD << MAGENTA << "[1]" << RESET << " Preorden" << std::endl;
	std::cout << BOLD << MAGENTA << "[2]" << RESET << " Inorden" << std::endl;
	std::cout << BOLD << MAGENTA << "[3]" << RESET << " Postorden" << std::endl << std::endl;
	std::cout << UNDERLINE << "Introduce una opción" << RESET << ": ";
	std::cin >> opcion;
	if (opcion < 0 || opcion > 3) {
		std::cout << BOLD << RED "Opción no válida." << std::endl;
		exit(EXIT_FAILURE);
	}
	if (opcion == 0) {
		std::cout << *(arbol.getArbolB());
	} else if (opcion == 1) {
		std::cout << std::endl;
		std::cout << BOLD << MAGENTA << "Recorrido Preorden" << RESET << std::endl;
		std::vector<Nif> datos;
		arbol.getArbolB()->recorrerPreorden(arbol.getArbolB()->getRaiz(), datos);
		for (const Nif& nif : datos) {
			std::cout << nif << " ";
		}
		std::cout << std::endl;
	} else if (opcion == 2) {
		std::cout << std::endl;
		std::cout << BOLD << MAGENTA << "Recorrido Inorden" << RESET << std::endl;
		arbol.getArbolB()->recorrerInorden(arbol.getArbolB()->getRaiz());
		std::cout << std::endl;
	} else if (opcion == 3) {
		std::cout << std::endl;
		std::cout << BOLD << MAGENTA << "Recorrido Postorden" << RESET << std::endl;
		arbol.getArbolB()->recorrerPostorden(arbol.getArbolB()->getRaiz());
		std::cout << std::endl;
	}
}

/**
 * @brief Función que muestra el menú de opciones.
 * 
 * @param opcion 
 */
void menu(ArbolBE<Nif>& arbol) {
	int opcion;
	do {
		std::cout << std::endl;
		std::cout << ITALIC << "Menú de opciones:" << RESET << std::endl;
		std::cout << BOLD << MAGENTA << "[0]" << RESET << " Salir" << std::endl;
		std::cout << BOLD << MAGENTA << "[1]" << RESET << " Insertar Clave" << std::endl;
		std::cout << BOLD << MAGENTA << "[2]" << RESET << " Buscar Clave" << std::endl;
		std::cout << BOLD << MAGENTA << "[3]" << RESET << " Mostrar árbol" << std::endl << std::endl;
		std::cout << UNDERLINE << "Introduce una opción" << RESET << ": ";
		std::cin >> opcion;
		if (opcion < 0 || opcion > 3) {
			std::cout << BOLD << RED "Opción no válida." << std::endl;
			exit(EXIT_FAILURE);
		}
		if (opcion == 0) {
			std::cout << std::endl;
			std::cout << BOLD << GREEN << "Saliendo..." << std::endl << std::endl;
			exit(EXIT_SUCCESS);
		} else if (opcion == 1) {
			std::cout << UNDERLINE << "Introduce el NIF a insertar" << RESET << ": ";
			Nif nif;
			std::cin >> nif;
			insertar(arbol, nif);
		} else if (opcion == 2) {
			std::cout << UNDERLINE << "Introduce el NIF a buscar" << RESET << ": ";
			Nif nif;
			std::cin >> nif;
			buscar(arbol, nif);
		} else if (opcion == 3) {
			mostrar(arbol);
		}
	} while (opcion != 0);
}

/**
 * @brief Función que muestra el menú de opciones.
 * 
 * @param opcion 
 */
void menu(ArbolBB<Nif>& arbol) {
	int opcion;
	do {
		std::cout << std::endl;
		std::cout << ITALIC << "Menú de opciones:" << RESET << std::endl;
		std::cout << BOLD << MAGENTA << "[0]" << RESET << " Salir" << std::endl;
		std::cout << BOLD << MAGENTA << "[1]" << RESET << " Insertar Clave" << std::endl;
		std::cout << BOLD << MAGENTA << "[2]" << RESET << " Buscar Clave" << std::endl;
		std::cout << BOLD << MAGENTA << "[3]" << RESET << " Mostrar árbol" << std::endl << std::endl;
		std::cout << UNDERLINE << "Introduce una opción" << RESET << ": ";
		std::cin >> opcion;
		if (opcion < 0 || opcion > 3) {
			std::cout << BOLD << RED "Opción no válida." << std::endl;
			exit(EXIT_FAILURE);
		}
		if (opcion == 0) {
			std::cout << std::endl;
			std::cout << BOLD << GREEN << "Saliendo..." << std::endl << std::endl;
			exit(EXIT_SUCCESS);
		} else if (opcion == 1) {
			std::cout << UNDERLINE << "Introduce el NIF a insertar" << RESET << ": ";
			Nif nif;
			std::cin >> nif;
			insertar(arbol, nif);
		} else if (opcion == 2) {
			std::cout << UNDERLINE << "Introduce el NIF a buscar" << RESET << ": ";
			Nif nif;
			std::cin >> nif;
			buscar(arbol, nif);
		} else if (opcion == 3) {
			mostrar(arbol);
		}
	} while (opcion != 0);
}

/**
 * @brief Función principal
 * Función que ejecuta el programa principal.
 * @return int 
 */
int main(int argc, char *argv[]) {
	usage(argc, argv);
	// Recogemos los argumentos.
	std::string ab = argv[2];
	std::string opcion = argv[4];
  std::vector<Nif> secuencia;
	// Creamos el árbol binario de búsqueda.
	ArbolBB<Nif> arbolBB;
	ArbolBE<Nif> arbolBE;
	if (opcion == "manual") { // Inicialización manual.
		for (unsigned i = 0; i < 10; ++i) { // Por defecto, inicializamos con 10 elementos.
			std::cout << "Introduce el NIF " << BOLD << MAGENTA << i + 1 << RESET << ": ";
			Nif nif;
			std::cin >> nif;

			// Seleccionamos el tipo de árbol y ejecutamos el menú.
			if (ab == "abe") {
				if (!arbolBE.insertar(nif)) {
					std::cout << BOLD << YELLOW << "El NIF " << nif << " ya existe." << RESET << std::endl;
					do {
						std::cout << "Introduce el NIF " << BOLD << MAGENTA << i + 1 << RESET << ": ";
						std::cin >> nif;
					} while (!arbolBE.insertar(nif));
				}
			} else if (ab == "abb") {
				if (!arbolBB.insertar(nif)) {
					std::cout << BOLD << YELLOW << "El NIF " << nif << " ya existe." << RESET << std::endl;
					do {
						std::cout << "Introduce el NIF " << BOLD << MAGENTA << i + 1 << RESET << ": ";
						std::cin >> nif;
					} while (!arbolBB.insertar(nif));
				}
			}
		}
	} else if (opcion == "random") { // Inicialización aleatoria.
		unsigned size = std::stoi(argv[5]);
		for (unsigned i = 0; i < size; ++i) {
			Nif nif;
			if (ab == "abe") {
				if (!arbolBE.insertar(nif)) {
					do {
						nif = Nif();
					} while (!arbolBE.insertar(nif));
				}
			} else if (ab == "abb") {
				if (!arbolBB.insertar(nif)) {
					do {
						nif = Nif();
					} while (!arbolBB.insertar(nif));
				}
			}
		}
	} else if (opcion == "file") { // Inicialización por fichero.
		unsigned size = std::stoi(argv[5]);
		std::string filename = argv[6];
		secuencia = processInitFile(filename, size);
		for (const Nif& nif : secuencia) {
			if (ab == "abb") {
				if (!arbolBB.insertar(nif)) {
					std::cout << BOLD << YELLOW << "El NIF " << nif << " ya existe. No se inserta." << RESET << std::endl;
				}
			} else {
				if (!arbolBE.insertar(nif)) {
					std::cout << BOLD << YELLOW << "El NIF " << nif << " ya existe. No se inserta." << RESET << std::endl;
				}
			}
		}
	}
	// Menú de opciones.
	if (ab == "abe") {
		menu(arbolBE);
	} else if (ab == "abb") {
		menu(arbolBB);
	}
	return 0;
}