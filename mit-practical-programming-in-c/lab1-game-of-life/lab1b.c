/*
 * lab1b.c
 *
 *  Created on:
 *      Author:
 */

/* include helper functions for game */
#include "lifegame.h"

/* add whatever other includes here */

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* functions to implement -- can copy from Part A */

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

int main(int argc, char ** argv)
{
	int n;

	if (argc == 2)
		initialize_world_from_file(argv[1]);
	else
		initialize_world();



	for (n = 0; n < NUM_GENERATIONS; n++)
		next_generation();

	save_world_to_file("world.txt");

	return 0;
}

void next_generation(void) {
	for (int x = 0; x < get_world_width(); x++)
		for (int y = 0; y < get_world_height(); y++)
			set_cell_state(x, y, get_next_state(x, y));
	finalize_evolution();
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
