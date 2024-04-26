#ifndef KEYPAD_H
#define KEYPAD_H

#include "packet.h"

struct ft8900r_keypad_button {
  uint8_t row;
  uint8_t col;
};

#define KEYPAD_ROW_0 0x03
#define KEYPAD_ROW_1 0x19
#define KEYPAD_ROW_2 0x32
#define KEYPAD_ROW_3 0x4c

#define KEYPAD_COL_0 0x1b
#define KEYPAD_COL_1 0x33
#define KEYPAD_COL_2 0x4c
#define KEYPAD_COL_3 0x66

#define KEYPAD_BTN_D1_VALUE { KEYPAD_ROW_0, KEYPAD_COL_0 }
#define KEYPAD_BTN_D2_VALUE { KEYPAD_ROW_0, KEYPAD_COL_1 }
#define KEYPAD_BTN_D3_VALUE { KEYPAD_ROW_0, KEYPAD_COL_2 }
#define KEYPAD_BTN_DA_VALUE { KEYPAD_ROW_0, KEYPAD_COL_3 }
#define KEYPAD_BTN_D4_VALUE { KEYPAD_ROW_1, KEYPAD_COL_0 }
#define KEYPAD_BTN_D5_VALUE { KEYPAD_ROW_1, KEYPAD_COL_1 }
#define KEYPAD_BTN_D6_VALUE { KEYPAD_ROW_1, KEYPAD_COL_2 }
#define KEYPAD_BTN_DB_VALUE { KEYPAD_ROW_1, KEYPAD_COL_3 }
#define KEYPAD_BTN_D7_VALUE { KEYPAD_ROW_2, KEYPAD_COL_0 }
#define KEYPAD_BTN_D8_VALUE { KEYPAD_ROW_2, KEYPAD_COL_1 }
#define KEYPAD_BTN_D9_VALUE { KEYPAD_ROW_2, KEYPAD_COL_2 }
#define KEYPAD_BTN_DC_VALUE { KEYPAD_ROW_2, KEYPAD_COL_3 }
#define KEYPAD_BTN_DS_VALUE { KEYPAD_ROW_3, KEYPAD_COL_0 }
#define KEYPAD_BTN_D0_VALUE { KEYPAD_ROW_3, KEYPAD_COL_1 }
#define KEYPAD_BTN_DH_VALUE { KEYPAD_ROW_3, KEYPAD_COL_2 }
#define KEYPAD_BTN_DD_VALUE { KEYPAD_ROW_3, KEYPAD_COL_3 }
#define KEYPAD_BTN_P1_VALUE { KEYPAD_ROW_3, KEYPAD_COL_0 }
#define KEYPAD_BTN_P2_VALUE { KEYPAD_ROW_3, KEYPAD_COL_1 }
#define KEYPAD_BTN_P3_VALUE { KEYPAD_ROW_3, KEYPAD_COL_2 }
#define KEYPAD_BTN_P4_VALUE { KEYPAD_ROW_3, KEYPAD_COL_3 }
#define KEYPAD_BTN_UP_VALUE { 0x1e, 0x06 }
#define KEYPAD_BTN_DN_VALUE { 0x35, 0x06 }
#define KEYPAD_BTN_MM_VALUE { 0x64, 0x03 }

extern const struct ft8900r_keypad_button KEYPAD_BTN_D1;
extern const struct ft8900r_keypad_button KEYPAD_BTN_D2;
extern const struct ft8900r_keypad_button KEYPAD_BTN_D3;
extern const struct ft8900r_keypad_button KEYPAD_BTN_DA;
extern const struct ft8900r_keypad_button KEYPAD_BTN_D4;
extern const struct ft8900r_keypad_button KEYPAD_BTN_D5;
extern const struct ft8900r_keypad_button KEYPAD_BTN_D6;
extern const struct ft8900r_keypad_button KEYPAD_BTN_DB;
extern const struct ft8900r_keypad_button KEYPAD_BTN_D7;
extern const struct ft8900r_keypad_button KEYPAD_BTN_D8;
extern const struct ft8900r_keypad_button KEYPAD_BTN_D9;
extern const struct ft8900r_keypad_button KEYPAD_BTN_DC;
extern const struct ft8900r_keypad_button KEYPAD_BTN_DS;
extern const struct ft8900r_keypad_button KEYPAD_BTN_D0;
extern const struct ft8900r_keypad_button KEYPAD_BTN_DH;
extern const struct ft8900r_keypad_button KEYPAD_BTN_DD;
extern const struct ft8900r_keypad_button KEYPAD_BTN_P1;
extern const struct ft8900r_keypad_button KEYPAD_BTN_P2;
extern const struct ft8900r_keypad_button KEYPAD_BTN_P3;
extern const struct ft8900r_keypad_button KEYPAD_BTN_P4;
extern const struct ft8900r_keypad_button KEYPAD_BTN_UP;
extern const struct ft8900r_keypad_button KEYPAD_BTN_DN;
extern const struct ft8900r_keypad_button KEYPAD_BTN_MM; 

void packet_set_keypad(struct ft8900r_head_packet *pkt, struct ft8900r_keypad_button *btn); 

#endif
