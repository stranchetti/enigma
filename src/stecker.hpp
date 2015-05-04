#ifndef _STECKER_H
#define _STECKER_H
#include <string>
#include <iostream>
using namespace std;

class Stecker {
  string out;

public:
  Stecker();
  string get_letters() const;
  void swap(char first, char second);
  char get_char(char input);
  char get_char_rev(char input);
};
#endif
