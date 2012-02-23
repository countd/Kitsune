#include "MangaGetter.h"
#include "UrlGetter.h"
#include "StringAux.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>

using std::string;
using std::stringstream;
using std::ofstream;
using std::vector;
using std::replace_copy;

using std::cout;
using std::endl;

xmlNodePtr getBody(xmlNodePtr cur) {
  cur = cur->xmlChildrenNode;
  while (cur != NULL) {
    if ((!xmlStrcmp(cur->name, (const xmlChar *)"body"))) {
      return cur;
    }
    cur = cur->next;
  }
  return cur;
}

xmlNodePtr viewerDiv(xmlNodePtr body) {
  body = body->xmlChildrenNode;
  while (body != NULL) {
    if ((!xmlStrcmp(body->name, (const xmlChar *)"div")) && 
	(!xmlStrcmp(xmlGetProp(body, (const xmlChar *)"id"), (const xmlChar *)"viewer"))) {
      return body;
    }
    body = body->next;
  }
  return body;
}

xmlNodePtr aFromDiv(xmlNodePtr div) {
  div = div->xmlChildrenNode;
  while (div != NULL) {
    if ((!xmlStrcmp(div->name, (const xmlChar *)"a"))) {
      return div;
    }
    div = div->next;
  }
  return div;
}

xmlNodePtr imgFromA(xmlNodePtr a) {
  a = a->xmlChildrenNode;
  while (a != NULL) {
    if ((!xmlStrcmp(a->name, (const xmlChar *)"img"))) {
      return a;
    }
    a = a->next;
  }
}

xmlNodePtr imgFromDiv(xmlNodePtr div) {
  return imgFromA(aFromDiv(div));
}

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

  cur = getBody(cur);
  cur = viewerDiv(cur);
  cur = imgFromDiv(cur);
  string imgUrl((char *)xmlGetProp(cur, (const xmlChar *)"src"));
  
  xmlFreeDoc(doc);

  ret = imgUrl;
}

void parseUrl(string url, string& series, string& chap, string& page) {
  vector<string> split = split_url(skipProto(url));
  // first 2 elements are www.mangafox.com and manga, so we don't work with them

  series.clear();
  replace_copy(split[2].begin(), split[2].end(),
	       back_inserter(series), '_', '-');
  // Next element is volume, which is unneeded, so we skip it

  int chapter = reduceToInt(split[4]);
  stringstream out;
  out << chapter;
  chap = out.str();
  
  int pg = reduceToInt(split[5]);
  stringstream out2;
  out2 << pg;
  page = out2.str();

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
