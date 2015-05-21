#include "stecker.hpp"

Stecker::Stecker() {
  out = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

string Stecker::get_letters() const {
  return out;
} 

void Stecker::swap(char first, char second) {
  int f_index = out.find(first);
  int s_index = out.find(second);
  out[f_index] = second;
  out[s_index] = first;
}

//find map of the input in the swapped letters
//input is at this point just a pure capital letter
char Stecker::get_char(char input) {
  return out[input - 'A'];
}

//map backward from swapped letters. find index of the letter and use that
//as the ofset from A
//input is the offset returned by the last wheel. Add A to it to
//convert it to a mapping where the current position of the wheel maps to
//the letter A, which is how the stecker works
char Stecker::get_char_rev(char input) {
  D_PRINT("stecker input: %d", (int) input);
  char temp;
  //workaround for negative % 26. C++ will give a negative result, but
  //we need a positive one
  if (input % 26 < 0) {
    temp = input % 26 + 26 + 'A';
  } else {
    temp = input % 26 + 'A';
  }
  D_PRINT("character to search for: %c", temp);
  return out.find(temp) + 'A';
}
