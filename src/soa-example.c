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

#define TOTAL 1 << 30 /* 2^30 */

struct quad_t {
	float *a;
	float *b;
	float *c;
	float *root;
};

int main(int argc, char **argv)
{
	FILE *fp;
	int i;
	struct quad_t quads;

	fp = fopen("output_soa.txt", "w");
	if (!fp) { perror("couldn't open file error\n"); exit(1); }

	/* we have to get some memory first */
	quads.a = malloc(sizeof(float) * TOTAL);
	quads.b = malloc(sizeof(float) * TOTAL);
	quads.c = malloc(sizeof(float) * TOTAL);
	quads.root = malloc(sizeof(float) * TOTAL);

	if (!quads.a || !quads.b || !quads.c || !quads.root) {
		 perror("memory error\n");
		 exit(1); 
	}

	srand(time(NULL)); // seed the RNG machine

	// set up some trash quadratics
	for (i = 0; i < TOTAL; i++) {
		quads.a[i] = rand() % 100 - 50;
		quads.b[i] = rand() % 100 - 50;
		quads.c[i] = rand() % 100 - 50;
	}

	// perform the math
	for (i = 0; i < TOTAL; i++) {
		quads.root[i] = 
			(-quads.b[i] +
			 sqrt(quads.b[i] * quads.b[i] - (4 * quads.a[i] * quads.c[i])) /
			 (2 * quads.a[i]));
	}

	for (i = 0; i < TOTAL; i++) {
		fprintf(fp, "%6d  %f\n", i, quads.root[i]);
	}

	fclose(fp);

	free(quads.a);
	free(quads.b);
	free(quads.c);
	free(quads.root);

	return 0;
}


