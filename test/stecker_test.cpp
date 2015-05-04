#include "UTFramework.h"
#include "../src/stecker.hpp"

using namespace Thilenius;

SUITE_BEGIN("Steckerboard Tests")

TEST_BEGIN("Unsteckered") {
  Stecker test;
  string res = "";
  for (int i = 0; i < 26; i++) {
    res.push_back(test.get_char(i + 'A'));
  }
  IsTrue("get_char()", res == "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "get_char() should map each character to itself");
  res = "";
  for (int i = 0; i < 26; i++) {
    res.push_back(test.get_char_rev(i));
  }
  IsTrue("get_char_rev()", res == "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "get_char_rev() should map each character to itself");
} TEST_END

TEST_BEGIN("swap()") {
  Stecker test;
  string s1 = "BACDEFGHIJKLMNOPQRSTUVWXYZ";
  test.swap('A', 'B');
  IsTrue("swap(A, B)", test.get_letters() == s1, "letters should have A and B swapped");
  string s2 = "BACDEFGHIQKLMNOPJRSTUVWXYZ";
  test.swap('Q', 'J');
  IsTrue("swap(Q, J)", test.get_letters() == s2, "letters should have Q and J swapped as well");
  string s3 = "TAZDEFGHIQKLMNOPJRSBUVWXYC";
  test.swap('C', 'Z');
  test.swap('T', 'B');
  IsTrue("swap(C, Z), swap(T, B)", test.get_letters() == s3, "letters should have C and Z swapped and T and B swapped");
  string s4 = "TAZDELGHIQKFMWOJPRSBUVNXYC";
  test.swap('N', 'W');
  test.swap('F', 'L');
  test.swap('P', 'J');
  IsTrue("swap(C, Z), swap(F, L), swap(P, J)", test.get_letters() == s4, "letters should have C and Z swapped, F and L swapped, and P and J swapped");
} TEST_END

TEST_BEGIN("Steckers + get_char()") {
  Stecker test;
  test.swap('A', 'N');
  IsTrue("get_char(N) after swap(A, N)", test.get_char('N') == 'A', "get_char(N) should return A");
  IsTrue("get_char(B)", test.get_char('B') == 'B', "get_char(B) should still return B after the swap");
  test.swap('Z', 'M');
  IsTrue("get_char(M) after swap(Z, M)", test.get_char('M') == 'Z', "get_char(M) should return Z after the swap");
  IsTrue("get_char(A)", test.get_char('A') == 'N', "get_char(A) should return N after the swap");
} TEST_END

TEST_BEGIN("Steckers + get_char_rev()") {
  Stecker test;
  test.swap('Q', 'P');
  IsTrue("get_char_rev(0)", test.get_char_rev(0) == 'A', "swap shouldn't affect A");
  IsTrue("get_char_rev(16)", test.get_char_rev('P' - 'A') == 'Q', "P should map to Q");
  test.swap('C', 'H');
  IsTrue("get_char_rev(3)", test.get_char_rev('C' - 'A') == 'H', "C should map to H");
  test.swap('X', 'M');
  IsTrue("get_char_rev(13)", test.get_char_rev('M' - 'A') == 'X', "M should map to X");
} TEST_END

TEST_BEGIN("get_char_rev() with negative input") {
  Stecker test;
  IsTrue("get_char_rev(-1)", test.get_char_rev(-1) == 'Z', "should map to the last letter in the stecker");
} TEST_END

SUITE_END

int main(int argc, char* argv[]) {
  UTFrameworkInit;
  return 0;
}
