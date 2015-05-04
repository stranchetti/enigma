#ifndef _WHEEL_H
#define _WHEEL_H
#include <string>
#include <utility>
using namespace std;

typedef pair<string, char> entry;

class Wheel {
  string letters;
  char turn;
  char pos;
public:
  Wheel();
  Wheel(int number, char start);
  char get_pos() const;
  char get_turn() const;
  string get_letters() const;
  bool get_whl(char input, char* out);
  void get_whl_rev(char input, char* out);
  void whl_turn();
};

extern entry w_version[5];
#endif
