#include <cstdlib> // Para std::rand
#include <ctime> // Para std::time

class Nif {
 public:
  Nif();
  Nif(long val);

  bool operator==(const Nif& other) const;
  bool operator!=(const int& other) const;
  bool operator<(const Nif& other) const;
  bool operator>(const Nif& other) const;
  bool operator<=(const Nif& other) const;
  bool operator>=(const Nif& other) const;
  Nif operator/=(const int& other);
  operator long() const;

 private:
  long value_;

};
