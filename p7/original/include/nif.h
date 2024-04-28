#include <iostream> // Para std::ostream
#include <cstdlib> // Para std::rand
#include <ctime> // Para std::time
#pragma once

class Nif {
 public:
  Nif();
  Nif(long val);

  bool operator==(const Nif& other) const;
  bool operator==(const int& other) const;
  bool operator!=(const int& other) const;
  bool operator!=(const Nif& other) const;
  bool operator<(const Nif& other) const;
  bool operator<(const int& other) const;
  bool operator>(const Nif& other) const;
  bool operator>(const int& other) const;
  bool operator<=(const Nif& other) const;
  bool operator>=(const Nif& other) const;
  Nif operator/=(const int& other);

  operator long() const;
  long getValue() const;

  friend std::ostream& operator<<(std::ostream& os, const Nif& nif);
  friend std::istream& operator>>(std::istream& is, Nif& nif);

 private:
  long value_;
};
