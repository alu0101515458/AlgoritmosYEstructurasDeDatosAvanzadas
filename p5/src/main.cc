#include <iostream>
#include "../include/nif.h"
#include "../include/sequence.h"
#include "../include/sortmethod.h"

int main() {
  StaticSequence<Nif> sequence(10, -1);
  RadixSort<Nif> radixSort(sequence);

  std::cout << "Vector de NIFs sin ordenar:" << std::endl;
  for (size_t i = 0; i < sequence.getSize(); i++) {
    Nif nif;
    sequence.insert(nif);
    std::cout << nif << std::endl;
  }

  radixSort.Sort();

  std::cout << "Vector de NIFs ordenado:" << std::endl;
  for (size_t i = 0; i < sequence.getSize(); i++) {
    std::cout << sequence[i] << std::endl;
  }
  return 0;
}