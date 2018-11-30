/*
 * Brian Chrzanowski
 * Demonstrating the values of Data Oriented Design
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>

// define some defaults
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define FPS 60
#define SCREEN_TICKS_PER_FRAME (1000 / FPS)
#define GET_TICKS(a) (SDL_GetTicks() - (a))

#define GRAVITY_PX 4

#define MAX_PARTICLES 100000

#ifndef DOD_VERSION
#define DOD_VERSION "Undef"
#endif

#define WINDOW_TITLE "Data Oriented Design V."DOD_VERSION
#define ERROR_AND_DIE(str) \
	fprintf(stderr, "%s:%d\t%s\n", __FILE__, __LINE__, (str)); exit(1);
/* JS_RANDFUNC : get random numbers just like Javascript */
#define JS_RANDFUNC() (((double)rand()) / ((double)RAND_MAX))

struct particle_t {
	unsigned long frame;
	int x;
	int y;
	double vx;
	double vy;
};
typedef struct particle_t part_t;

int init(SDL_Window **gWindow, SDL_Renderer **sRenderer);
int draw_screen(SDL_Renderer *render, struct particle_t *parts, int num,
		unsigned char colors[4]);
void update_parts(struct particle_t *parts, int total, int num);
void make_particles(struct particle_t *parts, int len);
void make_particle(struct particle_t *part);

int main(int argc, char **argv)
{
	SDL_Window *sWindow;
	SDL_Renderer *sRenderer;
	SDL_Event sEvent;
	int quit, curr_parts;
	unsigned int start_tick, frame_ticks;
	struct particle_t *parts;
	unsigned char colors[4] = {255, 100, 0, 255};

	parts = malloc(sizeof(struct particle_t) * MAX_PARTICLES);

	if (!parts) {
		fprintf(stderr, "not enough memory\n");
		exit(1);
	}

	srand(time(NULL));

	make_particles(parts, MAX_PARTICLES);
	curr_parts = MAX_PARTICLES / 2;
	quit = 0;

	if (init(&sWindow, &sRenderer)) {
		SDL_SetWindowTitle(sWindow, WINDOW_TITLE);
		SDL_RenderSetLogicalSize(sRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

		start_tick = SDL_GetTicks();

		while (!quit) {
			while (SDL_PollEvent(&sEvent)) {
				switch (sEvent.type) {
				case SDL_QUIT:
					quit = 1;
					break;
				}
			}

			// draw screen
			draw_screen(sRenderer, parts, curr_parts, colors);
			SDL_RenderPresent(sRenderer);
			update_parts(parts, MAX_PARTICLES, curr_parts);

			frame_ticks = GET_TICKS(start_tick);
			if (frame_ticks < SCREEN_TICKS_PER_FRAME) {
				SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
			}
		}

		SDL_DestroyRenderer(sRenderer);
		SDL_DestroyWindow(sWindow);

		SDL_Quit();

		free(parts);
	}

	return 0;
}

int init(SDL_Window **gWindow, SDL_Renderer **sRenderer)
{
	int success;

	success = 1;

		// init sdl
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "SDL couldn't initialize! SDL Error: %s\n",
				SDL_GetError());
		success = 0;
	}

	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT,
				SDL_WINDOW_RESIZABLE, gWindow, sRenderer)) {
		fprintf(stderr, "coulndn't get window, SDL Error: %s\n",
				SDL_GetError());
		success = 0;
	}

	return success;
}

/* update_parts : update particles and reinitialize those out of the range */
void update_parts(struct particle_t *parts, int total, int num)
{
	int i;

	for (i = 0; i < num; i++) { // handle gravity and the new position
		parts[i].x += parts[i].vx;
		parts[i].y += parts[i].vy;
		parts[i].vy += GRAVITY_PX;
	}

	// find those that need to be reinitialized in the presented range
	for (i = 0; i < num; i++) {
		if (parts[i].x < 0 || SCREEN_WIDTH < parts[i].x) {
			make_particle(parts + i);
		}

		// only reset if we've gone off of the bottom of the screen
		if (SCREEN_HEIGHT < parts[i].y) {
			make_particle(parts + i);
		}
	}

	// reinit everything else
	for (i = num; i < total; i++) {
		make_particle(parts + i);
	}
}

int draw_screen(SDL_Renderer *render, struct particle_t *parts, int num,
		unsigned char colors[4])
{
	int i, ret_val;

	ret_val = 0;

	SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
	SDL_RenderClear(render);
	SDL_SetRenderDrawColor(render, colors[0], colors[1], colors[2], colors[3]);

	for (i = 0; i < num; i++) {
		ret_val = SDL_RenderDrawLine(render,
						parts[i].x,
						parts[i].y,
						parts[i].x + parts[i].vx,
						parts[i].y + parts[i].vy);

		if (ret_val) {
			ERROR_AND_DIE(SDL_GetError());
		}
	}

	SDL_RenderPresent(render);

	return ret_val;
}

/* make_particles : init all of the particles */
void make_particles(struct particle_t *parts, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		make_particle(parts + i);
	}
}

/* make_particle : init just one particle */
void make_particle(struct particle_t *part)
{
	part->x = SCREEN_WIDTH / 2 + JS_RANDFUNC() * 50 - 25;
	part->y = SCREEN_HEIGHT;
	part->vx = JS_RANDFUNC() * 32 - 16;
	part->vy = JS_RANDFUNC() * 200 - 100;
}


