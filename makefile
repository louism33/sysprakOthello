CC=gcc
CFLAGS=-I -Wall -Werror -Wextra
DEPS = connector/connector.h thinker/thinker.h connector/mockgameserver.h
OBJ = main.o connector/connector.o thinker/thinker.o connector/mockgameserver.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sysprak-client: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

play: $(OBJ) sysprak-client
	./sysprak-client -g $(GAME_ID) -p $(PLAYER)

mock-play: $(OBJ) sysprak-client
	./sysprak-client -g 1234567890123 -p 1 -m 1

mock-play-with-env-variables: $(OBJ) sysprak-client
	./sysprak-client GAME_ID=1234567890123 PLAYER=1 -g $(GAME_ID) -p $(PLAYER) -m 1


clean:
	rm -f $(OBJ) sysprak-client play

