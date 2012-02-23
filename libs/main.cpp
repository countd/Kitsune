#include "MangaGetter.h"
#include "UrlGetter.h"
#include <iostream>
#include <string>
#include <limits>

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main() {

  //getImageByUrl("http://www.mangafox.com/manga/nana_to_kaoru/v01/c004/11.html", "/cygdrive/d/testpics");

  string page1 = "http://www.mangafox.com/manga/nana_to_kaoru/v01/c004/1.html";
  string page2 = "http://www.mangafox.com/manga/nana_to_kaoru/v01/c004/2.html";
  string page3 = "http://www.mangafox.com/manga/nana_to_kaoru/v01/c004/24.html";
  string next1,next2,next3;
  string prev1,prev2,prev3;

  next1 = parseXHTMLForNext(getPage(page1));
  next2 = parseXHTMLForNext(getPage(page2));
  next3 = parseXHTMLForNext(getPage(page3));

  prev1 = parseXHTMLForPrev(getPage(page1));
  prev2 = parseXHTMLForPrev(getPage(page2));
  prev3 = parseXHTMLForPrev(getPage(page3));

  cout << next1 << endl << next2 << endl << next3 << endl;
  cout << prev1 << endl << prev2 << endl << prev3 << endl;

  return 0;
}
