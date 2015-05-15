#include "enigma.hpp"

//set up array of wheels. Returns pointer to the array
Wheel* Enigma::init_wheels() {
  bool bad = true;
  int w[3];
  char o[3];
  int s[3];
  while (bad) {
    cout << "Input 3 wheel numbers to use (1 - 5)." << endl;
    cin >> w[0] >> w[1] >> w[2];
    cin.clear(); //reset stream if any errors have occurred
    //flush extra characters still in the stream
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if ((w[0] >= 1 && w[0] <= 5) && (w[1] >= 1 && w[1] <= 5) &&
        (w[2] >= 1 && w[2] <= 5)) {
      bad = false; //input is correct
    } else {
      cout << "Must input numbers between 1 and 5" << endl;
    }
  }
  bad = true;
  while (bad) {
    cout << "Input the starting position of each wheel (A - Z)." << endl;
    cin >> o[0] >> o[1] >> o[2];
    cin.clear(); //reset stream if any errors happened
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //chuck extra
    if ((o[0] >= 'A' && o[0] <= 'Z') && (o[1] >= 'A' && o[1] <= 'Z') &&
        (o[2] >= 'A' && o[2] <= 'Z')) {
      bad = false; //input is good
    } else {
      cout << "Must input capital letters" << endl;
    }
  }
  bad = true;
  while (bad) {
    cout << "Input the ring setting for each wheel (1 - 26)." << endl;
    cin >> s[0] >> s[1] >> s[2];
    cin.clear(); //reset errors
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore extra
    if ((s[0] >= 1 && s[0] <= 26) && (s[1] >= 1 && s[1] <= 26) &&
        (s[2] >= 1 && s[2] <= 26)) {
      bad = false; //input is good
    } else {
      cout << "Must input numbers between 1 and 26." << endl;
    }
  }
  Wheel* wheels = new Wheel [3];
  for (int i = 0; i < 3; i++) {
    cout << "Using wheel " << w[i] << " with starting position " << o[i] << " and tring setting " << s[i] << endl;
    wheels[i] = Wheel(w[i], o[i], s[i]);
  }
  return wheels;
}

//init reflector
Reflector* Enigma::init_ref() {
  bool bad = true;
  char ref;
  while (bad) {
    cout << "Input reflector version to use (A - C)." << endl;
    cin >> ref;
    cin.clear(); //reset stream
    cin.ignore(numeric_limits<streamsize>::max(), 10); //chuck extra
    if (ref >= 'A' && ref <= 'C') {
      bad = false; //input is good
    } else {
      cout << "Must input captial A, B, or C" << endl;
    }
  }
  cout << "Using reflector " << ref << endl;
  return new Reflector(ref);
}

//initialize the steckerboard
Stecker* Enigma::init_steck() {
  Stecker* ret = new Stecker;
  bool bad = true;
  string in;
  while (bad) {
    cout << "Input letters to swap on the steckerboard (A - Z)." << endl;
    cout << "Every two letters will be swapped." << endl;
    getline(cin, in);
    size_t size = in.size();
    //empty line means unsteckered and is automatically fine
    if (size == 0) {
      bad = false;
    } else if (size % 2 != 0) {
      cout << "Must input an even number of letters." << endl;
    } else {
      int count[26] = {};
      for (unsigned int i = 0; i < size; i++) {
        if (in[i] < 'A' || in[i] > 'Z') {
          cout << "Must input capital letters only." << endl;
          in = "";
          break;
        } else if (++count[in[i] - 'A'] > 1) {
          cout << "Duplicate letters are not allowed." << endl;
          in = "";
          break;
        }
      }
      if (in != "") { //input is good if string hasn't been reset
        bad = false;
      }
    }
  }
  //do swap here
  size_t size = in.size();
  for (unsigned int i = 0; i < size; i += 2) {
    ret->swap(in[i], in[i + 1]);
  }
  return ret;
}

char Enigma::get_wheel_pos(int whl) const {
  return wheels[whl].get_pos();
}

string Enigma::get_wheel_letters(int whl) const {
  return wheels[whl].get_letters();
}

char Enigma::get_wheel_turn(int whl) const {
  return wheels[whl].get_turn();
}

char Enigma::get_wheel_setting(int whl) const {
  return wheels[whl].get_setting();
}

string Enigma::get_ref_letters() const {
  return reflector->get_letters();
}

//translate a single charater and return it
//helper function for translate()
char Enigma::trans(char letter) {
  wheels[2].whl_turn();
  //send through steckerboard and make it initial wheel offset
  char input = stecker->get_char(letter) - 'A';
  cout << "input: " << int(input) << endl;
  char out = 0;
  //run letter through wheels from right to left
  for (int i = 2; i >= 0; i--) {
    if (wheels[i].get_whl(input, &out)) {
      if (i != 0) wheels[i - 1].whl_turn(); //turn over wheel to left
    }
    input = out;
    cout << "Wheel " << i + 1 << " Out: " << char(out + 'A' + wheels[i].get_pos()) << endl;
  }
  //reflector
  input = reflector->get_ref(input);
  cout << "After reflection: " << char(input + 'A') << endl;
  //run letters through wheels from left to right
  //note that we also have to "translate" backwards as well
  for (int i = 0; i < 3; i++) {
    wheels[i].get_whl_rev(input, &out);
    input = out;
    cout << "Wheel " << i + 1 << " Out: " << char(out + 'A' + wheels[i].get_pos()) << endl;
  }
  return stecker->get_char_rev(out);
}

//translate input string and return the translation
string Enigma::translate(string sentence) {
  size_t size = sentence.size();
  string ret;
  for (unsigned int i = 0; i < size; i++) {
    char let = sentence[i];
    //only translate vaild characters. Other things just fall through
    if (let < 'A' || let > 'Z') {
      ret.push_back(let);
    } else {
      char temp = trans(let);
      cout << "letter after translation: " << temp << endl;
      ret.push_back(temp);
    }
  }
  cout << "final string: " << ret << endl;
  return ret;
}

#ifndef TESTING
int main() {
  Enigma test = Enigma();
  string in;
  bool done = false;
  while (!done) {
    cout << "Input line to be translated. Enter an empty line to finish." << endl;
    cout << "> ";
    getline(cin, in);
    if (in != "") {
      cout << RED << test.translate(in) << DEFAULT << endl;
    } else {
      done = true;
    }
  }
  return 0;
}
#endif
