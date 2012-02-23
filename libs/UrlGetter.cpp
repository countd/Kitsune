#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <curl/curl.h>

using std::string;
using std::ofstream;
using std::find_end;

typedef string::size_type str_size;

size_t writeToString(char *data, size_t size, size_t nmemb, string *buffer) {
  size_t result = 0;
  if (buffer != NULL) {
    buffer->append(data, size * nmemb);
    result = size * nmemb;
  }
  return result;
}

// TODO: Error checking
string getPage(string url) {
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

string leadZeros(string num) {
  str_size currentSize = num.size();
  if (currentSize == 3) {
    return num;
  } else if (currentSize == 2) {
    return "0" + num;
  } else if (currentSize == 1) {
    return "00" + num;
  } else {
    std::cerr << "Non-standard string-int!" << std::endl;
    return num;
  }
}

string exten(string file) {
  string::iterator iter;
  string dot = ".";
  iter = find_end(file.begin(),file.end(),
		  dot.begin(), dot.end());
  // iter points to ., so we advance it
  iter++;
  if (iter != file.end()) {
    string ext(iter,file.end()); // correct value?
    return ext;
  } else {
    return "";
  }
}

void getPicture(string url, string dir, string series, string chap, string page) {
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
}
