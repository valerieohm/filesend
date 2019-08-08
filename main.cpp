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
  if (argc !=5) return usage(argv[0]);
  bool write = (!strcmp(argv[3],"write"));
  if (!write && (strcmp(argv[3], "read"))) return usage(argv[0]);
  std::string hostname = argv[1];
  int port = atoi(argv[2]);
  if (write) {
    sendFile(hostname, port, argv[4]);
  } else {
    getFile(port, argv[4]);
  }
  return 0;

 
}



