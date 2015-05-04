#include "wheel.hpp"
#include <iostream>

//strings containing mapping of alphabet for each wheel number
//paired with the letter they turn over on
entry w_version[5] = {make_pair("EKMFLGDQVZNTOWYHXUSPAIBRCJ", 'R'),
                      make_pair("AJDKSIRUXBLHWTMCQGZNPYFVOE", 'F'),
                      make_pair("BDFHJLCPRTXVZNYEIWGAKMUSQO", 'W'),
                      make_pair("ESOVPZJAYQUIRHXLNFTGKDCMWB", 'K'),
                      make_pair("VZBRGITYUPSDNHLXAWMJQOFECK", 'A')};

Wheel::Wheel() {
  letters = "";
  turn = 0;
  pos = 0;
}

Wheel::Wheel(int number, char start) {
  letters = w_version[number - 1].first;
  turn = w_version[number - 1].second;
  pos = start - 'A';
}

char Wheel::get_pos() const {
  return pos;
}

char Wheel::get_turn() const {
  return turn;
}

string Wheel::get_letters() const {
  return letters;
}

//returns true if rollover occurs
//input is current difference b/w wheel position and last map
//out is the place to store the value to be used as the next input
bool Wheel::get_whl(char input, char* out) {
  bool ret;
  if (pos + 'A'  == turn) { //current letter equal to turn letter
    ret = true; //turnover has occurred
  } else {
    ret = false;
  }
  char map = (pos + input) % 26;
  //we require the positive result, which C++ will not give us if
  //(pos + input) is negative
  if (map < 0) {
    map += 26;
  }
  char letter = letters[map];
  cout << "letter before return: " << letter << endl;
  *out = letter - 'A' - pos;
  return ret;
}

//like get_whl, but works in reverse (goes from left side of wheel to right)
void Wheel::get_whl_rev(char input, char* out) {
  //smae workaround as before, since we need the positive result
  char temp = (pos + input) % 26;
  if (temp < 0) {
    temp += 26;
  }
  char in_letter = temp + 'A';
  char index = letters.find(in_letter);
  cout << "letter before return: " << (char) (index + 'A') << endl;
  *out = index - pos;
}

void Wheel::whl_turn() {
  pos++;
  pos %= 26;
}
