#include <iostream>

class A {
private:
  int a_;
public:
  A(int x=10): a_(x) {}
  int f(int x) { return g(x * x); }
  virtual int g(int x) const { return x % a_; }
};

class B : public A {
private:
  int b_;
public:
  B(int x): b_(x) {}
  virtual int f(int x) const { return g(x + x); }
  int g(int x) const { return x % b_; }
};

class C : public B {
private:
  int c_;
public:
  C(int x=5): B(x), c_(x) {}
  int f(int x) { return g(x * c_); }
};

int main() {
  A *a = new A;
  std::cout << a->f(5) << std::endl; // Línea 1

  /**
   * A* a = new A -> a_ = 10 (no se aporta valor alguno)
   * a->f(5) = A::f(5) -> A::g(25) = 25 % 10 = 5
   */

  A *b = new B(7);
  std::cout << b->f(4) << std::endl; // Línea 2

  /**
   * A* b = new B(7) -> b_ = 7, a_ = 10
   * b->f(4) = A::f(4) -> B::g(16) = 16 % 7 = 2
   */

  B *c = new C;
  std::cout << c->f(3) << std::endl; // Línea 3

  /**
   * B* c = new C -> c_ = 5, b_ = 5, a_ = 10
   * c->f(3) = B::f(3) -> B::g(6) = 6 % 5 = 1
   */

  return 0;
}

// class Base {
// public:
//   virtual void display() {
//     std::cout << "Display de Base" << std::endl;
//   }
//   void prueba() {
//     std::cout << "Prueba de Base" << std::endl;
//   }
// };

// class Derived : public Base {
// public:
//   void display() override { // Sobrescribiendo la función virtual
//     std::cout << "Display de Derived" << std::endl;
//   }
//   virtual void prueba() {
//     std::cout << "Prueba de Derived" << std::endl;
//   }
// };

// int main() {
//   Base* b = new Derived;
//   b->prueba();
//   delete b;
//   return 0;
// }
