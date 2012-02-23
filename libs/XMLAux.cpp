#include "XMLAux.h"
#include <string>
#include <libxml/xmlmemory.h>

using std::string;

xmlNodePtr findSubNode(xmlNodePtr cur, string node) {
  cur = cur->xmlChildrenNode;
  
  while (cur != NULL) {
    if ( (!xmlStrcmp( cur->name, (const xmlChar *)node.c_str() )) ) {
      return cur;
    }
    cur = cur->next;
  }

  return cur; // throw exception here?
}

xmlNodePtr findSubNodeWithAttr(xmlNodePtr cur, string node, string attrib, string conts) {
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
