#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define ADDR "127.0.0.1"
#define PORT 1234


// set up udp socket as unblocking
// listen and loop checking for chars received


struct sockaddr_in addo;


/*
 * Create socket and bid to ADDR:PORT
 */
int create_socket() {

  struct sockaddr_in addr;
  int sock, flags;

  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    perror("could not create socket");
    exit(1);
  }

  if ((flags = fcntl(sock, F_GETFL)) == -1) {
    perror("could not get socket flags");
    exit(1);
  }

  if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) == -1) {
    perror("could not set socket flags");
    exit(1);
  }

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("could not bind socket");
    exit(1);
  }

  return sock;
}

int main(int argc, char **argv) {

  memset(&addo, '\0', sizeof(addo));

  

  int slen = sizeof(addo);
  
  char buf[32];
  socklen_t addr_size;

  int sock = create_socket();

  int r = 0;

  while(1) {
    r = recvfrom(sock, buf, 32, 0, (struct sockaddr *)&addo, &slen);
    if (r == -1 && errno != EAGAIN) {
      perror("could not recv from socket");
      exit(1);
    }
    if (r > 0) {
      printf("%s\n", buf);
    }
  }
  
  
  /* memset(&addr, '\0', sizeof(si_me)); */
  /* addr.sin_family = AF_INET; */
  /* addr.sin_port = htons(PORT); */
  /* addr.sin_addr.s_addr = inet_addr("127.0.0.1"); */

  /* fcntl(sockfd, F_SETFL, flags | O_NONBLOCK); */
  
  /* bind(sockfd, (struct sockaddr*)&addr, sizeof(si_me)); */
  /* addr_size = sizeof(addo); */

  /* recvfrom(sockfd, buf, 32, 0, (struct sockaddr*)&addo, &addr_size); */
  /* printf("DATA: %s\n"); */

  return 0;
}
