CC=gcc
CFLAGS=-I -Wall -Werror -Wextra
DEPS = connector/connector.h thinker/thinker.h connector/mockgameserver.h connector/config.h
OBJ = main.o connector/connector.o thinker/thinker.o connector/mockgameserver.o connector/config.o

# these are the "legitimate" targets
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sysprak-client: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

play: $(OBJ) sysprak-client
	./sysprak-client -g $(GAME_ID) -p $(PLAYER)

play-config-env: $(OBJ) sysprak-client
	./sysprak-client -g $(GAME_ID) -p $(PLAYER) -C client.conf

# these targets will connect to our mock server
mock-play: $(OBJ) sysprak-client
	./sysprak-client -g 1234567890123 -p 1 -m 1

mock-play-with-env-variables: $(OBJ) sysprak-client
	./sysprak-client GAME_ID=1234567890123 PLAYER=1 -g $(GAME_ID) -p $(PLAYER) -m 1

mock-play-with-config-file: $(OBJ) sysprak-client
	./sysprak-client GAME_ID=1234567890123 PLAYER=1 -g $(GAME_ID) -p $(PLAYER) -m 1 -z client.conf


clean:
	rm -f $(OBJ) sysprak-client play

