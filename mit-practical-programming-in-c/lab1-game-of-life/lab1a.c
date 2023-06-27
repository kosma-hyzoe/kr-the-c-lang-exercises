/*
 * lab1a.c
 *
 *  Created on:
 *      Author:
 */
/* hard-coded world size */
#define WORLDWIDTH 39
#define WORLDHEIGHT 20

/* include helper functions for game */
#include "lifegame.h"

/* add whatever other includes here */

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* functions to implement */

/* this function should set the state of all
   the cells in the next generation and call
   finalize_evolution() to update the current
   state of the world to the next generation */
void next_generation(void);

/* this function should return the state of the cell
   at (x,y) in the next generation, according to the
   rules of Conway's Game of Life (see handout) */
int get_next_state(int x, int y);

/* this function should calculate the number of alive
   neighbors of the cell at (x,y) */
int num_neighbors(int x, int y);

int main(void)
{
	initialize_world();

	for (int n = 0; n < NUM_GENERATIONS; n++)
		next_generation();

	output_world();

	return 0;
}

void next_generation(void) {
	for (int x = 0; x < get_world_width(); x++)
		for (int y = 0; y < get_world_height(); y++)
			set_cell_state(x, y, get_next_state(x, y));
}

int get_next_state(int x, int y) {
	int s = get_cell_state(x, y), nn = num_neighbors(x, y);
	return s ? ((nn == 2 || nn == 3) ? ALIVE : DEAD) : nn == 3 ? ALIVE : DEAD;
}

int num_neighbors(int x, int y) {
	int nn = 0;
	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y - 1; j <= y + 1; j++)
			if (get_cell_state(i, j) == ALIVE && !(i == x && j == y))
					nn++;
	return nn;

}
