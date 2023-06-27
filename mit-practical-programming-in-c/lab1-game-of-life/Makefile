CC=gcc
INCDIRS=-I.
OPT=O0
CFLAGS=-Wall -Wextra -g  $(INCDIRS) $(OPT)

CFILES=lab1a.c lifegame.c
BINARY=live

all: $(BINARY)

$(BINARY): $(CFILES)
	$(CC) $^ -o $@

clean:
	rm -rf $(BINARY)
