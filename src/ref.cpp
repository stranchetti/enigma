#include "ref.hpp"

string r_version[3] =  {"EJMZALYXVBWFCRQUONTSPIKHGD",
                        "YRUHQSLDPXNGOKMIEBFZCWVJAT",
                        "FVPJIAOYEDRZXWGCTKUQSBNMHL"};

Reflector::Reflector() {
  letters = "";
}

string Reflector::get_letters() const {
  return letters;
}

Reflector::Reflector(char letter) {
  letters = r_version[letter - 'A'];
}

char Reflector::get_ref(char input) {
  return letters[input] - 'A';
}
