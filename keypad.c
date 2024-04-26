#include "keypad.h"

const struct ft8900r_keypad_button KEYPAD_BTN_D1 = KEYPAD_BTN_D1_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_D2 = KEYPAD_BTN_D2_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_D3 = KEYPAD_BTN_D3_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_DA = KEYPAD_BTN_DA_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_D4 = KEYPAD_BTN_D4_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_D5 = KEYPAD_BTN_D5_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_D6 = KEYPAD_BTN_D6_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_DB = KEYPAD_BTN_DB_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_D7 = KEYPAD_BTN_D7_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_D8 = KEYPAD_BTN_D8_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_D9 = KEYPAD_BTN_D9_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_DC = KEYPAD_BTN_DC_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_DS = KEYPAD_BTN_DS_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_D0 = KEYPAD_BTN_D0_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_DH = KEYPAD_BTN_DH_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_DD = KEYPAD_BTN_DD_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_P1 = KEYPAD_BTN_P1_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_P2 = KEYPAD_BTN_P2_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_P3 = KEYPAD_BTN_P3_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_P4 = KEYPAD_BTN_P4_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_UP = KEYPAD_BTN_UP_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_DN = KEYPAD_BTN_DN_VALUE;
const struct ft8900r_keypad_button KEYPAD_BTN_MM = KEYPAD_BTN_MM_VALUE;

void packet_set_keypad(struct ft8900r_head_packet *pkt, struct ft8900r_keypad_button *btn) {
  pkt->sw1 = btn->row;
  pkt->sw2 = btn->col;
}
