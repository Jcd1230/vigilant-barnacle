/*
 * Brian Chrzanowski
 * Array of Structures
 *
 * demonstrates how mallocing every item, one at a time is real slow
 * then the data becomes even more fragmented
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef DEFAULT_MAX
#define DEFAULT_MAX 1 << 24
#endif

struct extra_garbage_t {
	unsigned char R, G, B;
	char crazy_data[128];
};

struct quad_t {
	float a, b, c;
	float root;
	struct extra_garbage_t garb;
};

int main(int argc, char **argv)
{
	struct quad_t **quads;
	int i, total_nans;

	printf("Testing AoS with %ld elements\n", (unsigned long)DEFAULT_MAX);

	quads = malloc(sizeof(struct quad_t *) * DEFAULT_MAX); // get the outer set of pointers
	if (!quads) { perror("memory error\n"); exit(1); }

	for (i = 0; i < DEFAULT_MAX; i++) {
		quads[i] = malloc(sizeof(struct quad_t));
		if (!quads) { perror("memory error\n"); exit(1); }
	}

	srand(time(NULL)); // seed the RNG machine

	// set up some trash quadratics
	for (i = 0; i < DEFAULT_MAX; i++) {
		quads[i]->a = rand() % 100 - 50;
		quads[i]->b = rand() % 100 - 50;
		quads[i]->c = rand() % 100 - 50;
	}

	// perform the math
	for (i = 0; i < DEFAULT_MAX; i++) {
		quads[i]->root =
			(-quads[i]->b + sqrt(quads[i]->b * quads[i]->b - (4 * quads[i]->a * quads[i]->c)) /
			 (2 * quads[i]->a));
	}

	// print all of the results
	for (i = 0, total_nans = 0; i < DEFAULT_MAX; i++) {
		if (quads[i]->root != quads[i]->root) { // check if it's NAN
			total_nans++;
		} 
	}
	printf("total nans : %d\n", total_nans);

	for (i = 0; i < DEFAULT_MAX; i++) {
		free(quads[i]);
	}
	free(quads);

	return 0;
}


