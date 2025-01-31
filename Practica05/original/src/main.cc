#include <iostream>
#include <fstream>
#include "../include/nif.h"
#include "../include/sequence.h"
#include "../include/sortmethod.h"

/**
 * @brief Función que muestra el uso del programa.
 * 
 * @param argc 
 * @param argv 
 */
void Usage(int argc, char *argv[]) {
  bool sizeFound = false;
  bool orderFound = false;
  bool initFound = false;
  bool traceFound = false;
  if (argc == 1) {
    std::cout << "No se han introducido argumentos." << std::endl;
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < argc; ++i) { // Comenzamos en 1 para omitir el nombre del programa
    std::string arg = argv[i];
    if (arg == "-h" || arg == "--help") {
      std::cout << "Uso: ./program -size <n> -ord <radix|selection|quick|heap|shell> -init <manual|random|file <fichero>> -trace <y|n>" << std::endl;
      std::cout << "Opciones:" << std::endl;
      std::cout << "-size <n> : Tamaño de la secuencia. NECESARIO" << std::endl;
      std::cout << "-ord radix|selection|quick|heap|shell : Métodos de ordenación. NECESARIO" << std::endl;
      std::cout << "-init <manual|random|file <fichero>> : Maneras de inicializar el Nif. NECESARIO" << std::endl;
      std::cout << "-trace <y|n> : Mostrar traza. NECESARIO" << std::endl;
      exit(EXIT_SUCCESS);
    } else if (arg == "-size") {
      if (i + 1 >= argc || std::stoi(argv[i + 1]) <= 0) {
        std::cout << "No se ha introducido un tamaño válido para '-size'." << std::endl;
        exit(EXIT_FAILURE);
      } else {
        sizeFound = true;
        ++i; // Saltamos el valor de este argumento
      }
    } else if (arg == "-ord") {
      if (i + 1 >= argc || (std::string(argv[i + 1]) != "radix" && std::string(argv[i + 1]) != "seleccion" && std::string(argv[i+1]) != "quick" && std::string(argv[i+1]) != "heap" && std::string(argv[i+1]) != "shell")) {
        std::cout << "No se ha introducido un tipo de ordenación válido para '-ord'." << std::endl;
        exit(EXIT_FAILURE);
      } else {
        orderFound = true;
        ++i; // Saltamos el valor de este argumento
      }
    } else if (arg == "-init") {
      if (i + 1 >= argc) {
        std::cout << "No se ha introducido una opción para '-init'." << std::endl;
        std::cout << "Opciones: 'manual' o 'random' o 'file <fichero>'." << std::endl;
        exit(EXIT_FAILURE);
      } else {
        ++i; // Saltamos el valor de este argumento
        initFound = true;
      }
    } else if (arg == "-trace") {
      if (i + 1 >= argc || (std::string(argv[i + 1]) != "y" && std::string(argv[i + 1]) != "n")) {
        std::cout << "No se ha introducido un valor válido para '-trace'." << std::endl;
        exit(EXIT_FAILURE);
      } else {
        ++i; // Saltamos el valor de este argumento
        traceFound = true;
      }
    }
  }
  if (!sizeFound || !orderFound || !initFound || !traceFound) {
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
int processInitFile(const std::string filename, StaticSequence<Nif>& sequence, unsigned expectedSize) {
  // Abrimos el fichero.
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "El fichero no se ha podido abrir." << std::endl;
    exit(EXIT_FAILURE);
  }
  
  // Leemos el fichero y comprobamos si está vacío.
  std::string line;
  std::getline(file, line);
  // Si el fichero está vacío, procedemos con la construcción por defecto.
  if (line.empty()) {
    std::cout << "El fichero está vacío, procedemos con la construcción por defecto." << std::endl;
    for (size_t i = 0; i < sequence.getSize(); i++) {
      Nif nif;
      sequence.insert(nif);
    }
    return 0;
  }
  std::vector<Nif> aux;
  // Insertamos el primer NIF en el vector auxiliar.
  Nif nif(std::stol(line));
  aux.push_back(nif);
  // Mientras haya líneas en el fichero, las leemos y las insertamos en el vector auxiliar.
  while (std::getline(file, line)) {
    Nif nif(std::stol(line));
    aux.push_back(nif);      
  }
  // Comprobamos si el tamaño del fichero coincide con el tamaño de la secuencia.
  if (aux.size() != expectedSize) {
    std::cout << "El tamaño del fichero no coincide con el tamaño de la secuencia." << std::endl;
    exit(EXIT_FAILURE);
  }
  // Insertamos los NIFs en la secuencia.
  for (size_t i = 0; i < aux.size(); i++) {
    sequence.insert(aux[i]);
  }
  return 0;
}

int main(int argc, char *argv[]) {
  Usage(argc, argv);
  StaticSequence<Nif> sequence(std::atoi(argv[2]), -1, false);
  // Si argc es 9, contiene: './program -size <n> -ord <radix|selection|quick|heap|shell> -init <manual|random> -trace <y|n>'
  if (argc == 9) {
    if (std::string(argv[4]) == "radix") {
      if (std::string(argv[6]) == "manual") {
        for (size_t i = 0; i < sequence.getSize(); i++) {
          std::cout << "Introduce el NIF nº" << i << ": ";
          long aux_nif;
          std::cin >> aux_nif;
          Nif nif(aux_nif);
          sequence.insert(nif);
        }
      } else if (std::string(argv[6]) == "random") {
        for (size_t i = 0; i < sequence.getSize(); i++) {
          std::cout << "NIF nº" << i << ": ";
          Nif nif;
          sequence.insert(nif);
          std::cout << nif << std::endl;
        }
      }
      if (std::string(argv[8]) == "y") {
        sequence.setTrace(true);
      }
      RadixSort<Nif> radixSort(sequence);
      radixSort.Sort();
      // Si no se ha especificado que se muestre la traza, se imprime el vector al final.
      if (std::string(argv[8]) == "n") {
        sequence.print();
      }

    } else if (std::string(argv[4]) == "seleccion") {
      if (std::string(argv[6]) == "manual") {
        for (size_t i = 0; i < sequence.getSize(); i++) {
          std::cout << "Introduce el NIF nº" << i << ": ";
          long aux_nif;
          std::cin >> aux_nif;
          Nif nif(aux_nif);
          sequence.insert(nif);
        }
      } else if (std::string(argv[6]) == "random") {
        for (size_t i = 0; i < sequence.getSize(); i++) {
          std::cout << "NIF nº" << i << ": ";
          Nif nif;
          sequence.insert(nif);
          std::cout << nif << std::endl;
        }
      }
      if (std::string(argv[8]) == "y") {
        sequence.setTrace(true);
      } 
      SelectionSort<Nif> selectionSort(sequence);
      selectionSort.Sort();
      // Si no se ha especificado que se muestre la traza, se imprime el vector al final.
      if (std::string(argv[8]) == "n") {
        sequence.print();
      }

    } else if (std::string(argv[4]) == "quick") {
      if (std::string(argv[6]) == "manual") {
        for (size_t i = 0; i < sequence.getSize(); i++) {
          std::cout << "Introduce el NIF nº" << i << ": ";
          long aux_nif;
          std::cin >> aux_nif;
          Nif nif(aux_nif);
          sequence.insert(nif);
        }
      } else if (std::string(argv[6]) == "random") {
        for (size_t i = 0; i < sequence.getSize(); i++) {
          std::cout << "NIF nº" << i << ": ";
          Nif nif;
          sequence.insert(nif);
          std::cout << nif << std::endl;
        }
      }
      if (std::string(argv[8]) == "y") {
        sequence.setTrace(true);
      }
      QuickSort<Nif> quickSort(sequence);
      quickSort.Sort();
      // Si no se ha especificado que se muestre la traza, se imprime el vector al final.
      if (std::string(argv[8]) == "n") {
        sequence.print();
      }

    } else if (std::string(argv[4]) == "heap") {
      if (std::string(argv[6]) == "manual") {
        for (size_t i = 0; i < sequence.getSize(); i++) {
          std::cout << "Introduce el NIF nº" << i << ": ";
          long aux_nif;
          std::cin >> aux_nif;
          Nif nif(aux_nif);
          sequence.insert(nif);
        }
      } else if (std::string(argv[6]) == "random") {
        for (size_t i = 0; i < sequence.getSize(); i++) {
          std::cout << "NIF nº" << i << ": ";
          Nif nif;
          sequence.insert(nif);
          std::cout << nif << std::endl;
        }
      }
      if (std::string(argv[8]) == "y") {
        sequence.setTrace(true);
      }
      HeapSort<Nif> heapSort(sequence);
      heapSort.Sort();
      // Si no se ha especificado que se muestre la traza, se imprime el vector al final.
      if (std::string(argv[8]) == "n") {
        sequence.print();
      }
  
    } else if (std::string(argv[4]) == "shell") {
      if (std::string(argv[6]) == "manual") {
        for (size_t i = 0; i < sequence.getSize(); i++) {
          std::cout << "Introduce el NIF nº" << i << ": ";
          long aux_nif;
          std::cin >> aux_nif;
          Nif nif(aux_nif);
          sequence.insert(nif);
        }
      } else if (std::string(argv[6]) == "random") {
        for (size_t i = 0; i < sequence.getSize(); i++) {
          std::cout << "NIF nº" << i << ": ";
          Nif nif;
          sequence.insert(nif);
          std::cout << nif << std::endl;
        }
      }
      if (std::string(argv[8]) == "y") {
        sequence.setTrace(true);
      }
      ShellSort<Nif> shellSort(sequence, 0.4);
      shellSort.Sort();
  
    }
  } else if (argc == 10) { // Si argc es 10, contiene: './program -size <n> -ord <radix|selection|quick|heap|shell> -init <file <fichero>> -trace <y|n>'
    if (std::string(argv[4]) == "radix") {
      if (std::string(argv[6]) == "file") {
        processInitFile(argv[7], sequence, std::atoi(argv[2]));
        if (std::string(argv[9]) == "y") {
          sequence.setTrace(true);
        }
        RadixSort<Nif> radixSort(sequence);
        radixSort.Sort();
        // Si no se ha especificado que se muestre la traza, se imprime el vector al final.
        if (std::string(argv[9]) == "n") {
          sequence.print();
        }
      }
    } else if (std::string(argv[4]) == "seleccion") {
      if (std::string(argv[6]) == "file") {
        processInitFile(argv[7], sequence, std::atoi(argv[2]));
        if (std::string(argv[9]) == "y") {
          sequence.setTrace(true);
        }
        SelectionSort<Nif> selectionSort(sequence);
        selectionSort.Sort();
        // Si no se ha especificado que se muestre la traza, se imprime el vector al final.
        if (std::string(argv[9]) == "n") {
          sequence.print();
        }
      }
    } else if (std::string(argv[4]) == "quick") {
      if (std::string(argv[6]) == "file") {
        processInitFile(argv[7], sequence, std::atoi(argv[2]));
        if (std::string(argv[9]) == "y") {
          sequence.setTrace(true);
        }
        QuickSort<Nif> quickSort(sequence);
        quickSort.Sort();
        // Si no se ha especificado que se muestre la traza, se imprime el vector al final.
        if (std::string(argv[9]) == "n") {
          sequence.print();
        }
      }
    } else if (std::string(argv[4]) == "heap") {
      if (std::string(argv[6]) == "file") {
        processInitFile(argv[7], sequence, std::atoi(argv[2]));
        if (std::string(argv[9]) == "y") {
          sequence.setTrace(true);  
        }
        HeapSort<Nif> heapSort(sequence);
        heapSort.Sort();
        // Si no se ha especificado que se muestre la traza, se imprime el vector al final.
        if (std::string(argv[9]) == "n") {
          sequence.print();
        }
      }
    } else if (std::string(argv[4]) == "shell") {
      if (std::string(argv[6]) == "file") {
        processInitFile(argv[7], sequence, std::atoi(argv[2]));
        if (std::string(argv[9]) == "y") {
          sequence.setTrace(true);
        }
        ShellSort<Nif> shellSort(sequence, 0.4);
        shellSort.Sort();
        // Si no se ha especificado que se muestre la traza, se imprime el vector al final.
        if (std::string(argv[9]) == "n") {
          sequence.print();
        }
      }
    }
  }
  return 0;
}