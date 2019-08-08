#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

#include <vector>
#include "sendfile.hpp"

#define BUFFER_SIZE 1024


  
void error(const char *msg) {
  perror(msg);
  exit(0);
}

int sendFile(const std::string & hostname, int portno, const char *filename)
{
  // open input file
  FILE *ifile = fopen(filename, "rb");
  if (!ifile) {
    error("Cannot open infile");
    exit(1);
  }

  // setup socket
  int sockfd, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char * buffer = new char[BUFFER_SIZE];
  //portno = 8081;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int option = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  if (sockfd < 0) 
    error("ERROR opening socket");
  server = gethostbyname(hostname.c_str());
  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }

  
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, 
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);

  // connect to other host
  if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    error("ERROR connecting");
  

  int bytesRead = 0;
  while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, ifile)) > 0) { // read a chunk
    n = write(sockfd,buffer,bytesRead); // send a chunk
//    std::cout << "wrote: " << buffer << std::endl;
    if (n < 0) 
      error("ERROR writing to socket");
    
  }
  
  close(sockfd);
  fclose(ifile);
  return 0;
}

