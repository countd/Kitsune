#include "MangaGetter.h"
#include "UrlGetter.h"
#include "StringAux.h"
#include "XMLAux.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>

using std::string;
using std::vector;
using std::copy;

using std::cout;
using std::endl;

string parseXHTMLForLink(const string& xhtml, const string& button) {
  const char* buffer = xhtml.c_str();
  int size = xhtml.size();

  xmlDocPtr doc;
  xmlNodePtr cur;

  doc = xmlParseMemory(buffer, size);
  if (doc == NULL) {
    std::cerr << "Could not parse XHTML" << endl;
    return "";
  }

  cur = xmlDocGetRootElement(doc);

  if (cur == NULL) {
    std::cerr << "Empty XHTML" << endl;
    xmlFreeDoc(doc);
    return "";
  }

  cur = findSubNode(cur, "body");
  cur = findSubNodeWithAttr(cur, "div", "class", "widepage page");
  cur = findSubNodeWithAttr(cur, "div", "id", "top_center_bar");
  cur = findSubNodeWithAttr(cur, "form", "id", "top_bar");
  cur = findSubNodeWithAttr(cur, "div", "class", "r m");
  cur = findSubNodeWithAttr(cur, "a", "class", button);

  string url = getAttrib(cur, "href");

  xmlFreeDoc(doc);

  return url;

}

string parseXHTMLForNext(const string& xhtml) {
  return parseXHTMLForLink(xhtml, "btn next_page");
}

string parseXHTMLForPrev(const string& xhtml) {
  return parseXHTMLForLink(xhtml, "btn prev_page");
}

string parseXHTMLForImage(const string& xhtml) {
  const char* buffer = xhtml.c_str();
  int size = xhtml.size();
  
  xmlDocPtr doc;
  xmlNodePtr cur;

  doc = xmlParseMemory(buffer, size);
  if (doc == NULL) {
    std::cerr << "Could not parse XHTML" << endl;
    return "";
  } 

  cur = xmlDocGetRootElement(doc);

  if (cur == NULL) {
    std::cerr << "Empty XHTML" << endl;
    xmlFreeDoc(doc);
    return "";
  }

  cur = findSubNode(cur, "body");
  cur = findSubNodeWithAttr(cur, "div", "id", "viewer");
  cur = findSubNode(cur, "a");
  cur = findSubNode(cur, "img");
  string imgUrl = getAttrib(cur, "src");
  
  xmlFreeDoc(doc);

  return imgUrl;
}

vector<string> getPrevs(const string& url) {
  vector<string> urls;
  string prev = parseXHTMLForPrev(getPage(url));
  while (isExt(prev,"html")) {
    urls.push_back(followRelative(url,prev));
    prev = parseXHTMLForPrev(getPage(followRelative(url, prev)));
  }
  return urls;
}

vector<string> getNexts(const string& url) {
  vector<string> urls;
  string next = parseXHTMLForNext(getPage(url));
  while (isExt(next,"html")) {
    urls.push_back(followRelative(url,next));
    next = parseXHTMLForNext(getPage(followRelative(url, next)));
  }
  return urls;
}

vector<string> getChapterByPage(const string& url) {
  vector<string> prevs = getPrevs(url);
  vector<string> next = getNexts(url);

  copy(next.begin(),next.end(),back_inserter(prevs));

  prevs.push_back(url);

  return prevs;

}

void getImageByUrlAndData(const string& url, const string&  dir, const string& series, const string& chap, const string& page) {
  string imgUrl =  parseXHTMLForImage(getPage(url));
  
  getPicture(imgUrl, dir, series, chap, page);
}

void getImageByUrl(const string& url, const string& dir) {
  string series, chapter, page;
  parseUrl(url, series, chapter, page);
  getImageByUrlAndData(url, dir, series, chapter,page);
}

void getChapter(const string& url, const string& dir) {
  vector<string> pages = getChapterByPage(url);

  vector<string>::const_iterator iter = pages.begin();
  
  while(iter != pages.end()) {
    getImageByUrl(*iter, dir);
    iter++;
  }

  cout << "Finished fetching chapter!" << endl;
}
