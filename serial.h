#ifndef SERIAL_H
#define SERIAL_H

int init_tty(char *dev);
struct ft8900r_head_packet * read_packet(int fd);

#endif
