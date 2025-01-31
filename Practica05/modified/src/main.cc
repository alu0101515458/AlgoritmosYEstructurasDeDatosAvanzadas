#include <iostream>
#include <fstream>
#include "../include/nif.h"
#include "../include/sequence.h"
#include "../include/sortmethod.h"

#define RED   "\033[31m"
#define BOLD  "\033[1m"
#define RESET "\033[0m"

/**
 * @brief Función principal del programa
 * 
 * @return int 
 */
int main() {
  StaticSequence<Nif> sequence(100, -1, false);
  StaticSequence<Nif> sequence2(1000, -1, false);
  for (size_t i = 0; i < sequence.getSize(); i++) {
    Nif nif;
    sequence.insert(nif);
  }
  for (size_t i = 0; i < sequence2.getSize(); i++) {
    Nif nif;
    sequence2.insert(nif);
  }
  SelectionSort<Nif> selectionSort(sequence);
  std::cout << RED << BOLD << "MÉTODO\t\t" << "SIZE\t" << "Nº COMPARACIONES" << RESET << std::endl;
  selectionSort.Sort();
  std::cout << "SELECTION\t" << sequence.getSize() << "\t" << sequence.getComparisons() << std::endl;
  sequence.resetComparisons();
  QuickSort<Nif> quickSort(sequence);
  quickSort.Sort();
  std::cout << "QUICK\t\t" << sequence.getSize() << "\t" << sequence.getComparisons() << std::endl;
  SelectionSort<Nif> selectionSort2(sequence2);
  selectionSort2.Sort();
  std::cout << "SELECTION\t" << sequence2.getSize() << "\t" << sequence2.getComparisons() << std::endl;
  sequence2.resetComparisons();
  QuickSort<Nif> quickSort2(sequence2);
  quickSort2.Sort();
  std::cout << "QUICK\t\t" << sequence2.getSize() << "\t" << sequence2.getComparisons() << std::endl;
  return 0;
}