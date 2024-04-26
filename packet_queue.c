#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/queue.h>

#include "packet_queue.h"

struct packet_queue pktq;
pthread_mutex_t pktq_lock;

struct ft8900r_head_packet_entry {
  TAILQ_ENTRY(ft8900r_head_packet_entry) tailq;
  struct ft8900r_head_packet *packet;
};

TAILQ_HEAD(packet_queue, ft8900r_head_packet_entry);

void packet_queue_init() {
  TAILQ_INIT(&pktq);
  pthread_mutex_init(&pktq_lock, NULL);
}

void packet_queue_append(struct ft8900r_head_packet *pkt) {
  struct ft8900r_head_packet_entry *entry;

  entry = malloc(sizeof(struct ft8900r_head_packet_entry));
  entry->packet = malloc(sizeof(struct ft8900r_head_packet));
  memcpy(entry->packet, pkt, sizeof(struct ft8900r_head_packet));

  pthread_mutex_lock(&pktq_lock);
  TAILQ_INSERT_TAIL(&pktq, entry, tailq);
  pthread_mutex_unlock(&pktq_lock);
}

int packet_queue_pop(struct ft8900r_head_packet *pkt) {
  int ok = 0;
  struct ft8900r_head_packet_entry *entry;

  pthread_mutex_lock(&pktq_lock);
  if(!TAILQ_EMPTY(&pktq)) {
    entry = TAILQ_FIRST(&pktq);
    TAILQ_REMOVE(&pktq, entry, tailq);
    memcpy(pkt, entry->packet, sizeof(struct ft8900r_head_packet));
    free(entry->packet);
    free(entry);
    ok = 1;
  }
  pthread_mutex_unlock(&pktq_lock);

  return ok;
}
