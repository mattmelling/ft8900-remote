#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "socket.h"

struct sockaddr_in addo;

/*
 * Create socket and bid to ADDR:PORT
 */
int socket_init(long port) {

  struct sockaddr_in addr;
  int sock, flags;

  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
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

size_t socket_read(int sock, char *buf, size_t n) {
  int slen = sizeof(addo);
  int r = recvfrom(sock, buf, n, 0, (struct sockaddr *)&addo, &slen);
  if(r == -1 && errno != EAGAIN) {
    perror("recvfrom");
    exit(1);
  }
  if(r > 0) {
    return r;
  }
  return 0;
}
