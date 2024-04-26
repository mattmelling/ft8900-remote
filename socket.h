#ifndef SOCKET_H
#define SOCKET_H

int socket_init();
size_t socket_read(int sock, char *buf, size_t n);
#endif
