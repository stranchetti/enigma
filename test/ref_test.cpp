#include "../src/ref.hpp"
#include "UTFramework.h"

using namespace Thilenius;

SUITE_BEGIN("Reflector Tests")

TEST_BEGIN("Default Constructor") {
  Reflector test = Reflector();
  IsTrue("empty letters string", test.get_letters() == "", "letters should be empty string");
} TEST_END

TEST_BEGIN("Char Constructor") {
  Reflector test1 = Reflector('A');
  Reflector test2 = Reflector('B');
  Reflector test3 = Reflector('C');
  IsTrue("version A", test1.get_letters() == r_version[0], "A should be first string");
  IsTrue("version B", test2.get_letters() == r_version[1], "B should be second string");
  IsTrue("version C", test3.get_letters() == r_version[2], "C should be third string");
} TEST_END

TEST_BEGIN("get_ref(), version A") {
  char off = 'A'; //works with numbers, not letters
  Reflector test = Reflector('A');
  IsTrue("a to e", test.get_ref('A' - off) == 'E' - off, "a should map to e");
  IsTrue("z to d", test.get_ref('Z' - off) == 'D' - off, "z should map to d");
} TEST_END

TEST_BEGIN("get_ref(), version B") {
  char off = 'A';
  Reflector test = Reflector('B');
  IsTrue("a to y", test.get_ref('A' - off) == 'Y' - off, "a should map to y");
  IsTrue("z to t", test.get_ref('Z' - off) == 'T' - off, "z should map to t");
} TEST_END

TEST_BEGIN("get_ref(), version C") {
  char off = 'A';
  Reflector test = Reflector('C');
  IsTrue("a to f", test.get_ref('A' - off) == 'F' - off, "a should map to f");
  IsTrue("z to l", test.get_ref('Z' - off) == 'L' - off, "z should map to l");
} TEST_END

SUITE_END

int main(int argc, char* argv[]) {
  UTFrameworkInit;
}
