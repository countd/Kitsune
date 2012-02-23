#ifndef GUARD_XMLAUX_H
#define GUARD_XMLAUX_H
#include <string>
#include <libxml/xmlmemory.h>

std::string getAttrib(xmlNodePtr,std::string);
xmlNodePtr findSubNode(xmlNodePtr, std::string);
xmlNodePtr findSubNodeWithAttr(xmlNodePtr, std::string, std::string, std::string);

#endif
