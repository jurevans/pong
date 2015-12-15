// pong.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <assert.h>

#include "pong.h"

int main(int argc, char *argv[])
{
	// Create NCURSES Screen
	initscr();
	noecho();
	curs_set(FALSE);

	struct Pong* _pong = Pong_create( 0, 0, 0, 0, 0, 0, 1, 1, "O" );

	// Main Loop:
	while(1) 
	{
		// Handle window resizes
		getmaxyx( stdscr, _pong->max_y, _pong->max_x );

		clear();
		mvprintw( _pong->y, _pong->x, _pong->element );
		refresh();

		usleep(DELAY);

		Pong_move(_pong);
	}

	endwin();

	/* Let's see where our guy ended up! */
	Pong_status(_pong);

	/* Then destroy it! */
	Pong_destroy(_pong);

	return 0;
}

struct Pong *Pong_create(	int x, int y,
				int max_x, int max_y,
				int next_x, int next_y,
				int x_direction, int y_direction,
				char* element )
{
	struct Pong *_pong = malloc(sizeof(struct Pong));

	assert(_pong != NULL);

	_pong->x 		= x;
	_pong->y 		= y;
	_pong->max_x		= max_x;
	_pong->max_y		= max_y;
	_pong->next_x 		= next_x;
	_pong->next_y 		= next_y;
	_pong->x_direction 	= x_direction;
	_pong->y_direction 	= y_direction;

	strcpy(_pong->element, element);

	return _pong;
}

void Pong_move(struct Pong* _pong)
{
	_pong->next_x = _pong->x + _pong->x_direction;
	_pong->next_y = _pong->y + _pong->y_direction;

	// Calculate for x-axis
	if(_pong->x >= _pong->max_x || _pong->next_x < 0) {
		_pong->x_direction *= -1;
	} else {
		_pong->x += _pong->x_direction;
	}

	// Calculate for y-axis
	if(_pong->y >= _pong->max_y || _pong->next_y < 0) {
		_pong->y_direction *= -1;
	} else {
		_pong->y += _pong->y_direction;
	}

}

void Pong_status(struct Pong* _pong)
{
	printf("\nx, y: (%d, %d)\n", _pong->x, _pong->y);
	printf("\nnext_x, next_y: (%d, %d)\n", _pong->next_x, _pong->next_y);
	printf("\nmax_x: %d, max_y: %d\n", _pong->max_x, _pong->max_y);
	printf("x axis direction: %s\n", _pong->x_direction < 0 ? "backwards" : "forwards");
	printf("y axis direction: %s\n", _pong->y_direction < 0 ? "backwards" : "forwards");
}

void Pong_destroy(struct Pong* _pong)
{
	assert(_pong != NULL);
	free(_pong);
}


