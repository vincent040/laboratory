#include "common.h"

ssize_t Write(int fd, const void *buf, size_t nbyte)
{
	if(buf == NULL)
		return -1;

	const char *tmp = buf;
	ssize_t total   = 0;

	while(nbyte > 0)
	{
		ssize_t n = write(fd, tmp, nbyte);
		if(n == -1)
		{
			perror("write() error");
			return -1;
		}

		nbyte -= n;
		tmp   += n;
		total += n;
	}
	return total;
}


ssize_t Read(int fd, void *buf, size_t nbyte)
{
	if(buf == NULL)
		return -1;

	ssize_t n = read(fd, buf, nbyte);

	if(n == -1)
	{
		perror("read() error");
		return -1;
	}

	return n;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int ret = bind(sockfd, addr, addrlen);
	if(ret == -1)
	{
		perror("bind() error");
	}

	return ret;
}

int Listen(int sockfd, int backlog)
{
	int ret = listen(sockfd, backlog);
	if(ret == -1)
	{
		perror("listen() error");
	}

	return ret;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	int ret = accept(sockfd, addr, addrlen);
	if(ret == -1)
	{
		perror("accept() error");
	}

	return ret;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int connfd = connect(sockfd, addr, addrlen);
	if(connfd == -1)
	{
		perror("connect() error");
	}

	return connfd;
}

int Socket(int domain, int type, int protocol)
{
	int sockfd = socket(domain, type, protocol);
	if(sockfd == -1)
	{
		perror("socket() error");
	}

	return sockfd;
}

int Setsockopt(int sockfd, int level, int optname,
	       const void *optval, socklen_t optlen)
{
	int ret = setsockopt(sockfd, level, optname, optval, optlen);
	if(ret == -1)
	{
		perror("setsockopt() error");
	}

	return ret;
}

int Select(int nfds, fd_set *readfds, fd_set *writefds,
	   fd_set *exceptfds, struct timeval *timeout)
{
	int ret = select(nfds, readfds, writefds, exceptfds, timeout);
	if(ret == 0)
	{
		printf("select() timeout.\n");
	}
	else if(ret == -1)
	{
		perror("select() failed");
	}

	return ret;
}
