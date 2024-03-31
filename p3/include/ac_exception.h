#pragma once
#include <exception>
#include <string>

/**
 * @brief Clase ac_exception que implementa una exceptión propia.
 * 
 */
class ac_exception : public std::exception {
 public:
  ac_exception(const std::string& msg);
  const char* what() const throw();

 private:
  std::string message;
};
