#include <iostream>

// class Base {
// protected:
//   int x;
// public:
//   Base() { x = 5; }
//   virtual int get() const { return 0; }
//   virtual int get() { return x; }
// };

// class Derivada: public Base {
// protected:
//   int y;
// public:
//   Derivada() { y = 10; }
//   int get() const { return y; }
// };

// int main() {
//   Base *ptr = new Derivada;
//   std::cout << ptr->get() << std::endl;
//   return 0;
// }

class Base {
protected:
  int x;
public:
  Base() { x = 5; }
  virtual int get() const { return 0; }
  virtual int get() { return x; }
};

class Derivada: public Base {
protected:
  int y;
public:
  Derivada() { y = 10; }
  int get() const { return y; }
};

int main() {
  const Base* ptr = new Derivada;
  std::cout << ptr->get() << std::endl;
  return 0;
}

/**
 * Cuando lleva puntero pegado al objeto:
 * - Const detrás: No se puede modificar el objeto (objeto constante) -> Se llama a la función constante
 * - Const delante: No se puede modificar el puntero (objeto no constante) -> Se llama a la función no constante
 * - Sin const: Se puede modificar el objeto (objeto no constante) -> Se llama a la función no constante
 * 
 * Cuando lleva puntero pegado a la variable:
 * - Const detrás: No se puede modificar el objeto (objeto constante) -> Se llama a la función constante
 * - Const delante: No se puede modificar el objeto (objeto constante) -> Se llama a la función constante
 * - Sin const: Se puede modificar el objeto (objeto no constante) -> Se llama a la función no constante
 * 
 */