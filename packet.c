#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "packet.h"

void packet_print(struct ft8900r_head_packet *pkt) {
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

int packet_find(uint8_t *buf, size_t len) {
  for(int i = 0; i < len; i++) {
    if(buf[i] & 0x80) {
      return i;
    }
  }
  return -1;
}

int packet_read(int fd, struct ft8900r_head_packet *pkt) {
  uint8_t buf[13];
  memset(&buf, '\0', sizeof(buf));
  int n = read(fd, &buf, sizeof(buf));
  if(n == 0) {
    if(errno == EAGAIN) {
      return 0;
    }
    perror("read");
    exit(1);
  }

  if(n < 13) {
    return 0;
  }

  int offset = packet_find((void *)&buf, n);
  if(offset < 0) {
    return 0;
  }

  int t = sizeof(buf) - offset;
  if(t < sizeof(struct ft8900r_head_packet)) {
    return 0;
  }

  memcpy(pkt, &buf + offset, sizeof(struct ft8900r_head_packet));
  return n;
}

void packet_init(struct ft8900r_head_packet *pkt) {
  memset(pkt, '\0', sizeof(struct ft8900r_head_packet));
  pkt->ccl = 0x80;
  pkt->ccr = 0x00;
  pkt->ptt = 0x7f;
  pkt->prm = 0x7f;
  pkt->plm = 0x7f;
}
