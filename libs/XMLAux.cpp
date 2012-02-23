#include "XMLAux.h"
#include <string>
#include <libxml/xmlmemory.h>

using std::string;

// what if attribute doesn't exist?
string getAttrib(xmlNodePtr cur, const string& attrib) {
  return (char *)xmlGetProp(cur, (const xmlChar *)attrib.c_str());
}

xmlNodePtr findSubNode(xmlNodePtr cur, const string& node) {
  cur = cur->xmlChildrenNode;
  
  while (cur != NULL) {
    if ( (!xmlStrcmp( cur->name, (const xmlChar *)node.c_str() )) ) {
      return cur;
    }
    cur = cur->next;
  }

  return cur; // throw exception here?
}

xmlNodePtr findSubNodeWithAttr(xmlNodePtr cur, const string& node, const string& attrib, const string& conts) {
  cur = cur->xmlChildrenNode;
  while (cur != NULL) {
    
    if ( (!xmlStrcmp( cur->name, (const xmlChar *)node.c_str())) &&
	 (!xmlStrcmp( xmlGetProp(cur, (const xmlChar *)attrib.c_str()),
		      (const xmlChar *)conts.c_str())) ) {
      return cur;
    }

    cur = cur->next;
  }

  return cur; // throw exception here?
}
