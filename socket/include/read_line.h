#ifndef __READ_LINE
#define __READ_LINE

#include <sys/socket.h>

#include <stdio.h>

/* revc until encounter '\n' */
ssize_t read_line(int sockfd, void *buffer, size_t n, int flags);

#endif