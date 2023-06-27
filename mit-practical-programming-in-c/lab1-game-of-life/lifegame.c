/*
 * lifegame.c
 *
 *  Created on:
 *      Author:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "lifegame.h"

/* hard-coded world size */
#define WORLDWIDTH 39
#define WORLDHEIGHT 20

/* character representations of cell states */
#define CHAR_ALIVE '*'
#define CHAR_DEAD ' '

/* current cell states of the world */
static int world[WORLDWIDTH][WORLDHEIGHT];

/* next generation cell states */
static int nextstates[WORLDWIDTH][WORLDHEIGHT];

/* functions to write for Part B of lab */
void initialize_world_from_file(const char * filename)
{
	FILE *f;
	int c, state;
	int x = 0, y = 0;

	if ((f == fopen(filename, "r")) == NULL) {
		perror("fopen");
		abort();
	}

	for (int yi = 0; y < WORLDHEIGHT; yi++)
		for (int xi = 0; x < WORLDWIDTH; xi++)
			nextstates[xi][yi] = DEAD;


	while ((c = getc(f)) != EOF) {
		if (c == '\n') {
			if (x != WORLDWIDTH)
				fill_dead_width(x, y);
			x = 0;
			y++;
		} else if (c == CHAR_ALIVE || c == CHAR_DEAD) {
			world[x][y] = (c == CHAR_ALIVE) ? ALIVE : DEAD;
			x++;
		}
	}

	if (y != WORLDHEIGHT)
		fill_dead_height(x, y);

	fclose(f);
}

void fill_dead_height(int x, int y) {
	for (int yi = y; yi < WORLDHEIGHT; yi++)
		for (int xi = 0; xi < WORLDWIDTH; xi++)
			world[xi][yi] = DEAD;
}

void fill_dead_width(int x, int y) {
	for (int i = x; i < WORLDWIDTH; i++)
		world[i][y] = DEAD;
}

void save_world_to_file(const char * filename) {
	/* TODO: write the state of the world into a file with
	   name "filename". Assume the file can be created, or if
	   the file exists, overwrite the file. The ith character
	   of the jth line (zero-indexed) describes world[i][j]
	   using the characters CHAR_ALIVE and CHAR_DEAD

	   This file should be readable using the function
	   initialize_world_from_file(filename) above; we can use
	   it to resume a game later
	 */

	FILE *f;

	if ((f == fopen(filename, "r")) == NULL) {
		perror("fopen");
		abort();
	}

	for (int iy = 0; iy < WORLDHEIGHT; iy++) {
		for (int ix = 0; ix < WORLDWIDTH; ix++) {
			if (ix == WORLDWIDTH - 1)
				// putc('\n'
		}

	}



}

/* you shouldn't need to edit anything below this line */

/* initializes the world to a hard-coded pattern, and resets
   all the cells in the next generation to DEAD */
void initialize_world(void) {
	int i, j;

	for (i = 0; i < WORLDWIDTH; i++)
		for (j = 0; j < WORLDHEIGHT; j++)
			world[i][j] = nextstates[i][j] = DEAD;

	/* pattern "glider" */
	world[1][2] = ALIVE;
	world[3][1] = ALIVE;
	world[3][2] = ALIVE;
	world[3][3] = ALIVE;
	world[2][3] = ALIVE;
}

int get_world_width(void) {
	return WORLDWIDTH;
}

int get_world_height(void) {
	return WORLDHEIGHT;
}

int get_cell_state(int x, int y) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT)
		return DEAD;
	return world[x][y];
}

void set_cell_state(int x, int y, int state) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT) {
		fprintf(stderr,"Error: coordinates (%d,%d) are invalid.\n", x, y);
		abort();
	}
	nextstates[x][y] = state;
}

void finalize_evolution(void) {
	int x, y;
	for (x = 0; x < WORLDWIDTH; x++) {
		for (y = 0; y < WORLDHEIGHT; y++) {
			world[x][y] = nextstates[x][y];
			nextstates[x][y] = DEAD;
		}
	}
}

void output_world(void) {
	char worldstr[2*WORLDWIDTH+2];
	int i, j;

	worldstr[2*WORLDWIDTH+1] = '\0';
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
	for (i = 0; i <= 2*WORLDWIDTH; i+=2)
		worldstr[i] = '|';
	for (i = 0; i < WORLDHEIGHT; i++) {
		for (j = 0; j < WORLDWIDTH; j++)
			worldstr[2*j+1] = world[j][i] == ALIVE ? CHAR_ALIVE : CHAR_DEAD;
		puts(worldstr);
	}
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
}
