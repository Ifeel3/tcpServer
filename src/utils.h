#ifndef UTILS_H
# define UTILS_H
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <string.h>
# include <fcntl.h>

# define PORT 21042

void exit_error(char *sting);

#endif