#include "../src/wheel.hpp"
#include "UTFramework.h"

using namespace Thilenius;

SUITE_BEGIN("Wheel Tests")

TEST_BEGIN("Default Constructor") {
  Wheel test = Wheel();
  IsTrue("empty letters", test.get_letters() == "", "letters should be empty string");
  IsTrue("empty turn", test.get_turn() == 0, "turn should be 0");
  IsTrue("empty pos", test.get_pos() == 0, "pos should be 0");
  IsTrue("empty setting", test.get_setting() == 0, "setting should be 0");
} TEST_END

TEST_BEGIN("int/char Constructor") {
  char off = 'A'; //we work in numbers not letters
  Wheel test1 = Wheel(1, 'A', 1);
  IsTrue("1, A, 1: letters", test1.get_letters() == w_version[0].first, "letters should be first string");
  IsTrue("1, A, 1: turn", test1.get_turn() == w_version[0].second, "turn should be first char");
  IsTrue("1, A, 1: pos", test1.get_pos() == 'A' - off, "pos should be A");
  IsTrue("1, A, 1: setting", test1.get_setting() == 0, "ring setting should be 0");
  Wheel test2 = Wheel(2, 'M', 6);
  IsTrue("2, M, 6: letters", test2.get_letters() == w_version[1].first, "letters should be second string");
  IsTrue("2, M, 6: turn", test2.get_turn() == w_version[1].second, "turn should be second char");
  IsTrue("2, M, 6: pos", test2.get_pos() == 'M' - off, "pos should be M");
  IsTrue("2, M, 6: setting", test2.get_setting() == 5, "ring setting should be 5");
  Wheel test3 = Wheel(3, 'Z', 16);
  IsTrue("3, Z, 16: letters", test3.get_letters() == w_version[2].first, "letters should be third string");
  IsTrue("3, Z, 16: turn", test3.get_turn() == w_version[2].second, "turn should be third char");
  IsTrue("3, Z, 16: pos", test3.get_pos() == 'Z' - off, "pos should be Z");
  IsTrue("3, Z, 16: setting", test3.get_setting() == 15, "reing setting should be 15");
  Wheel test4 = Wheel(4, 'S', 20);
  IsTrue("4, S, 20: letters", test4.get_letters() == w_version[3].first, "letters should be fourth string");
  IsTrue("4, S, 20: turn", test4.get_turn() == w_version[3].second, "turn should be fourth char");
  IsTrue("4, S, 20: pos", test4.get_pos() == 'S' - off, "pos should be S");
  IsTrue("4, S, 20: setting", test4.get_setting() == 19, "ring setting should be 19");
  Wheel test5 = Wheel(5, 'H', 26);
  IsTrue("5, H, 26: letters", test5.get_letters() == w_version[4].first, "letters should be fifth string");
  IsTrue("5, H, 26: turn", test5.get_turn() == w_version[4].second, "turn should be fifth char");
  IsTrue("5, H, 26: pos", test5.get_pos() == 'H' - off, "pos should be H");
  IsTrue("5, H, 26: setting", test5.get_setting() == 25, "ring setting should be 25");
} TEST_END

TEST_BEGIN("whl_turn()") {
  char off = 'A'; //we work in numbers still
  Wheel test = Wheel(1, 'A', 1);
  IsTrue("Initial Position", test.get_pos() == 'A' - off, "Inital pos should be 'A'");
  test.whl_turn();
  IsTrue("Turn once", test.get_pos() == 'B' - off, "pos should advance to 'B'");
  for (int i = 0; i < 25; i++) { test.whl_turn(); }
  IsTrue("Turn completely", test.get_pos() == 'A' - off, "pos should reset to 'A'");
} TEST_END

TEST_BEGIN("get_whl()") {
  Wheel test1 = Wheel(1, 'Q', 1);
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
  Wheel test2 = Wheel(2, 'E', 1);
  off = 'A' + test2.get_pos();
  res = test2.get_whl(12, &out);
  IsTrue("no turnover w/input offset: char", out == 'Q' - off, "char returned should be 'Q'");
  IsTrue("no turnover w/input offset: res", res == false, "get_whl() should return false");
  test2.whl_turn();
  off++;
  res = test2.get_whl(12, &out);
  IsTrue("turnover w/input offset: char", out == 'G' - off, "char returned should be 'G'");
  IsTrue("turnover w/input offset: res", res == true, "get_whl() should return true");
  Wheel test3 = Wheel(3, 'V', 1);
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
  Wheel test1 = Wheel(1, 'B', 1);
  char off = 'A' + test1.get_pos();
  char out = 0;
  test1.get_whl_rev(2, &out);
  IsTrue("1B, input D", out == 'G' - off, "D should map back to G");
  test1.get_whl_rev(24, &out);
  IsTrue("1B, input Z", out == 'J' - off, "Z should map back to J");
  test1.get_whl_rev(11, &out);
  IsTrue("1B, input M", out == 'C' - off, "M should map back to C");
  Wheel test2 = Wheel(2, 'J', 1);
  off = 'A' + test2.get_pos();
  test2.get_whl_rev(3, &out);
  IsTrue("2J, input M", out == 'O' - off, "M should map back to O");
  test2.get_whl_rev(12, &out);
  IsTrue("2J, input V", out == 'X' - off, "V should map back to X");
  test2.get_whl_rev(20, &out);
  IsTrue("2J, input D", out == 'C' - off, "D should map back to C");
  Wheel test3 = Wheel(3, 'Y', 1);
  off = 'A' + test3.get_pos();
  test3.get_whl_rev(10, &out);
  IsTrue("3Y, input I", out == 'Q' - off, "I should map back to Q");
  test3.get_whl_rev(19, &out);
  IsTrue("3Y, input R", out == 'I' - off, "R should map back to I");
  test3.get_whl_rev(7, &out);
  IsTrue("3Y, input F", out == 'C' - off, "F should map back to C");
  Wheel test4 = Wheel(4, 'S', 1);
  off = 'A' + test4.get_pos();
  test4.get_whl_rev(5, &out);
  IsTrue("4S, input X", out == 'O' - off, "X should map back to O");
  test4.get_whl_rev(17, &out);
  IsTrue("4S, input J", out == 'G' - off, "J should map back to G");
  test4.get_whl_rev(11, &out);
  IsTrue("4S, input D", out == 'V' - off, "D should map back to V");
  Wheel test5 = Wheel(5, 'N', 1);
  off = 'A' + test5.get_pos();
  test5.get_whl_rev(4, &out);
  IsTrue("5N, input R", out == 'D' - off, "R should map back to D");
  test5.get_whl_rev(23, &out);
  IsTrue("5N, input K", out == 'Z' - off, "K should map back to Z");
  test5.get_whl_rev(11, &out);
  IsTrue("5N, input Y", out == 'H' - off, "Y should map back to H");
} TEST_END

TEST_BEGIN("get_whl() with ring settings") {
  Wheel test1 = Wheel(1, 'A', 2);
  char off = 'A' + test1.get_pos();
  char out = 0;
  test1.get_whl(0, &out);
  IsTrue("1A2, input A", out == 'K' - off, "A should map to K with ring setting 1");
  test1.get_whl(11, &out);
  IsTrue("1A2, input L", out == 'O' - off, "L should map to O with ring setting 1");
  Wheel test2 = Wheel(2, 'H', 26);
  off = 'A' + test2.get_pos();
  test2.get_whl(0, &out);
  IsTrue("2H26, input H", out == 'W' - off, "H should map to W with ring setting 25");
  test2.get_whl(12, &out);
  IsTrue("2H26, input T", out == 'O' - off, "T should map to O with ring setting 25");
  Wheel test3 = Wheel(3, 'S', 14);
  off = 'A' + test3.get_pos();
  test3.get_whl(3, &out);
  IsTrue("3S14, input V", out == 'E' - off, "V should map to E with ring setting 13");
  test3.get_whl(20, &out);
  IsTrue("3S14, input M", out == 'B' - off, "M should map to B with ring setting 13");
} TEST_END

TEST_BEGIN("get_whl_rev() with ring settings") {
  Wheel test1 = Wheel(1, 'A', 2);
  char off = 'A' + test1.get_pos();
  char out = 0;
  test1.get_whl_rev(10, &out);
  IsTrue("1A2, input K", out == 'A' - off, "K should map back to A with ring setting 1");
  test1.get_whl_rev(17, &out);
  IsTrue("1A2, input R", out == 'I' - off, "R should map back to I with ring setting 1");
  Wheel test2 = Wheel(2, 'F', 6);
  off = 'A' + test2.get_pos();
  test2.get_whl_rev(6, &out);
  IsTrue("2F6, input L", out == 'W' - off, "L should map back to W with ring setting 5");
  test2.get_whl_rev(22, &out);
  IsTrue("2F6, input B", out == 'R' - off, "B should map back to R with ring setting 5");
  Wheel test3 = Wheel(3, 'X', 18);
  off = 'A' + test3.get_pos();
  test3.get_whl_rev(11, &out);
  IsTrue("3X18, input I", out == 'Z' - off, "I should map back to Z with ring setting 17");
  test3.get_whl_rev(25, &out);
  IsTrue("3X18, input W", out == 'T' - off, "W should map back to T with ring setting 17");
} TEST_END

SUITE_END

int main(int argc, char* argv[]) {
  UTFrameworkInit;
}
