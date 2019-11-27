CC=gcc
CFLAGS=-I -Wall -Wextra -g
DEPS = connector/connector.h thinker/thinker.h connector/mockgameserver.h connector/config.h \
	connector/boardmessageparser.h thinker/thinkertests/boardtests.h thinker/board.h \
	connector/connectorTests/connectortests.h
OBJ = main.o connector/connector.o thinker/thinker.o connector/mockgameserver.o \
	connector/config.o connector/boardmessageparser.o thinker/thinkertests/boardtests.o \
	thinker/board.h connector/connectorTests/connectortests.o
# todo, replace above with discoveries (find c files and replace extensions)

# these are the "legitimate" targets
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sysprak-client: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

play: $(OBJ) sysprak-client
ifeq ($(CONFIG_FILE),)
	./sysprak-client -g $(GAME_ID) -p $(PLAYER)
else
	./sysprak-client -g $(GAME_ID) -p $(PLAYER) -C $(CONFIG_FILE)
endif

# test target
test: $(OBJ) sysprak-client
	make -B && ./sysprak-client TEST

tests: $(OBJ) sysprak-client
	make -B && ./sysprak-client TEST




# these targets will connect to our mock server
x-helper-mock: $(OBJ) sysprak-client
ifeq ($(CONFIG_FILE),)
	./sysprak-client -g $(GAME_ID) -p $(PLAYER) -m 1
else
	./sysprak-client -g $(GAME_ID) -p $(PLAYER) -C $(CONFIG_FILE) -m 1
endif

mock-play: $(OBJ) sysprak-client
	GAME_ID=1234567890123 PLAYER=1 make x-helper-mock

mock-play-customconfig: $(OBJ) sysprak-client
	GAME_ID=1234567890123 PLAYER=1 CONFIG_FILE=client.conf make x-helper-mock

clean:
	rm -f $(OBJ) sysprak-client play

