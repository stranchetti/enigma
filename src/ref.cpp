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
  input %= 26;
  //we need input to be positive so we have to use the same
  //workaround as the other files
  if (input < 0) {
    input += 26;
  }
  return letters[input] - 'A';
}
