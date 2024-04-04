#include <cmath>

#include "sequence.h"
#pragma once

/**
 * @brief Función que realiza el std::swap de dos elementos de la secuencia NIF.
 *
 */
void swapNif(StaticSequence<Nif>& sequence, int i, int j) {
  Nif aux = sequence[i];
  sequence[i] = sequence[j];
  sequence[j] = aux;
}
/**
 * @brief Clase abstracta que define un método de ordenamiento.
 *
 * @tparam Key
 */
template <class Key>
class SortMethod {
 public:
  virtual void Sort() = 0;

 protected:
  StaticSequence<Key>& sequence_;
  SortMethod(StaticSequence<Key>&);
};

/**
 * @brief Constructor de la clase SortMethod.
 *
 * @tparam Key
 * @param sequence
 */
template <class Key>
SortMethod<Key>::SortMethod(StaticSequence<Key>& sequence)
    : sequence_(sequence) {}

/**
 * @brief Clase que define el método de ordenamiento por selección.
 *
 * @tparam Key
 */
template <class Key>
class SelectionSort : public SortMethod<Key> {
 public:
  SelectionSort(StaticSequence<Key>&);
  void Sort() override;
};

/**
 * @brief Constructor de la clase SelectionSort.
 *
 * @tparam Key
 * @param sequence
 */
template <class Key>
SelectionSort<Key>::SelectionSort(StaticSequence<Key>& sequence)
    : SortMethod<Key>(sequence) {}

/**
 * @brief Método que ordena la secuencia por selección.
 *
 * @tparam Key
 * @param sequence
 * @param size
 */
template <class Key>
void selectionSortCode(StaticSequence<Key>& sequence, size_t size) {
  // Bucle para recorrer la secuencia
  for (size_t i = 0; i < size - 1; i++) {
    // Inicializamos el mínimo en la posición i
    size_t min = i;
    // Bucle para encontrar el mínimo en el resto de la secuencia
    for (size_t j = i + 1; j < size; j++) {
      // Comparamos los elementos para encontrar el mínimo
      if (sequence[j] < sequence[min]) {
        min = j;
      }
    }
    // Intercambiamos el mínimo encontrado con el elemento en la posición i
    if (min != i) {
      swapNif(sequence, i, min);
    }
  }
}

/**
 * @brief Método que ordena la secuencia por selección.
 *
 * @tparam Key
 */
template <class Key>
void SelectionSort<Key>::Sort() {
  selectionSortCode(this->sequence_, this->sequence_.getSize());
}

/**
 * @brief Clase que define el método de ordenamiento por HeapSort.
 *
 * @tparam Key
 */
template <class Key>
class HeapSort : public SortMethod<Key> {
 public:
  HeapSort(StaticSequence<Key>&);
  void Sort() override;
};

/**
 * @brief Constructor de la clase HeapSort.
 *
 * @tparam Key
 * @param sequence
 */
template <class Key>
HeapSort<Key>::HeapSort(StaticSequence<Key>& sequence)
    : SortMethod<Key>(sequence) {}

/**
 * @brief Código del algoritmo heapify que sirve para ordenar la secuencia por
 * HeapSort.
 *
 * @tparam Key
 */
template <class Key>
void heapify(StaticSequence<Key>& sequence, int n, int i) {
  int largest = i;        // Inicializamoa el más grande como raíz
  int left = 2 * i + 1;   // izquierda = 2*i + 1
  int right = 2 * i + 2;  // derecha = 2*i + 2

  // Si el hijo izquierdo es más grande que la raíz
  if (left < n && sequence[left] > sequence[largest]) {
    largest = left;
  }
  // Si el hijo derecho es más grande que el más grande hasta ahora
  if (right < n && sequence[right] > sequence[largest]) {
    largest = right;
  }
  // Si el más grande no es la raíz
  if (largest != i) {
    std::swap(sequence[i], sequence[largest]);
    // Recursivamente heapify el subárbol afectado
    heapify(sequence, n, largest);
  }
}

/**
 * @brief Método que ordena la secuencia por HeapSort.
 *
 * @tparam Key
 */
template <class Key>
void heapSortCode(StaticSequence<Key>& sequence, int n) {
  // Construimos el heap (reorganizamos el array)
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(sequence, n, i);
  }
  // Uno por uno extraemos un elemento del heap
  for (int i = n - 1; i > 0; i--) {
    // Movemos la raíz actual al final
    std::swap(sequence[0], sequence[i]);
    // llamamos a heapify en el heap reducido
    heapify(sequence, i, 0);
  }
}

/**
 * @brief Método que ordena la secuencia por HeapSort.
 *
 * @tparam Key
 */
template <class Key>
void HeapSort<Key>::Sort() {
  heapSortCode(this->sequence_, this->sequence_.getSize());
}

/**
 * @brief Clase que define el método de ordenamiento por QuickSort.
 *
 * @tparam Key
 */
template <class Key>
class QuickSort : public SortMethod<Key> {
 public:
  QuickSort(StaticSequence<Key>&);
  void Sort() override;
};

/**
 * @brief Constructor de la clase QuickSort.
 *
 * @tparam Key
 * @param sequence
 */
template <class Key>
QuickSort<Key>::QuickSort(StaticSequence<Key>& sequence)
    : SortMethod<Key>(sequence) {}

/**
 * @brief Código del algoritmo quickSort que sirve para ordenar la secuencia por
 * QuickSort.
 *
 * @tparam Key
 */
template <class Key>
void quickSortCode(StaticSequence<Key>& sequence, int ini, int fin) {
  int i = ini, f = fin;
  Key p = sequence[(i + f) / 2];  // Pivote
  while (i <= f) {
    while (sequence[i] < p) i++;
    while (sequence[f] > p) f--;
    if (i <= f) {
      std::swap(sequence[i], sequence[f]);
      i++;
      f--;
    }
  }
  if (ini < f) quickSortCode(sequence, ini, f);
  if (i < fin) quickSortCode(sequence, i, fin);
}

/**
 * @brief Método que ordena la secuencia por QuickSort.
 *
 * @tparam Key
 */
template <class Key>
void QuickSort<Key>::Sort() {
  quickSortCode(this->sequence_, 0, this->sequence_.getSize() - 1);
}

/**
 * @brief Clase que define el método de ordenamiento por ShellSort.
 *
 * @tparam Key
 */
template <class Key>
class ShellSort : public SortMethod<Key> {
 public:
  ShellSort(StaticSequence<Key>&, const double&);
  void Sort() override;

 private:
  double alpha_;
};

/**
 * @brief Constructor de la clase ShellSort.
 *
 * @tparam Key
 * @param sequence
 */
template <class Key>
ShellSort<Key>::ShellSort(StaticSequence<Key>& sequence, const double& alpha)
    : SortMethod<Key>(sequence), alpha_(alpha) {}

/**
 * @brief Función que ordena la secuencia por ShellSort.
 * 
 * @tparam Key 
 * @param delta 
 * @param sec 
 * @param n 
 */
template <class Key>
void deltaSort(int delta, StaticSequence<Key>& sec, int n) {
  for (int i = delta; i < n; i++) {
    Key x = sec[i];
    int j = i;
    while ((j >= delta) && (x < sec[j - delta])) {
      sec[j] = sec[j - delta];
      j = j - delta;
    }
    sec[j] = x;
  }
}

/**
 * @brief Método que ordena la secuencia por ShellSort.
 *
 * @tparam T
 * @param sec
 */
template <class Key>
void shellSortCode(StaticSequence<Key>& sec, int n) {
  int delta = n;
  while (delta > 1) {
    delta = delta / 2;
    deltaSort(delta, sec, n);
  }
}

/**
 * @brief Método que ordena la secuencia por ShellSort.
 *
 * @tparam Key
 */
template <class Key>
void ShellSort<Key>::Sort() {
  if (alpha_ <= 0 || alpha_ >= 1) {
    throw std::invalid_argument("Alfa debe estar en el rango (0, 1)");
  }
  shellSortCode(this->sequence_, this->sequence_.getSize());
}

/**
 * @brief Clase que define el método de ordenamiento por RadixSort.
 *
 * @tparam Key
 */
template <class Key>
class RadixSort : public SortMethod<Key> {
 public:
  RadixSort(StaticSequence<Key>&);
  void Sort() override;
};

/**
 * @brief Constructor de la clase RadixSort.
 *
 * @tparam Key
 * @param sequence
 */
template <class Key>
RadixSort<Key>::RadixSort(StaticSequence<Key>& sequence)
    : SortMethod<Key>(sequence) {}

/**
 * @brief Método que ordena la secuencia por RadixSort.
 *
 * @tparam Key
 */
template <class Key>
void radixSortCode(StaticSequence<Key>& sequence, int n) {
  if (n == 0) return;  // Retornamos si la secuencia está vacía

  // Encontramos el número máximo en la secuencia
  Key maxNumber = -1;
  for (int i = 0; i < n; i++) {
    if (sequence[i] < 0) {
      throw std::invalid_argument("RadixSort no soporta números negativos");
    }
    // Si encontramos un número mayor, lo actualizamos
    if (sequence[i] > maxNumber) {
      maxNumber = sequence[i];
    }
  }

  int maxDigits = 0;
  // Encontramos el número de dígitos del número máximo para saber el número de
  // iteraciones
  while (maxNumber > 0) {
    maxNumber /= 10;
    maxDigits++;
  }

  // Nos aseguramos de manejar el caso cuando el número máximo es 0.
  if (maxDigits == 0) maxDigits = 1;

  // Cubetas para los dígitos del 0 al 9
  std::vector<std::vector<Key>> buckets(10);

  // Procesamos cada dígito desde el menos significativo al más significativo
  for (int digit = 0; digit < maxDigits; digit++) {
    // Limpiamos las cubetas
    for (int i = 0; i < 10; i++) {
      buckets[i].clear();
    }
    // Repartimos elementos en cubetas
    for (int i = 0; i < n; i++) {
      // La fórmula para encontrar el dígito es (n / 10^d) % 10 pues 10^d es el
      // número de dígitos que debemos movernos para encontrar el dígito
      // deseado. Nos aseguramos de que dígitos con un número menor de dígitos
      // se completen con 0s a la izquierda y, por ende, se ubiquen en la cubeta
      // 0. EJ: 32 pero maxDigits = 3, entonces 32 / 10^2 = 0
      int bucketIndex =
          (sequence[i] / static_cast<int>(std::pow(10, digit))) % 10;
      // Ponemos el elemento en la cubeta correspondiente
      buckets[bucketIndex].push_back(sequence[i]);
    }
    // Recogemos elementos de las cubetas y los ponemos de vuelta en la
    // secuencia
    int idx = 0;
    for (int i = 0; i < 10; i++) {
      for (const Key& elem : buckets[i]) {
        sequence[idx++] = elem;
      }
    }
  }
}

/**
 * @brief Método que ordena la secuencia por RadixSort.
 *
 * @tparam Key
 */
template <class Key>
void RadixSort<Key>::Sort() {
  radixSortCode(this->sequence_, this->sequence_.getSize());
}
