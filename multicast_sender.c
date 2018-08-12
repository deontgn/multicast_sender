#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cmd_package.h"


#define PORT 1589
#define GROUP "225.0.0.55"



int main(int argc, char *argv[])
{
	struct Command cmd;

	cmd.type = 1;
	cmd.who = 0x1001;
	cmd.to = 0x00001;
	cmd.cmd1 = 0x0002;
	cmd.cmd1_param[0] = 0x1001;
	cmd.cmd1_param[1] = 0x1001;
	cmd.cmd2 = 0;
	cmd.cmd2_param[0] = 0;
	cmd.cmd2_param[1] = 0;
	cmd.cmd3_param[0] = 0;
	cmd.cmd3_param[1] = 0;

	cmd.execute = 1;

	struct sockaddr_in addr;
	int fd, cnt;
	struct ip_mreq mreq;

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(GROUP);
	addr.sin_port = htons(PORT);


	while (1) {
		if (sendto(fd, &cmd, sizeof(cmd), 0, (struct sockaddr *) &addr,
				sizeof(addr)) < 0) {
			perror("sendto");
			exit(1);
		}
		sleep(1);
	}
}
