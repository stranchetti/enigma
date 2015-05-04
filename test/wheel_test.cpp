#include "../src/wheel.hpp"
#include "UTFramework.h"

using namespace Thilenius;

SUITE_BEGIN("Wheel Tests")

TEST_BEGIN("Default Constructor") {
  Wheel test = Wheel();
  IsTrue("empty letters", test.get_letters() == "", "letters should be empty string");
  IsTrue("empty turn", test.get_turn() == 0, "turn should be 0");
  IsTrue("empty pos", test.get_pos() == 0, "pos should be 0");
} TEST_END

TEST_BEGIN("int/char Constructor") {
  char off = 'A'; //we work in numbers not letters
  Wheel test1 = Wheel(1, 'A');
  IsTrue("1, A: letters", test1.get_letters() == w_version[0].first, "letters should be first string");
  IsTrue("1, A: turn", test1.get_turn() == w_version[0].second, "turn should be first char");
  IsTrue("1, A: pos", test1.get_pos() == 'A' - off, "pos should be A");
  Wheel test2 = Wheel(2, 'M');
  IsTrue("2, M: letters", test2.get_letters() == w_version[1].first, "letters should be second string");
  IsTrue("2, M: turn", test2.get_turn() == w_version[1].second, "turn should be second char");
  IsTrue("2, M: pos", test2.get_pos() == 'M' - off, "pos should be M");
  Wheel test3 = Wheel(3, 'Z');
  IsTrue("3, Z: letters", test3.get_letters() == w_version[2].first, "letters should be third string");
  IsTrue("3, Z: turn", test3.get_turn() == w_version[2].second, "turn should be third char");
  IsTrue("3, Z: pos", test3.get_pos() == 'Z' - off, "pos should be Z");
  Wheel test4 = Wheel(4, 'S');
  IsTrue("4, S: letters", test4.get_letters() == w_version[3].first, "letters should be fourth string");
  IsTrue("4, S: turn", test4.get_turn() == w_version[3].second, "turn should be fourth char");
  IsTrue("4, S: pos", test4.get_pos() == 'S' - off, "pos should be S");
  Wheel test5 = Wheel(5, 'H');
  IsTrue("5, H: letters", test5.get_letters() == w_version[4].first, "letters should be fifth string");
  IsTrue("5, H: turn", test5.get_turn() == w_version[4].second, "turn should be fifth char");
  IsTrue("5, H: pos", test5.get_pos() == 'H' - off, "pos should be H");
} TEST_END

TEST_BEGIN("whl_turn()") {
  char off = 'A'; //we work in numbers still
  Wheel test = Wheel(1, 'A');
  IsTrue("Initial Position", test.get_pos() == 'A' - off, "Inital pos should be 'A'");
  test.whl_turn();
  IsTrue("Turn once", test.get_pos() == 'B' - off, "pos should advance to 'B'");
  for (int i = 0; i < 25; i++) { test.whl_turn(); }
  IsTrue("Turn completely", test.get_pos() == 'A' - off, "pos should reset to 'A'");
} TEST_END

TEST_BEGIN("get_whl()") {
  Wheel test1 = Wheel(1, 'Q');
  //offsef b/c get_whl() returns difference b/w letter and current possition
  char off = 'A' + test1.get_pos();
  char out = 0;
  bool res = test1.get_whl(0, &out);
  IsTrue("No turnover w/o input offset: char", out == 'X' - off, "char returned should be 'X'");
  IsTrue("No turnover w/o input offset: res", res == false, "get_whl() should return false");
  test1.whl_turn();
  off++;
  res = test1.get_whl(0, &out);
  IsTrue("turnover wo/ input offset: char", out == 'U' - off, "char returned should be 'U'");
  IsTrue("turnover w/o input offset: res", res == true, "get_whl() should return true");
  Wheel test2 = Wheel(2, 'E');
  off = 'A' + test2.get_pos();
  res = test2.get_whl(12, &out);
  IsTrue("no turnover w/input offset: char", out == 'Q' - off, "char returned should be 'Q'");
  IsTrue("no turnover w/input offset: res", res == false, "get_whl() should return false");
  test2.whl_turn();
  off++;
  res = test2.get_whl(12, &out);
  IsTrue("turnover w/input offset: char", out == 'G' - off, "char returned should be 'G'");
  IsTrue("turnover w/input offset: res", res == true, "get_whl() should return true");
  Wheel test3 = Wheel(3, 'V');
  off = 'A' + test3.get_pos();
  res = test3.get_whl(15, &out);
  IsTrue("no turnover w/input wrap around: char", out == 'X' - off, "char returned should be 'X'");
  IsTrue("no turnover w/input wrap around: res", res == false, "get_whl() should return false");
  test3.whl_turn();
  off++;
  res = test3.get_whl(15, &out);
  IsTrue("turnover w/input wrap around: char", out == 'V' - off, "char returned should be 'V'");
  IsTrue("turnover w/input wrap around: res", res == true, "get_whl() should return true");
} TEST_END

TEST_BEGIN("get_whl_rev()") {
  Wheel test1 = Wheel(1, 'B');
  char off = 'A' + test1.get_pos();
  char out = 0;
  test1.get_whl_rev(2, &out);
  IsTrue("1B, input D", out == 'G' - off, "D should map back to G");
  test1.get_whl_rev(24, &out);
  IsTrue("1B, input Z", out == 'J' - off, "Z should map back to J");
  test1.get_whl_rev(11, &out);
  IsTrue("1B, input M", out == 'C' - off, "M should map back to C");
  Wheel test2 = Wheel(2, 'J');
  off = 'A' + test2.get_pos();
  test2.get_whl_rev(3, &out);
  IsTrue("2J, input M", out == 'O' - off, "M should map back to O");
  test2.get_whl_rev(12, &out);
  IsTrue("2J, input V", out == 'X' - off, "V should map back to X");
  test2.get_whl_rev(20, &out);
  IsTrue("2J, input D", out == 'C' - off, "D should map back to C");
  Wheel test3 = Wheel(3, 'Y');
  off = 'A' + test3.get_pos();
  test3.get_whl_rev(10, &out);
  IsTrue("3Y, input I", out == 'Q' - off, "I should map back to Q");
  test3.get_whl_rev(19, &out);
  IsTrue("3Y, input R", out == 'I' - off, "R should map back to I");
  test3.get_whl_rev(7, &out);
  IsTrue("3Y, input F", out == 'C' - off, "F should map back to C");
  Wheel test4 = Wheel(4, 'S');
  off = 'A' + test4.get_pos();
  test4.get_whl_rev(5, &out);
  IsTrue("4S, input X", out == 'O' - off, "X should map back to O");
  test4.get_whl_rev(17, &out);
  IsTrue("4S, input J", out == 'G' - off, "J should map back to G");
  test4.get_whl_rev(11, &out);
  IsTrue("4S, input D", out == 'V' - off, "D should map back to V");
  Wheel test5 = Wheel(5, 'N');
  off = 'A' + test5.get_pos();
  test5.get_whl_rev(4, &out);
  IsTrue("5N, input R", out == 'D' - off, "R should map back to D");
  test5.get_whl_rev(23, &out);
  IsTrue("5N, input K", out == 'Z' - off, "K should map back to Z");
  test5.get_whl_rev(11, &out);
  IsTrue("5N, input Y", out == 'H' - off, "Y should map back to H");
} TEST_END

SUITE_END

int main(int argc, char* argv[]) {
  UTFrameworkInit;
}
