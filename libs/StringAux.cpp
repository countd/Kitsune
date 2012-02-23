#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cctype>

using std::string;
using std::vector;
using std::isspace;
using std::isdigit;
using std::find_if;
using std::search;
using std::atoi;

bool is_delim(char c) {
  return c == '/';
}

bool not_space(char c) {
  return !isspace(c);
}

string skipProto(const string& url) {
  typedef string::const_iterator iter;

  string delim = "://";

  iter i = search(url.begin(), url.end(),
		  delim.begin(), delim.end());

  if (i == url.end()) {
    return url;
  } else {
    return string((i + delim.size()), url.end());
  }
  
}

vector<string> split_url(const string& str) {
  typedef string::const_iterator iter;
  vector<string> ret;

  iter i = str.begin();
  while (i != str.end()) {
    
    i = find_if(i,str.end(), not_space);

    iter j = find_if(i, str.end(), is_delim);
    
    if (i != str.end())
      ret.push_back(string(i, j));
    i = j;
    if (i != str.end())
      i++; // advance past /
  }
  return ret;
}

bool is_number(char c) {
  return isdigit(c);
}

bool not_number(char c) {
  return !isdigit(c);
}

int reduceToInt(const string& str) {
  // Leave the first numeric sequance
  typedef string::const_iterator iter;

  iter i = str.begin();
  while (i != str.end()) {
    i = find_if(i,str.end(),is_number);

    iter j = find_if(i,str.end(), not_number);
    
    if (i != str.end())
      return atoi(string(i,j).c_str());
    return -1;
  }
}
