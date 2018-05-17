#include "sock.h"
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

#include "dlist.h"
#include "head4qq.h"

#define MAXSIZE 80

void usage(const char *info)
{
	printf("Usage: %s <PORT>\n", info);
	exit(0);
}

void catch_sig(int sig)
{
	if(sig == SIGCHLD){
		while(waitpid(-1, NULL, WNOHANG) > 0)
			printf("(%03d)child exit\n", childnum--);
	}
}

void init_client(client **phead)
{
	*phead = (client *)malloc(sizeof(client));

	(*phead)->cli_count = 0;
	INIT_LIST_HEAD(&((*phead)->list));
}

int main(int argc, char **argv)
{
	if(argc != 2)
		usage(argv[0]);

	int sockfd;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	int on = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);

	struct sockaddr_in srvaddr, cliaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(atoi(argv[1]));

	Bind(sockfd, (struct sockaddr *)&srvaddr,
		sizeof srvaddr);

	Listen(sockfd, 5);

	int connfd;
	socklen_t len;
	char recv[MAXSIZE];

	pid_t pid;
	len = sizeof cliaddr;

	signal(SIGCHLD, catch_sig);

	client *head;
	init_client(&head);

	int nread = -1;
	int maxfd = -1;
	struct list_head *pos;
	node *tmp;
	char buf[MAXSIZE];

	fd_set rset;

	while(1){
		FD_ZERO(&rset);
		FD_SET(sockfd, &rset);
		maxfd = sockfd;

		list_for_each(pos, &(head->list)){
			tmp = list_entry(pos, node, list);
			FD_SET(tmp->clifd, &rset);
			maxfd = (maxfd>tmp->clifd)?maxfd:tmp->clifd;
		}


		select(maxfd + 1, &rset, NULL, NULL, NULL);

		// a new connection
		if(FD_ISSET(sockfd, &rset) > 0){
			bzero(&cliaddr, len);
			connfd = Accept(sockfd,
				(struct sockaddr*)&cliaddr, &len);
	
			printf("(%03d)new connection: %s:%hu (fd:%d)\n",
				childnum++,
				inet_ntoa(cliaddr.sin_addr),
				cliaddr.sin_port,
				connfd);

			// add the new client to the list
			tmp = (node *)malloc(sizeof(node));
			tmp->clifd = connfd;
			list_add_tail(&(tmp->list), &(head->list));
			head->cli_count++;
		}
		// check which client has new msg
		struct list_head *n;
		list_for_each_safe(pos, n, &(head->list)){
			tmp = list_entry(pos, node, list);

			if(FD_ISSET(tmp->clifd, &rset) > 0){

				bzero(recv, MAXSIZE);
				while(((nread=read(tmp->clifd, recv, MAXSIZE)) <= 0)
						&& (errno == EINTR));

				// client has entered "quit" or logout
				if(!strncmp("quit", recv, 4) ||
						nread == 0){
					cli_logout(head, tmp);
					continue;
				}

				// client has entered a msg
				else{
					broadcast_msg(head, tmp->clifd,
						recv, strlen(recv));
				}
			}
		}
	}

	return 0;
}
