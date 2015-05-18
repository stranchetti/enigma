#include <iostream>
#include <sstream>
#include <limits>
#include <string>
#include <stdexcept>
#include "wheel.hpp"
#include "ref.hpp"
#include "stecker.hpp"
using namespace std;

//terminal colors
#define RED "\033[0;31m"
#define DEFAULT "\033[0;39m"

//stecker_checker() result codes
#define STECK_OK 0
#define STECK_BAD_INPUT 1
#define STECK_UNEVEN 2
#define STECK_DUPLICATE 3

class Enigma {
  Wheel* wheels;
  Reflector* reflector;
  Stecker* stecker;
  Wheel* init_wheels();
  Reflector* init_ref();
  Stecker* init_steck();
  int stecker_checker(string input);
  char trans(char letter);
public:
  Enigma();
  Enigma(string whls, string ref, string steck);
  ~Enigma();
  char get_wheel_pos(int whl) const;
  string get_wheel_letters(int whl) const;
  char get_wheel_turn(int whl) const;
  char get_wheel_setting(int whl) const;
  string get_ref_letters() const;
  string translate(string sentence);
};
