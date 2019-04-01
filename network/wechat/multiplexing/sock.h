#ifndef _SOCK_H_
#define _SOCK_H_

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>

#define MAXMSGLEN 1024

ssize_t Write(int fildes, const void *buf, size_t nbyte);
int Socket(int domain, int type, int protocol);
int Setsockopt(int sockfd, int level, int optname,
	       const void *optval, socklen_t optlen);

ssize_t Read(int fildes, void *buf, size_t nbyte);
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Select(int, fd_set *, fd_set *, fd_set *, struct timeval *);

#endif
