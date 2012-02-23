#ifndef GUARD_STRINGAUX_H
#define GUARD_STRINGAUX_H
#include <vector>
#include <string>

std::vector<std::string> split_url(const std::string&);
std::string skipProto(const std::string&);
int reduceToInt(const std::string&);
#endif
