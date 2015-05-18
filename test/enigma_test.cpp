//send printed output from enigma setup to /dev/null, but reset cout so
//output from UnitTest still appears like normal
#define SETUP(name) cout.rdbuf(d_null); Enigma name = Enigma(); cout.rdbuf(out_orig)

#include "../src/enigma.hpp"
#include "../src/wheel.hpp"
#include "../src/ref.hpp"
#include "../src/stecker.hpp"
#include "UTFramework.h"
#include <fstream>
#include <typeinfo>

using namespace Thilenius;

ifstream t_file; //file holding test settings
ifstream enc_file; //file holding encrypted messages
ifstream dec_file; //file holding decrypted messages
ofstream n_file; //dev null
streambuf* in_orig; //cin stream
streambuf* out_orig; //cout stream
streambuf* d_null; //stream associated w/dev null
invalid_argument ia = invalid_argument("I'm here for the testing");

//custom get line method to read message from files
string Readline(ifstream& file) {
  string ret;
  bool bad = true;
  while (bad) {
    getline(file, ret);
    //skip over comments 
    if (ret[0] != '#') {
      bad = false;
    }
  }
  return ret;
}

//macros to add a function to ensure something raised a desired exception
//to Alec's test framework...
#define RAISE_BEGIN try
#define RAISE_END(t_name, ex_type)\
  IsTrue(t_name, false, "Failed to raise " + string(ex_type) + " exception"); \
  } catch (exception& ex) {\
  if (typeid(ex).name() == ex_type) {\
  IsTrue(t_name, true, "");\
  } else {\
    IsTrue(t_name, false, "Failed to raise " + string(ex_type) + " exception"); \
  }

SUITE_BEGIN("Enigma Test")

TEST_BEGIN("1A, 2A, 3A, A") {
  SETUP(test);
  char off = 'A';
  IsTrue("Wheel 1: letters", test.get_wheel_letters(0) == w_version[0].first,
         "Wheel 1 should have the correct letters associated with it");
  IsTrue("Wheel 1: pos", test.get_wheel_pos(0) == 'A' - off,
         "Wheel 1 should be at position A");
  IsTrue("Wheel 1: turn", test.get_wheel_turn(0) == w_version[0].second,
         "Wheel 1 should turnover at position R");
  IsTrue("Wheel 1: setting", test.get_wheel_setting(0) == 0,
         "Wheel 1 should have setting 0");
  IsTrue("Wheel 2: letters", test.get_wheel_letters(1) == w_version[1].first,
         "Wheel 2 should have the correct letters associated with it");
  IsTrue("Wheel 2: pos", test.get_wheel_pos(1) == 'A' - off,
         "Wheel 2 should be at position A");
  IsTrue("Wheel 2: turn", test.get_wheel_turn(1) == w_version[1].second,
         "Wheel 2 should turnover at position F");
  IsTrue("Wheel 2: setting", test.get_wheel_setting(1) == 0,
         "Wheel 2 should have setting 0");
  IsTrue("Wheel 3: letters", test.get_wheel_letters(2) == w_version[2].first,
         "Wheel 3 should have the correct letters associated with it");
  IsTrue("Wheel 3: pos", test.get_wheel_pos(2) == 'A' - off,
         "Wheel 3 should be at position A");
  IsTrue("Wheel 3: turn", test.get_wheel_turn(2) == w_version[2].second,
         "Wheel 3 should turnover at position W");
  IsTrue("Wheel 3: setting", test.get_wheel_setting(2) == 0,
         "Wheel 3 should have setting 0");
  IsTrue("Reflector", test.get_ref_letters() == r_version[0],
         "Reflector should have correct letters associated with it");
} TEST_END

TEST_BEGIN("1H, 2D, 3X, C") {
  SETUP(test);
  char off = 'A';
  IsTrue("Wheel 1: letters", test.get_wheel_letters(0) == w_version[0].first,
         "Wheel 1 should have the correct letters associated with it");
  IsTrue("Wheel 1: pos", test.get_wheel_pos(0) == 'H' - off,
         "Wheel 1 should be at position H");
  IsTrue("Wheel 1: turn", test.get_wheel_turn(0) == w_version[0].second,
         "Wheel 1 should turnover at position R");
  IsTrue("wheel 1: setting", test.get_wheel_setting(0) == 5,
         "Wheel 1 should have setting 5");
  IsTrue("Wheel 2: letters", test.get_wheel_letters(1) == w_version[1].first,
         "Wheel 2 should have the correct letters associated with it");
  IsTrue("Wheel 2: pos", test.get_wheel_pos(1) == 'D' - off,
         "Wheel 2 should be at position D");
  IsTrue("Wheel 2: turn", test.get_wheel_turn(1) == w_version[1].second,
         "Wheel 2 should turnover at position F");
  IsTrue("Wheel 2: setting", test.get_wheel_setting(1) == 9,
         "Wheel 2 should have setting 9");
  IsTrue("Wheel 3: letters", test.get_wheel_letters(2) == w_version[2].first,
         "Wheel 3 should have the correct letters associated with it");
  IsTrue("Wheel 3: pos", test.get_wheel_pos(2) == 'X' - off,
         "Wheel 3 should be at position X");
  IsTrue("Wheel 3: turn", test.get_wheel_turn(2) == w_version[2].second,
         "Wheel 3 should turnover at position W");
  IsTrue("Wheel 3: setting", test.get_wheel_setting(2) == 13,
         "Wheel 3 should have setting 13");
  IsTrue("Reflector", test.get_ref_letters() == r_version[2],
         "Reflector should have correct letters associated with it");
} TEST_END

TEST_BEGIN("3Z, 4F, 5M, B") {
  SETUP(test);
  char off = 'A';
  IsTrue("Wheel 1: letters", test.get_wheel_letters(0) == w_version[2].first,
         "Wheel 1 should have the correct letters associated with it");
  IsTrue("Wheel 1: pos", test.get_wheel_pos(0) == 'Z' - off,
         "Wheel 1 should be at position Z");
  IsTrue("Wheel 1: turn", test.get_wheel_turn(0) == w_version[2].second,
         "Wheel 1 should turnover at position W");
  IsTrue("Wheel 1: setting", test.get_wheel_setting(0) == 19,
         "Wheel 1 should have setting 19");
  IsTrue("Wheel 2: letters", test.get_wheel_letters(1) == w_version[3].first,
         "Wheel 2 should have the correct letters associated with it");
  IsTrue("Wheel 2: pos", test.get_wheel_pos(1) == 'F' - off,
         "Wheel 2 should be at position F");
  IsTrue("Wheel 2: turn", test.get_wheel_turn(1) == w_version[3].second,
         "Wheel 2 should turnover at position K");
  IsTrue("Wheel 2: setting", test.get_wheel_setting(1) == 3,
         "Wheel 2 should have setting 3");
  IsTrue("Wheel 3: letters", test.get_wheel_letters(2) == w_version[4].first,
         "Wheel 3 should have the correct letters associated with it");
  IsTrue("Wheel 3: pos", test.get_wheel_pos(2) == 'M' - off,
         "Wheel 3 should be at position M");
  IsTrue("Wheel 3: turn", test.get_wheel_turn(2) == w_version[4].second,
         "Wheel 3 should turnover at position A");
  IsTrue("Wheel 3: setting", test.get_wheel_setting(2) == 17,
         "Wheel 3 should have setting 17");
  IsTrue("Reflector", test.get_ref_letters() == r_version[1],
         "Reflector should have the correct letters associated with it");
} TEST_END

TEST_BEGIN("Garbage input. 2B, 3D, 5S, A") {
  SETUP(test);
  char off = 'A';
  IsTrue("Wheel 1: letters", test.get_wheel_letters(0) == w_version[1].first,
         "Wheel 1 should have the correct letters associated with it");
  IsTrue("Wheel 1: pos", test.get_wheel_pos(0) == 'B' - off,
         "Wheel 1 should be at position B");
  IsTrue("Wheel 1: turn", test.get_wheel_turn(0) == w_version[1].second,
         "Wheel 1 should turnover at position F");
  IsTrue("Wheel 1: setting", test.get_wheel_setting(0) == 10,
         "Wheel 1 should have setting 10");
  IsTrue("Wheel 2: letters", test.get_wheel_letters(1) == w_version[2].first,
         "Wheel 2 should have the correct letters associated with it");
  IsTrue("Wheel 2: pos", test.get_wheel_pos(1) == 'D' - off,
         "Wheel 2 should be at position D");
  IsTrue("Wheel 2: turn", test.get_wheel_turn(1) == w_version[2].second,
         "Wheel 2 should turnover at position W");
  IsTrue("Wheel 2: setting", test.get_wheel_setting(1) == 16,
         "Wheel 2 should have setting 16");
  IsTrue("Wheel 3: letters", test.get_wheel_letters(2) == w_version[4].first,
         "Wheel 3 should have the correct letters associated with it");
  IsTrue("Wheel 3: pos", test.get_wheel_pos(2) == 'S' - off,
         "Wheel 3: should turnover at position A");
  IsTrue("Wheel 3: setting", test.get_wheel_setting(2) == 0,
         "Wheel 3 should have setting 0");
  IsTrue("Reflector", test.get_ref_letters() == r_version[0],
         "Reflector should have the correct letters associated with it");
} TEST_END

TEST_BEGIN("translate()") {
  SETUP(test1);
  IsTrue("A first", test1.translate("A") == "B", "A should map to B");
  IsTrue("A second", test1.translate("A") == "D", "A should map to D as the second letter");
  IsTrue("A third", test1.translate("A") == "Z", "A should map to Z as the third letter");
  IsTrue("AAA", test1.translate("AAA") == "GOW", "Three more A's should yield GOW");
  SETUP(test2);
  IsTrue("AAA first", test2.translate("AAA") == "EWT", "Three A's should yield EWT");
  IsTrue("AAA second", test2.translate("AAA") == "YXQ", "Three more A's should yield YXQ");
} TEST_END

TEST_BEGIN("Enigma Instuction Manual Test") {
  SETUP(test1);
  string enc = Readline(enc_file);
  string dec = Readline(dec_file);
  IsTrue("translation", test1.translate(enc) == dec,
         "the first encrypted message should decrypt to the first decrypted message");
  SETUP(test2);
  IsTrue("encryption", test2.translate(dec) == enc,
         "the first decrypted message should encrypt to the first encrypted message");
} TEST_END

TEST_BEGIN("Operation Barbarossa") {
  SETUP(test1);
  string enc1 = Readline(enc_file);
  string enc2 = Readline(enc_file);
  string dec1 = Readline(dec_file);
  string dec2 = Readline(dec_file);
  IsTrue("translation part 1", test1.translate(enc1) == dec1,
         "The first encrypted message part should decrypt to the first decrypted message part");
  SETUP(test2);
  IsTrue("encryption part 1", test2.translate(dec1) == enc1,
         "The first decrypted message part should encrypt to the first encryped message part");
  SETUP(test3);
  IsTrue("translation part 2", test3.translate(enc2) == dec2,
         "The second encrypted message part should decrypt to the second decrypted message part");
  SETUP(test4);
  IsTrue("encryption part 2", test4.translate(dec2) == enc2,
         "The second decrypted message part should encrypt to the first encrypted message part");
} TEST_END

TEST_BEGIN("Custom Constructor: 1A1 2A1 3A1 B") {
  Enigma test = Enigma("1A1 2A1 3A1", "B", "");
  IsTrue("Wheel 1: letters", test.get_wheel_letters(0) == w_version[0].first,
         "Wheel 1 should have the correct letters associated with it.");
  IsTrue("Wheel 1: pos", test.get_wheel_pos(0) == 0, 
         "Wheel 1 should be at position A");
  IsTrue("Wheel 1: turn", test.get_wheel_turn(0) == w_version[0].second, 
         "Wheel 1 should have the correct turnover position");
  IsTrue("Wheel 1: setting", test.get_wheel_setting(0) == 0, 
         "Wheel 1 should be at setting 0");
  IsTrue("Wheel 2: letters", test.get_wheel_letters(1) == w_version[1].first,
         "Wheel 2 should have the correct letters associated with it");
  IsTrue("Wheel 2: pos", test.get_wheel_pos(1) == 0, 
         "Wheel 2 should be at position A");
  IsTrue("Wheel 2: turn", test.get_wheel_turn(1) == w_version[1].second, 
         "Wheel 2 should have the correct turnover position");
  IsTrue("Wheel 2: setting", test.get_wheel_setting(1) == 0, 
         "Wheel 2 should be at ring setting 0");
  IsTrue("Wheel 3: letters", test.get_wheel_letters(2) == w_version[2].first,
         "Wheel 3 should have the correct letters associated with it");
  IsTrue("Wheel 3: pos", test.get_wheel_pos(2) == 0, 
         "Wheel 3 should be at position A");
  IsTrue("Wheel 3: turn", test.get_wheel_turn(2) == w_version[2].second, 
         "Wheel 3 should have the correct turnover position");
  IsTrue("Wheel 3: setting", test.get_wheel_setting(2) == 0, 
         "Wheel 3 should be at ring setting 0");
  IsTrue("Reflector", test.get_ref_letters() == r_version[1], 
         "Reflector should have the correct letters associated with it");
  IsTrue("Stecker", test.get_stecker_letters() == "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "Steckerboard should have no plugs");
} TEST_END

TEST_BEGIN("Custom Constructor: 5V14 3G2 4K22 C ABCDEF") {
  Enigma test = Enigma("5V14 3G2 4K22", "C", "ABCDEF");
  IsTrue("Wheel 1: letters", test.get_wheel_letters(0) == w_version[4].first,
         "Wheel 1 should have the correct letters associated with it");
  IsTrue("Wheel 1: pos", test.get_wheel_pos(0) == 'V' - 'A',
         "Wheel 1 should be at position V");
  IsTrue("Wheel 1: turn", test.get_wheel_turn(0) == w_version[4].second,
         "Wheel 1 should have the correct turnover position");
  IsTrue("Wheel 1: setting", test.get_wheel_setting(0) == 13,
         "Wheel 1 should be at ring setting 13");
  IsTrue("Wheel 2: letters", test.get_wheel_letters(1) == w_version[2].first,
         "Wheel 2 should have the correct letters associated with it");
  IsTrue("Wheel 2: pos", test.get_wheel_pos(1) == 'G' - 'A',
         "Wheel 2 should be at position G");
  IsTrue("Wheel 2: turn", test.get_wheel_turn(1) == w_version[2].second,
         "Wheel 2 should have the correct turnover position");
  IsTrue("Wheel 2: setting", test.get_wheel_setting(1) == 1,
         "Wheel 2 should have ring setting 1");
  IsTrue("Wheel 3: letters", test.get_wheel_letters(2) == w_version[3].first,
         "Wheel 3 should have the correct letters associated with it");
  IsTrue("Wheel 3: pos", test.get_wheel_pos(2) == 'K' - 'A',
         "Wheel 3 should be at position K");
  IsTrue("Wheel 3: turn", test.get_wheel_turn(2) == w_version[3].second,
         "Wheel 3 should have the correct turnover position");
  IsTrue("Wheel 3: setting", test.get_wheel_setting(2) == 21, 
         "Wheel 3 should be at ring setting 21");
  IsTrue("Reflector", test.get_ref_letters() == r_version[2],
         "Reflector should have the correct letters associated with it");
  IsTrue("Stecker", test.get_stecker_letters() == "BADCFEGHIJKLMNOPQRSTUVWXYZ", "Stecker should swap AB, CD, and EF");
} TEST_END

TEST_BEGIN("Custom Constructor Exceptions") {
  RAISE_BEGIN {
    Enigma test1 = Enigma("12A1 1A1 1A 1", "A", "");
    RAISE_END("Bad wheel number", typeid(ia).name())
  }
  RAISE_BEGIN {
    Enigma test2 = Enigma("1/1 1A1 1A1", "A", "");
    RAISE_END("Bad wheel position", typeid(ia).name())
  }
  RAISE_BEGIN {
    Enigma test3 = Enigma("1A100 1A1 1A1", "A", "");
    RAISE_END("Bad ring setting", typeid(ia).name())
  }
  RAISE_BEGIN {
    Enigma test4 = Enigma("1A1 1A1 1A1", "123", "");
    RAISE_END("Bad reflector version", typeid(ia).name())
  }
  RAISE_BEGIN {
    Enigma test5 = Enigma("1A1 1A1 1A1", "A", "11");
    RAISE_END("Bad stecker input characters", typeid(ia).name())
  }
  RAISE_BEGIN {
    Enigma test6 = Enigma("1A1 1A1 1A1", "A", "A");
    RAISE_END("Uneven number of stecker letters", typeid(ia).name())
  }
  RAISE_BEGIN {
    Enigma test7 = Enigma("1A1 1A1 1A1", "A", "ABCDDFERASHA");
    RAISE_END("Duplicate letters in stecker input", typeid(ia).name())
  }
  RAISE_BEGIN {
    Enigma test8 = Enigma("1A", "A", "");
    RAISE_END("Not enough wheel arguments", typeid(ia).name())
  }
} TEST_END
SUITE_END

int main(int argc, char* argv[]) {
  t_file.open("test/test.txt");
  n_file.open("/dev/null");
  enc_file.open("test/mess_enc.txt");
  dec_file.open("test/mess_dec.txt");
  d_null = n_file.rdbuf();
  out_orig = cout.rdbuf();
  in_orig = cin.rdbuf(t_file.rdbuf());
  UTFrameworkInit;
}
