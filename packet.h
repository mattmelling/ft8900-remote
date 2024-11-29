#include <stdint.h>
#include <stddef.h>

#ifndef PACKET_H
#define PACKET_H

struct __attribute__((__packed__)) ft8900r_head_packet {
  uint8_t ccl; // Left encoder
  uint8_t ccr; // Right encoder
  uint8_t ptt; // PTT ADC
  uint8_t rvl; // Right volume
  uint8_t rsq; // Right squelch
  uint8_t sw1; // SW1 keypad matrix row
  uint8_t lvl; // Left volumne
  uint8_t lsq; // Left squelch
  uint8_t sw2; // SW2 keypad matrix column
  uint8_t prm; // Panel right buttons
  uint8_t plm; // Panel left buttons
  uint8_t flg; // Flags
  uint8_t hyp; // Hyper buttons
};

void packet_print(struct ft8900r_head_packet *pkt);

// Look for packet in buf and return offset
int packet_find(uint8_t *buf, size_t len);

// Read a packet in to pkt and return 1 or return 0 if no packet read
int packet_read(int fd, struct ft8900r_head_packet *pkt);

void packet_init(struct ft8900r_head_packet *pkt);

#endif
