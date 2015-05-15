#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include "wheel.hpp"
#include "ref.hpp"
#include "stecker.hpp"
using namespace std;

//terminal colors
#define RED "\033[0;31m"
#define DEFAULT "\033[0;39m"

class Enigma {
  Wheel* wheels;
  Reflector* reflector;
  Stecker* stecker;
  char trans(char letter);
public:
  Enigma() {
    wheels = init_wheels();
    reflector = init_ref();
    stecker = init_steck();
  }
  char get_wheel_pos(int whl) const;
  string get_wheel_letters(int whl) const;
  char get_wheel_turn(int whl) const;
  char get_wheel_setting(int whl) const;
  string get_ref_letters() const;
  Wheel* init_wheels();
  Reflector* init_ref();
  Stecker* init_steck();
  string translate(string sentence);
};
