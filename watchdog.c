#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <stdio.h>

#include "watchdog.h"

FILE *wd_marker;
int watchdog_count = 0;

void watchdog_update() {
  watchdog_count++;
  if (watchdog_count % 32 == 0) {
    wd_marker = fopen(WATCHDOG_PATH, "w");
    fputc('1', wd_marker);
    fclose(wd_marker);
    watchdog_count = 0;
  }
}

#endif
