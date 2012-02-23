#ifndef GUARD_XMLAUX_H
#define GUARD_XMLAUX_H
#include <string>
#include <libxml/xmlmemory.h>

std::string getAttrib(xmlNodePtr,const std::string&);
xmlNodePtr findSubNode(xmlNodePtr, const std::string&);
xmlNodePtr findSubNodeWithAttr(xmlNodePtr, const std::string&, const std::string&, const std::string&);

#endif
