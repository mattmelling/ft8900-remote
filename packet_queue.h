#ifndef PACKET_QUEUE_H
#define PACKET_QUEUE_H

#include "packet.h"

void packet_queue_init();
void packet_queue_append(struct ft8900r_head_packet *msg);
int packet_queue_pop(struct ft8900r_head_packet *pkt);

#endif
