#include <stdio.h>
#include <string.h>
#include <unistd.h> // provides close()
#include <arpa/inet.h> // provides inet_addr() and htons

int main() {
  int sd, cd; // server and client socket descriptor

  struct sockaddr_in sad, cad; // sad and cad are instances of sockaddr_in. They store client and server socket info

  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // AF_INET - IPv4; SOCK_STREAM - two way, connection based; IPPROTO_TCP - TCP connection

  sad.sin_family = AF_INET; // IPv4
  sad.sin_port = htons(9995); // convert integer from host byte order
  sad.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost IP

  bind(sd, (struct sockaddr*)&sad, sizeof(sad));
  listen(sd, 10);

  int cadl = sizeof(cad); // size of cad
  cd = accept(sd, (struct sockaddr*)&cad, &cadl);

  char s[50];

  recv(cd, s, sizeof(s), 0); // recieve
  printf("Client says: %s\n", s);

  close(sd);
  close(cd);

  return 0;
}