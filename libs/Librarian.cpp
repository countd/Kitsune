#include <string>
#include <vector>
#include <cstring>
extern "C" {
#include "Packer.h"
}

using std::string;
using std::vector;
using std::strncpy;

void archive(string basename, vector<string> files) {
  if (files.size() < 1)
    return;

  string filename = basename + ".cbz";
  char** cfiles = new char*[files.size()];

  //allocate memory and copy strings
  for (size_t i = 0; i < files.size(); i++) {
    cfiles[i] = new char[files[i].size()+1];
    strncpy(cfiles[i], files[i].c_str(), files[i].size());
  }

  write_archive(filename.c_str(), (const char**)cfiles);

  //free memory
  for (size_t i = 0; i < files.size(); i++) delete[] cfiles[i];
  delete[] cfiles;
  
  
}

