#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>


#include "packet.h"




int init_tty(char *dev) {
  int fd = open(dev, O_RDWR | O_NOCTTY | O_SYNC);
  if (fd < 0) {
    perror("could not open port");
    exit(1);
  }

  struct termios tty;
  memset(&tty, 0, sizeof(tty));
  if (tcgetattr(fd, &tty) != 0) {
    perror("tcgetattr fail");
    exit(1);
  }

  cfsetospeed(&tty, B19200);
  cfsetispeed(&tty, B19200);

  tty.c_iflag &= ~(IGNBRK | IXON | IXOFF | IXANY);

  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8 bit chars
  tty.c_cflag &= ~(PARENB | PARODD); // no parity
  tty.c_cflag &= ~(CSTOPB | CRTSCTS); // 1 stop bit, disable RTS/CTS
  tty.c_cflag |= (CLOCAL | CREAD);

  tty.c_lflag = 0;
  tty.c_oflag = 0;

  tty.c_cc[VMIN] = 13; // non blocking
  tty.c_cc[VTIME] = 5; // 0.5s timeout

  if (tcsetattr(fd, TCSANOW, &tty) != 0) {
    perror("tcsetattr");
    exit(1);
  }

  return fd;
}
