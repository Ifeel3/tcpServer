#include "utils.h"
#include <stdio.h>

void handler(int sig, siginfo_t *siginfo, void *unuse) {
	(void) sig;
	(void) siginfo;
	(void) unuse;
	exit(EXIT_SUCCESS);
}

int main(void) {
	struct sigaction catch;
	catch.sa_sigaction = handler;
	sigaction(SIGTERM, &catch, 0);
	sigaction(SIGHUP, &catch, 0);

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	int sock;
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		exit_error("Error: socket creation failed\n");
	if (bind(sock, (const struct sockaddr *)&addr, sizeof(addr)) == -1)
		exit_error("Error: bind failed\n");
	if (listen(sock, 10) != 0)
		exit_error("Error: listen failed\n");
	int sock_fd;
	socklen_t len = sizeof(addr);
	char buffer[256];
	while (1) {
		bzero(&buffer, 256);
		if ((sock_fd = accept(sock, (struct sockaddr *)&addr, &len)) < 0)
			exit_error("Error: accept error\n");
		read(sock_fd, &buffer,255);
		int file_fd = open(buffer, O_CREAT | O_TRUNC | O_WRONLY, 00666);
		bzero(&buffer, 256);
		write(sock_fd, "OK", 2);
		ssize_t readed;
		while ((readed = read(sock_fd, &buffer, 255))) {
			if (strcmp(buffer, "EOF") == 0) {
				close(file_fd);
				break;
			}
			write(file_fd, buffer, strlen(buffer));
			bzero(&buffer, 256);
			write(sock_fd, "NEXT", 4);
		}
		close(file_fd);
		if (readed == -1)
			exit_error("Error: problem?");
		}
	return 0;
}
