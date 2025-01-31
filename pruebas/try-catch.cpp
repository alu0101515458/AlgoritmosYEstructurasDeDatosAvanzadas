#include <iostream>
#include <exception>

class MyException : public std::exception {
  public:
    const char* what() const noexcept override {
      return "Error: División por 0.";
    }
};

int division(const int& numerador, const int& denominador) {
  if (denominador == 0) throw MyException();
  return numerador / denominador;
}

int main() {
  int numerador = 3, denominador = 1;
  try {
    int resultado = division(numerador, denominador);
    std::cout << "Resultado: " << resultado << std::endl;
  } catch (const MyException& e) {
    std::cout << "Excepción capturada: " << e.what() << std::endl;
  }
  return 0;
}