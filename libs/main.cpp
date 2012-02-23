#include "MangaGetter.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main() {

  //getImageByUrl("http://www.mangafox.com/manga/nana_to_kaoru/v01/c004/11.html", "/cygdrive/d/testpics");
  
  string page1 = "http://www.mangafox.com/manga/nana_to_kaoru/v01/c004/24.html";
  
  getChapter(page1, "/cygdrive/d/testpics");

  return 0;
}
