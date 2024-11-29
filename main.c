#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/queue.h>
#include <unistd.h>
#include <termios.h>

#include "serial.h"
#include "packet.h"
#include "socket.h"
#include "packet_queue.h"
#include "keypad.h"
#include "command.h"

int fd;
int sock;

// Serial reader thread
void *thr_rx_f(void *arg) {
  struct ft8900r_head_packet pkt;
  while(1) {
    if(packet_read(fd, &pkt)) {
      packet_queue_append(&pkt);
    }
    usleep(1);
  }
}

// Serial writer thread
void *thr_tx_f(void *arg) {
  struct ft8900r_head_packet pkt;
  while(1) {
    if(packet_queue_pop(&pkt)) {
      write(fd, &pkt, sizeof(struct ft8900r_head_packet));
    }
    usleep(1);
  }
}

// Socket thread
void *thr_sock_f(void *arg) {
  char buf[32];
  size_t n = 0;

  while(1) {
    memset(&buf, '\0', sizeof(buf));
    n = socket_read(sock, (char *)&buf, sizeof(buf));
    if(n > 0) {
      command_process((char *)&buf);
    }
    usleep(1000 * 10);
  }
}

int main(int argc, char **argv) {

  char *dev = getenv("FT8900R_DEVICE");
  fd = init_tty(dev);

  char *ports = getenv("FT8900R_PORT");
  long port = strtol(ports, NULL, 10);

  sock = socket_init(port);
  packet_queue_init();

  pthread_t thr_rx;
  if(pthread_create(&thr_rx, NULL, thr_rx_f, NULL)) {
    perror("pthread_create rx");
    exit(1);
  }

  pthread_t thr_tx;
  if(pthread_create(&thr_tx, NULL, thr_tx_f, NULL)) {
    perror("pthread_create tx");
    exit(1);
  }

  pthread_t thr_sock;
  if(pthread_create(&thr_sock, NULL, thr_sock_f, NULL)) {
    perror("pthread_create socket");
    exit(1);
  }

  pthread_join(thr_rx, NULL);
}
