#ifndef _REF_H
#define _REF_H
#include <string>
using namespace std;

//separate class for reflector wheel. Don't need to keep track
//of the current position since it never turns
class Reflector {
  string letters;
public:
  Reflector();
  Reflector(char letter);
  string get_letters() const;
  char get_ref(char input);
};

extern string r_version[3];
#endif
