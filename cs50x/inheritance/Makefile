CC=gcc
INCDIRS=-I.
OPT=O0
CFLAGS=-Wall -Wextra -g  $(INCDIRS) $(OPT)

CFILES=*.c
BINARY=play

all: $(BINARY)

$(BINARY): $(CFILES)
	$(CC) $^ -o $@

clean:
	rm -rf $(BINARY)
