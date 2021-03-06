CC=gcc

### production:
CFLAGS=-I -Wall -Wextra -Werror -std=gnu11 -lm -lpthread -DNDEBUG

#CFLAGS=-I -Wall -Wextra -Werror -g -std=gnu11 -lm -lpthread -DNDEBUG
# CFLAGS=-I -Wall -Wextra -Werror -g -std=gnu11 -lm -lpthread

#todo -DNDEBUG  will disable assserts
#todo remove -g
# todo -pg makes callgrind possible but profiling timer expired for valgrind
DEPS = main.h connector/connector.h thinker/thinker.h  connector/config.h \
	connector/boardmessageparser.h thinker/thinkertests/boardtests.h  thinker/board.h \
	connector/connectorTests/connectortests.h thinker/thinkertests/unmakemovetests.h thinker/thinkertests/makemovetests.h \
	thinker/thinkertests/perft.h thinker/thinkertests/biggerboardtest.h  shm/shm.c pipe/pipe.c \
	ki/alex.h ki/kitests/testkisimple.h \
    	ki/kitests/testkibasicthinking.h ki/kitests/testkibasicstrategy.h
OBJ = main.o connector/connector.o thinker/thinker.o  \
	connector/config.o connector/boardmessageparser.o thinker/thinkertests/boardtests.o \
	 connector/connectorTests/connectortests.o thinker/thinkertests/unmakemovetests.o thinker/thinkertests/makemovetests.o \
	 thinker/thinkertests/perft.o thinker/thinkertests/biggerboardtest.o shm/shm.o pipe/pipe.o \
	 ki/alex.o ki/kitests/testkisimple.o \
     	 ki/kitests/testkibasicthinking.o ki/kitests/testkibasicstrategy.o
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

# in case we get timeouts
playtime: $(OBJ) sysprak-client
ifeq ($(CONFIG_FILE),)
	./sysprak-client -g $(GAME_ID) -p $(PLAYER) -t $(TIME_OFFSET)
else
	./sysprak-client -g $(GAME_ID) -p $(PLAYER) -C $(CONFIG_FILE) -t $(TIME_OFFSET)
endif

# perft target
perft: $(OBJ) sysprak-client
	make -B && ./sysprak-client perft ${DEPTH}

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
