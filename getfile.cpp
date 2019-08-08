#include <iostream>
#include <fstream>
#include "getfile.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#define BUFFER_SIZE 1024
void error(const char *msg);


int getFile(int portno, const char * filename) {

  // open the file to save in
  FILE *ofile = fopen(filename, "wb");
  if (!ofile) {
    error("Cannot open file");
    exit(1);
  }

  // setup socket
  int sockfd, newsockfd;
  socklen_t clilen;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in serv_addr, cli_addr;
  int n = 1;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  int option = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
  if (sockfd < 0) {
    error("ERROR opening socket");
    exit(1);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  // listen
  if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)             { 
    error("ERROR on binding");
  }
  listen(sockfd,1);
  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd, 
                     (struct sockaddr *) &cli_addr, 
                     &clilen);
  if (newsockfd < 0) 
    error("ERROR on accept");

  bzero(buffer,BUFFER_SIZE);
  while (n > 0) {
    n = read(newsockfd,buffer,BUFFER_SIZE); // read a chunk
    if (n < 0) error("ERROR reading from socket");
//    printf("Here is the message: %s\n",buffer);
    fwrite(buffer, 1, n, ofile); // write a chunk
    bzero(buffer,BUFFER_SIZE);
  }
  
  close(newsockfd);
  close(sockfd);
  fclose(ofile);
  return 0; 
}


