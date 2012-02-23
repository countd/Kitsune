#ifndef GUARD_STRINGAUX_H
#define GUARD_STRINGAUX_H
#include <vector>
#include <string>

std::vector<std::string> split_url(const std::string&);
std::string skipProto(const std::string&);
int reduceToInt(const std::string&);
std::string leadZeros(std::string);
std::string exten(std::string);
std::string itos(int);
void parseUrl(std::string,std::string&,std::string&,std::string& page);
#endif
