#include "Kitsune.h"
#include <string>
#include <iostream>
#include <vector>
#include "StringAux.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

int main(int argc, char** argv) {
  
  if (argc != 3) {
    cout << "Wrong number of arguments!" << endl;

    return -1;
  }

  string url = argv[1];
  string dir = argv[2];
  
  cout << "Packed into " <<  getAndPackChapter(url,dir) << endl; // WARNING! NO CHEKING!!

  return 0;
}
