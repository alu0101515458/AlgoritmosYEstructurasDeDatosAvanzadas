#include "ac_exception.h"

/**
 * @brief Constructor de la clase ac_exception.
 * 
 * @param msg 
 */
ac_exception::ac_exception(const std::string& msg) : message(msg) {}

/**
 * @brief Función que devuelve el mensaje de la excepción.
 * 
 * @return const char* 
 */
const char* ac_exception::what() const throw() {
  return message.c_str();
}