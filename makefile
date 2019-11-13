CC=gcc
CFLAGS=-I.
DEPS = connector/connector.h thinker/thinker.h
OBJ = main.o connector/connector.o thinker/thinker.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sysprak-client: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)