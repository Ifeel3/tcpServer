#include "utils.h"

void exit_error(char *string) {
	write(2, string, strlen(string));
	exit(EXIT_FAILURE);
}