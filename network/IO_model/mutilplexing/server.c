#include <sock.h>
#include <errno.h>
#include "dlist.h"

typedef struct node
{
	struct list_head list;
	int clifd;
}*client;

void usage(const char *prog)
{
	fprintf(stderr, "Usage: %s <PORT>\n", prog);
	exit(1);
}

int main(int argc, char **argv)
{
	if(argc != 2)
		usage(argv[0]);

	int sockfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	int on = 1;
	Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);

	struct sockaddr_in srvaddr, cliaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(atoi(argv[1]));
	Bind(sockfd, (struct sockaddr *)&srvaddr, sizeof srvaddr);

	Listen(sockfd, 3);

	fd_set rset;
	int maxfd = sockfd;
	socklen_t len;
	
	client head = (client)malloc(sizeof(struct node));
	INIT_LIST_HEAD(&head->list);

	client pos, n;

	while(1)
	{

		FD_ZERO(&rset);
		FD_SET(sockfd, &rset);

		list_for_each_entry(pos, &head->list, list){

			FD_SET(pos->clifd, &rset);
			maxfd = maxfd>pos->clifd ? maxfd : pos->clifd;
		}

		select(maxfd+1, &rset, NULL, NULL, NULL);

		// new connection
		if(FD_ISSET(sockfd, &rset)){
			bzero(&cliaddr, sizeof cliaddr);
			len = sizeof cliaddr;
			int connfd = Accept(sockfd,
					(struct sockaddr *)&cliaddr,
					&len);

			printf("new connection: %s:%hu\n",
					inet_ntoa(cliaddr.sin_addr),
					ntohs(cliaddr.sin_port));

			client new = (client)malloc(sizeof(struct node));
			new->clifd = connfd;
			list_add(&new->list, &head->list);
		}

		// message from clients
		char buf[30];
		int nread;
		list_for_each_entry_safe(pos, n, &head->list, list){

			if(!FD_ISSET(pos->clifd, &rset))
				continue;

			bzero(buf, 30);

			nread = read(pos->clifd, buf, 30);

			if(!strncmp(buf, "quit", 4) || nread == 0){
				len = sizeof cliaddr;
				getpeername(pos->clifd,
					(struct sockaddr *)&cliaddr,
					&len);
				fprintf(stderr, "%s:%hu has quit.\n",
					inet_ntoa(cliaddr.sin_addr),
					ntohs(cliaddr.sin_port));
				list_del(&pos->list);
				free(pos);
				pos = NULL;
				continue;
			}

			// broadcast
			client tmp;
			list_for_each_entry(tmp, &head->list, list){
				if(tmp->clifd == pos->clifd)
					continue;

				Write(tmp->clifd, buf, strlen(buf));
			}
		}
	}

	return 0;
}
