#include <unistd.h>
#include <stdlib.h>

#include "command.h"
#include "packet.h"
#include "packet_queue.h"
#include "keypad.h"

#define packet_inject(pkt) {\
    for(int i = 0; i < 10; i++) {\
      packet_queue_append(pkt);\
    }\
}

void command_process_keypad(char *cmd) {
  struct ft8900r_keypad_button btn;
  struct ft8900r_head_packet pkt;
  switch(*cmd) {
  case '1':
    btn = KEYPAD_BTN_D1;
    break;
  case '2':
    btn = KEYPAD_BTN_D2;
    break;
  case '3':
    btn = KEYPAD_BTN_D3;
    break;
  case '4':
    btn = KEYPAD_BTN_D4;
    break;
  case '5':
    btn = KEYPAD_BTN_D5;
    break;
  case '6':
    btn = KEYPAD_BTN_D6;
    break;
  case '7':
    btn = KEYPAD_BTN_D7;
    break;
  case '8':
    btn = KEYPAD_BTN_D8;
    break;
  case '9':
    btn = KEYPAD_BTN_D9;
    break;
  case '0':
    btn = KEYPAD_BTN_D0;
    break;
  default:
    return;
  }

  // Key down
  packet_init(&pkt);
  packet_set_keypad(&pkt, &btn);
  packet_inject(&pkt);

  // Key up
  packet_init(&pkt);
  packet_queue_append(&pkt);
}

void command_process_hyper(char *cmd) {
  long hyper = strtol(cmd, NULL, 10);
  struct ft8900r_head_packet pkt;

  packet_init(&pkt);
  pkt.hyp = hyper;
  packet_inject(&pkt);
}

void command_process(char *cmd) {
  switch (*cmd) {
  case 'k':
    cmd++;
    while(*cmd != '\0') {
      command_process_keypad(cmd++);
      usleep(1000 * 500);
    }
    break;
  case 'h':
    command_process_hyper(++cmd);
    break;
  default:
    break;
  }
}
