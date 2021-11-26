#include "utils.h"

int main(int argc, char **argv) {
	if (argc < 2 || argc > 2)
		exit_error("Error: bad arguments\n");

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);

	int sock;
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		exit_error("Error: socket creation failed\n");
	if (connect(sock, (const struct sockaddr *)&addr, sizeof(addr)) == -1)
		exit_error("Error: connection failed\n");
	else {
		int file_fd;

		if ((file_fd = open(argv[1], O_RDONLY)) == -1)
			exit_error("Error: file open failed\n");
		char buffer[256] = {0};
		char *file_name = strrchr(argv[1], '/');
		if (file_name == NULL)
			file_name = argv[1];
		write(sock, file_name, strlen(file_name));
		read(sock, &buffer, 255);
		bzero(buffer, 256);
		ssize_t readed;
		while ((readed = read(file_fd, &buffer, 255))) {
			if (readed == -1)
				break;
			write(sock, &buffer, 255);
			bzero(buffer, 256);
			read(sock, &buffer, 255);
			if (strcmp(buffer, "NEXT") == 0)
				continue;
		}
		close(sock);
		if (readed == -1) {
			exit_error("Error: file read error\n");
		}
		else {
			close(file_fd);
			write(sock, "EOF", 3);
		}
	}
	return (EXIT_SUCCESS);
}