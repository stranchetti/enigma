#include "enigma.hpp"

Enigma::Enigma() {
#ifdef INTERACTIVE
  wheels = init_wheels();
  reflector = init_ref();
  stecker = init_steck();
#else
  wheels = new Wheel[3];
  wheels[0] = Wheel(1, 'A', 1);
  wheels[1] = Wheel(2, 'A', 1);
  wheels[2] = Wheel(3, 'A', 1);
  reflector = new Reflector('B');
  stecker = new Stecker();
#endif
}

Enigma::Enigma(string whls, string ref, string steck) {
  //check wheels
  stringstream wheel_in(whls);
  int w1, w2, w3, s1, s2, s3;
  char p1, p2, p3;
  wheel_in >> w1 >> p1 >> s1 >> w2 >> p2 >> s2 >> w3 >> p3 >> s3;
  if (wheel_in.eof() && wheel_in.fail()) {
    throw invalid_argument("Not enough arguments for wheels");
  } else if (w1 < 1 || w1 > 5 || w2 < 1 || w2 > 5 || w3 < 1 || w3 > 5) {
    throw invalid_argument("Wheel argument must use numbers between 1 and 5 for the wheel number");
  } else if (p1 < 'A' || p1 > 'Z' || p2 < 'A' || p2 > 'Z' || p3 < 'A' || p3 > 'Z') {
    throw invalid_argument("Wheel argument must use capital letters for the wheel position");
  } else if (s1 < 1 || s1 > 26 || s2 < 1 || s2 > 26 || s3 < 1 || s3 > 26) {
    throw invalid_argument("Wheel argument must use numbers between 1 and 26 for the ring setting");
  } else {
    wheels = new Wheel[3];
    wheels[0] = Wheel(w1, p1, s1);
    wheels[1] = Wheel(w2, p2, s2);
    wheels[2] = Wheel(w3, p3, s3);
  }
  //check ref
  if (ref == "" || ref[0] < 'A' || ref[0] > 'C') {
    throw invalid_argument("Reflector argument must be captial A, B, or C");
  } else {
    reflector = new Reflector(ref[0]);
  }
  //check stecker
  int res = stecker_checker(steck);
  if (res == STECK_OK) {
    stecker = new Stecker();
    size_t size = steck.size();
    for (unsigned int i = 0; i < size; i += 2) {
      stecker->swap(steck[i], steck[i + 1]);
    }
  } else if (res == STECK_BAD_INPUT) {
    throw invalid_argument("Stecker argument must be capital letters only");
  } else if (res == STECK_UNEVEN) {
    throw invalid_argument("Stecker argument must have an even number of letters");
  } else {
    throw invalid_argument("Stecker argument may not contain duplicate letters");
  }
}

Enigma::~Enigma() {
  delete [] wheels;
  delete reflector;
  delete stecker;
}

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
    int res = stecker_checker(in);
    if (res == STECK_OK) {
      bad = false;
    } else if (res == STECK_UNEVEN) {
      cout << "Must input an even number of letters." << endl;
    } else if (res == STECK_BAD_INPUT) {
      cout << "Must input capital letters only." << endl;
    } else {
      cout << "Duplicate letters are not allowed." << endl;
    }
  }
  //do swap here
  size_t size = in.size();
  for (unsigned int i = 0; i < size; i += 2) {
    ret->swap(in[i], in[i + 1]);
  }
  return ret;
}

int Enigma::stecker_checker(string input) {
  size_t size = input.size();
  if (size == 0) {
    return STECK_OK;
  } else if (size % 2 != 0) {
    return STECK_UNEVEN;
  } else {
    int count[26] = {};
    for (unsigned int i = 0; i < size; i++) {
      if (input[i] < 'A' || input[i] > 'Z') {
        return STECK_BAD_INPUT;
      } else if (++count[input[i] - 'A'] > 1) {
        return STECK_DUPLICATE;
      }
    }
    return STECK_OK;
  }
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

string Enigma::get_stecker_letters() const {
  return stecker->get_letters();
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
