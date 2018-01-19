#include <iostream>
#include "json.hpp"
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_send_data.hpp"
using json = nlohmann::json;

void error(const char *msg){
    perror(msg);
    exit(1);
}

json read_configuration(){
  json j;
  std::ifstream i("config");
  if(i.good()){
    i >> j;
  }else{
    std::cout<< "Plik config nie istnieje lub jest błędny!!!"<<"\n";
    return 1;
  };
  i.close();
  std::cout<<"Konfiguracja serwera"<<"\n";
  std::cout<<"SOCKET Port: "<<j["SOCKETport"]<<"\n";
  std::cout<<"Prędkość transmisji rs485: "<<j["rs485speed"]<<"\n";
  std::cout<<"Port USB konwertera: "<<j["USBconverter"]<<"\n";
  return j;
}

int main(){

  json config;
  config = read_configuration();
  int sockfd, newsockfd, port_number, pid;
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("ERROR opening socket");
  bzero((char *) &serv_addr, sizeof(serv_addr));
  port_number = config["SOCKETport"];
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port_number);
  if (bind(sockfd, (struct sockaddr *) &serv_addr,
    sizeof(serv_addr)) < 0)
    error("ERROR on binding");
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   while (1) {
     newsockfd = accept(sockfd,
     (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0)
       error("ERROR on accept");
     pid = fork();
     if (pid < 0)
       error("ERROR on fork");
     if (pid == 0)  {
       close(sockfd);
       Prepare_Data p_data(config["USBconverter"], config["rs485speed"], newsockfd);
       exit(0);
       }
     else close(newsockfd);
     } /* end of while */
  close(sockfd);
  return 0;
}
