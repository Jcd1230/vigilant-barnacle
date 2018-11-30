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

#define TOTAL 1 << 30 /* 2^24 */

struct quad_t {
	float a, b, c;
	float root;
};

int main(int argc, char **argv)
{
	FILE *fp;
	struct quad_t *quads;
	int i;

	fp = fopen("output_aos.txt", "w");
	if (!fp) { perror("couldn't open file error\n"); exit(1); }

	quads = malloc(sizeof(struct quad_t) * TOTAL); // get some bytes
	if (!quads) { perror("memory error\n"); exit(1); }

	srand(time(NULL)); // seed the RNG machine

	// set up some trash quadratics
	for (i = 0; i < TOTAL; i++) {
		quads[i].a = rand() % 100 - 50;
		quads[i].b = rand() % 100 - 50;
		quads[i].c = rand() % 100 - 50;
	}

	// perform the math
	for (i = 0; i < TOTAL; i++) {
		quads[i].root =
			(-quads[i].b + sqrt(quads[i].b * quads[i].b - (4 * quads[i].a * quads[i].c)) /
			 (2 * quads[i].a));
	}

	for (i = 0; i < TOTAL; i++) {
		fprintf(fp, "%6d  %f\n", i, quads[i].root);
	}

	fclose(fp);
	free(quads);

	return 0;
}


