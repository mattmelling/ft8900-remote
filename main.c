#include <stdlib.h>
#include <stdio.h>

#include <errno.h>

#include <pthread.h>
#include <sys/queue.h>

#include "serial.h"
#include "packet.h"

int fd;

TAILQ_HEAD(msgqueue, ft8900r_head_msg_entry);
struct msgqueue msgq;

pthread_t thr_rx;
pthread_t thr_tx;
pthread_mutex_t lock;

int count = 0;


struct ft8900r_head_msg_entry {
  TAILQ_ENTRY(ft8900r_head_msg_entry) tailq;
  struct ft8900r_head_msg *message;
};

void *thr_rx_f(void *arg) {
  struct ft8900r_head_msg *pkt;
  struct ft8900r_head_msg_entry *entry;
  
  while(1) {
    pkt = read_packet(fd);
    if(pkt != NULL) {

      entry = malloc(sizeof(struct ft8900r_head_msg_entry));
      entry->message = pkt;

      pthread_mutex_lock(&lock);
      TAILQ_INSERT_TAIL(&msgq, entry, tailq);
      count++;
      pthread_mutex_unlock(&lock);
    }
  }
}

void *thr_tx_f(void *arg) {
  struct ft8900r_head_msg_entry *pkt = NULL;
  while(1) {
    pthread_mutex_lock(&lock);
    if(!TAILQ_EMPTY(&msgq)) {
      pkt = TAILQ_FIRST(&msgq);
      TAILQ_REMOVE(&msgq, pkt, tailq);
      count--;
    }
    pthread_mutex_unlock(&lock);

    if(pkt != NULL) {
      printf("cnt: %02d ", count);
      print_packet(pkt->message);
      write(fd, pkt->message, sizeof(struct ft8900r_head_msg));
      tcdrain(fd);
      free(pkt);
      free(pkt->message);
      pkt = NULL;
    }
  }
}

int main(int argc, char **argv) {
  fd = init_tty("/dev/ttyUSB0");
  
  TAILQ_INIT(&msgq);

  pthread_mutex_init(&lock, NULL);

  if(pthread_create(&thr_rx, NULL, thr_rx_f, NULL)) {
    perror("pthread_create rx");
    exit(1);
  }

  if(pthread_create(&thr_tx, NULL, thr_tx_f, NULL)) {
    perror("pthread_create tx");
    exit(1);
  }

  pthread_join(thr_rx, NULL);
}
