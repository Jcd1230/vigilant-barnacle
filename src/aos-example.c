/*
 * Brian Chrzanowski
 * Fri Nov 30, 2018 03:15
 *
 * Array of Structures
 *
 * Formal Example code, demonstrating DOD principles with
 * the quadratic formula (-b +- sqrt(b^2 - 4ac)) / 2a
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef DEFAULT_MAX
#define DEFAULT_MAX 1 << 24
#endif

struct quad_t {
	float a, b, c;
	float root;
};

int main(int argc, char **argv)
{
	struct quad_t *quads;
	int i;

	printf("Testing AoS with %ld elements\n", (unsigned long)DEFAULT_MAX);

	quads = malloc(sizeof(struct quad_t) * DEFAULT_MAX); // get some bytes
	if (!quads) { perror("memory error\n"); exit(1); }

	srand(time(NULL)); // seed the RNG machine

	// set up some trash quadratics
	for (i = 0; i < DEFAULT_MAX; i++) {
		quads[i].a = rand() % 100 - 50;
		quads[i].b = rand() % 100 - 50;
		quads[i].c = rand() % 100 - 50;
	}

	// perform the math
	for (i = 0; i < DEFAULT_MAX; i++) {
		quads[i].root =
			(-quads[i].b + sqrt(quads[i].b * quads[i].b - (4 * quads[i].a * quads[i].c)) /
			 (2 * quads[i].a));
	}

	free(quads);

	return 0;
}


