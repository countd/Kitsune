#include "Kitsune.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

int main(int argc, char** argv) {
  
  if (argc != 3) {
    cout << "Wrong number of arguments!" << endl;

    return -1;
  }

  string url = argv[1];
  string dir = argv[2];

  getChapter(url,dir); // WARNING! NO CHEKING!!

  return 0;
}
