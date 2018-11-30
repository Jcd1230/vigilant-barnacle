/*
 * Brian Chrzanowski
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

#define OUTPUT_FILE "/dev/null"

struct extra_garbage_t {
	unsigned char R, G, B;
	char crazy_data[128];
};

struct quad_t {
	float *a;
	float *b;
	float *c;
	float *root;
	struct extra_garbage_t *garb;
};

int main(int argc, char **argv)
{
	int i, total_nans;
	struct quad_t quads;

	printf("Testing SoA with %ld elements\n", (unsigned long)DEFAULT_MAX);

	/* we have to get some memory first */
	quads.a = malloc(sizeof(float) * DEFAULT_MAX);
	quads.b = malloc(sizeof(float) * DEFAULT_MAX);
	quads.c = malloc(sizeof(float) * DEFAULT_MAX);
	quads.root = malloc(sizeof(float) * DEFAULT_MAX);
	quads.garb = malloc(sizeof(struct extra_garbage_t) * DEFAULT_MAX);

	if (!quads.a || !quads.b || !quads.c || !quads.root || !quads.garb) {
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

  // print all of the results
	for (i = 0, total_nans = 0; i < DEFAULT_MAX; i++) {
		if (quads.root[i] != quads.root[i]) { // check if it's NAN
			total_nans++;
		} 
	}
	printf("total nans : %d\n", total_nans);

	free(quads.a);
	free(quads.b);
	free(quads.c);
	free(quads.root);
	free(quads.garb);

	return 0;
}


