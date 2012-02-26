#ifndef GUARD_MANGAGETTER_H
#define GUARD_MANGAGETTER_H
#include <string>
#include <vector>

std::vector<std::string> getChapter(const std::string& url, const std::string& dir);

std::string getAndPackChapter(const std::string& url, const std::string& dir);
#endif
