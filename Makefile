CLIENT	= client
SERVER	= server
SRCC	= src/client.c src/utils.c
SRCS	= src/server.c src/utils.c
OBJC	= $(SRCC:%.c=%.o)
OBJS	= $(SRCS:%.c=%.o)
CC		= clang
CFLAGS	= -Wall -Werror -Wextra -std=c99

.PHONY: all clean fclean re

%.o: %.c
	$(CC) $(CFLAGS) -c $? -o $@

all: $(CLIENT) $(SERVER)

$(CLIENT): $(OBJC) src/utils.h
	$(CC) $(OBJC) -o $@

$(SERVER): $(OBJS) src/utils.h
	$(CC) $(OBJS) -o $@

clean:
	rm -f $(OBJS) $(OBJC)

fclean: clean
	rm -f $(CLIENT) $(SERVER)

re: fclean all