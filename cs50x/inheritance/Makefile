CC=gcc
INCDIRS=-I.
OPT=O0
CFLAGS=-Wall -Wextra -g -std=c11 -$(OPT) $(INCDIRS)

CFILES=*.c
BINARY=play

all: $(BINARY)

$(BINARY): $(CFILES)
	$(CC) $^ -o $@

clean:
	rm -rf $(BINARY)
