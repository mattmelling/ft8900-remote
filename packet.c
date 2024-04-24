#include <stdio.h>

#include "packet.h"

void print_packet(struct ft8900r_head_msg *pkt) {
  printf("ccl: %02x ", pkt->ccl);
  printf("ccr: %02x ", pkt->ccr);
  printf("ptt: %02x ", pkt->ptt);
  printf("rsq: %02x ", pkt->rsq);
  printf("rvl: %02x ", pkt->rvl);
  printf("sw1: %02x ", pkt->sw1);
  printf("lsq: %02x ", pkt->lsq);
  printf("lvl: %02x ", pkt->lvl);
  printf("sw2: %02x ", pkt->sw2);
  printf("prm: %02x ", pkt->prm);
  printf("plm: %02x ", pkt->plm);
  printf("flg: %02x ", pkt->flg);
  printf("hyp: %02x ", pkt->hyp);
  printf("\n");
}

int find_packet(uint8_t *buf, size_t len) {
  for(int i = 0; i < (len - sizeof(struct ft8900r_head_msg)); i++) {
    if(buf[i] & 0x80) {
      return i;
    }
  }
  return -1;
}
