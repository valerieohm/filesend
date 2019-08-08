#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <thread>
#include <vector>
#include "CurlWrapper.h"
#include <mutex>
#include <regex>

#include "sendfile.hpp"
#include "getfile.hpp"


int usage(const char * app) {
  std::cout << "Usage " << app << " <host> <port> write|read <filename>" << std::endl;
  return 0;
}

int main(int argc, char *argv[])
{
  if (argc == 3) {
    if (strcmp(argv[1],"read")) {
      return usage(argv[0]);
    } else {
      int port = atoi(argv[2]);
      return getFile(port);
    }
  } else {
    if (argc == 5) {
      if (strcmp(argv[1],"write")) {
        return usage(argv[0]);
      } else {
        std::string hostname = argv[2];
        int port = atoi(argv[3]);
        return sendFile(hostname, port, argv[4]);
      }
    }
  }
  return usage(argv[0]);

 
}



