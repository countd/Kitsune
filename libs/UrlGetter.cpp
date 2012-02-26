#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <curl/curl.h>
#include "StringAux.h"

using std::string;
using std::ofstream;
using std::find_end;

using std::cout;
using std::endl;

size_t writeToString(char *data, size_t size, size_t nmemb, string *buffer) {
  size_t result = 0;
  if (buffer != NULL) {
    buffer->append(data, size * nmemb);
    result = size * nmemb;
  }
  return result;
}

// TODO: Error checking
string getPage(const string& url) {
  CURL *curl;
  string buffer;

  curl = curl_easy_init();

  // Get page at URL
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_HEADER, 0); // Don't return the header
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToString);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer); // address of buffer
  
  curl_easy_perform(curl); // fetch data

  curl_easy_cleanup(curl); // close connection and clean up

  return buffer;
}

static size_t writeToFile(char *data, size_t size, size_t nmemb, ofstream *file) {
  file->write(data,size*nmemb);
  return size*nmemb;
}

string getPicture(const string& url, const string& dir, const string& series, const string& chap, const string& page) {
  CURL *curl;
  string filename = dir + "/" + series + "-c" + leadZeros(chap) + "-p" + leadZeros(page);
  string filetype = exten(url);
  string fullname = filename + "." + filetype;
  ofstream outfile(fullname.c_str());
  
  curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_HEADER, 0);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToFile);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outfile);

  curl_easy_perform(curl);

  curl_easy_cleanup(curl);
  cout << "Fetched " << fullname << endl;

  return fullname;
}
