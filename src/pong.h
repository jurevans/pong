// pong.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <assert.h>

#ifndef DELAY
#define DELAY 30000
#endif

struct Pong {
	int x;
	int y;
	int max_x;
	int max_y;
	int next_x;
	int next_y;
	int x_direction;
	int y_direction;
	char* element;
};

struct Pong *Pong_create(	int x, int y, 
				int max_x, int max_y,
				int next_x, int next_y, 
				int x_direction, int y_direction, char* element );

void Pong_move(struct Pong* _pong);
void Pong_status(struct Pong* _pong);
void Pong_destroy(struct Pong* _pong);

