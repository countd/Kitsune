#include "MangaGetter.h"
#include "UrlGetter.h"
#include "StringAux.h"
#include "XMLAux.h"
#include <iostream>
#include <string>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>

using std::string;

using std::cout;
using std::endl;

void parseXHTMLForImage(string xhtml, string& ret) {
  const char* buffer = xhtml.c_str();
  int size = xhtml.size();
  
  xmlDocPtr doc;
  xmlNodePtr cur;

  doc = xmlParseMemory(buffer, size);
  if (doc == NULL) {
    std::cerr << "Could not parse XHTML" << endl;
    return;
  } 

  cur = xmlDocGetRootElement(doc);

  if (cur == NULL) {
    std::cerr << "Empty XHTML" << endl;
    xmlFreeDoc(doc);
    return;
  }

  cur = findSubNode(cur, "body");
  cur = findSubNodeWithAttr(cur, "div", "id", "viewer");
  cur = findSubNode(cur, "a");
  cur = findSubNode(cur, "img");
  string imgUrl((char *)xmlGetProp(cur, (const xmlChar *)"src"));
  
  xmlFreeDoc(doc);

  ret = imgUrl;
}

void getImageByUrlAndData(string url, string dir, string series, string chap, string page) {
  string imgUrl;
  parseXHTMLForImage(getPage(url), imgUrl);
  
  getPicture(imgUrl, dir, series, chap, page);
}

void getImageByUrl(string url, string dir) {
  string series, chapter, page;
  parseUrl(url, series, chapter, page);
  getImageByUrlAndData(url, dir, series, chapter,page);
}
