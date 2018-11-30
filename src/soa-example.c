/*
 * Brian Chrzanowski
 * Fri Nov 30, 2018 03:15
 *
 * Structure Of Arrays
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
	float *a;
	float *b;
	float *c;
	float *root;
};

int main(int argc, char **argv)
{
	int i;
	struct quad_t quads;

	printf("Testing SoA with %ld elements\n", (unsigned long)DEFAULT_MAX);

	/* we have to get some memory first */
	quads.a = malloc(sizeof(float) * DEFAULT_MAX);
	quads.b = malloc(sizeof(float) * DEFAULT_MAX);
	quads.c = malloc(sizeof(float) * DEFAULT_MAX);
	quads.root = malloc(sizeof(float) * DEFAULT_MAX);

	if (!quads.a || !quads.b || !quads.c || !quads.root) {
		 perror("memory error\n");
		 exit(1); 
	}

	srand(time(NULL)); // seed the RNG machine

	// set up some trash quadratics
	for (i = 0; i < DEFAULT_MAX; i++) {
		quads.a[i] = rand() % 100 - 50;
		quads.b[i] = rand() % 100 - 50;
		quads.c[i] = rand() % 100 - 50;
	}

	// perform the math
	for (i = 0; i < DEFAULT_MAX; i++) {
		quads.root[i] = 
			(-quads.b[i] +
			 sqrt(quads.b[i] * quads.b[i] - (4 * quads.a[i] * quads.c[i])) /
			 (2 * quads.a[i]));
	}

	free(quads.a);
	free(quads.b);
	free(quads.c);
	free(quads.root);

	return 0;
}


