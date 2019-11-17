CC=gcc
CFLAGS=-I -Wall -Werror -Wextra
DEPS = connector/connector.h thinker/thinker.h connector/mockgameserver.h
OBJ = main.o connector/connector.o thinker/thinker.o connector/mockgameserver.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sysprak-client: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)