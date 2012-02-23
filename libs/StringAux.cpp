#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <sstream>

using std::string;
using std::vector;
using std::isspace;
using std::isdigit;
using std::find_if;
using std::search;
using std::atoi;
using std::stringstream;

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
  }
  return -1;
}

string leadZeros(string num) {
  string::size_type currentSize = num.size();
  if (currentSize == 3) {
    return num;
  } else if (currentSize == 2) {
    return "0" + num;
  } else if (currentSize == 1) {
    return "00" + num;
  } else {
    //    std::clog << "Non-standard string-int!" << std::endl;
    return num;
  }
}

string exten(string file) {
  string::iterator iter;
  string dot = ".";
  iter = find_end(file.begin(),file.end(),
		  dot.begin(), dot.end());

  // iter points to ., so we advance it
  if (iter != file.end())
    iter++;

  if (iter != file.end()) {
    string ext(iter,file.end()); // correct value?
    return ext;
  } else {
    return "";
  }
}

string itos(int i) {
  stringstream out;
  out << i;
  return out.str();
}

void parseUrl(string url, string& series, string& chap, string& page) {
  vector<string> split = split_url(skipProto(url));
  // first 2 elements are www.mangafox.com and manga, so we don't work with them

  series.clear();
  replace_copy(split[2].begin(), split[2].end(),
	       back_inserter(series), '_', '-');
  // Next element is volume, which is unneeded, so we skip it

  int chapter = reduceToInt(split[4]);
  chap = itos(chapter);
  
  int pg = reduceToInt(split[5]);
  page = itos(pg);
}
