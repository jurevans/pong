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
	struct Pong* _pong = pong_create( 0, 0, 50, 50, 0, 0, 1, 1, "*" );

#if DEBUG_POSITION
	char status[10];
#endif
	init_screen(_pong);

	// Main Loop:
	while(1) 
	{
		// Handle window resizes
		getmaxyx( stdscr, _pong->max_y, _pong->max_x );

		clear();

#if DEBUG_POSITION	
		snprintf(status, sizeof(status), "%d,%d", _pong->x, _pong->y);
		mvwprintw(stdscr, 0, 0, status );
#endif
		mvprintw( _pong->y, _pong->x, _pong->element );

		refresh();

		usleep(DELAY);

		pong_next(_pong);
	}

	end_screen();

	/* Let's see where our guy ended up! */
	pong_status(_pong);

	pong_destroy(_pong);

	return 0;
}

void init_screen(struct Pong* _pong)
{
	// Create NCURSES Screen
	initscr();
	noecho();
	curs_set(FALSE);

	// Initialize x/y border max
	getmaxyx( stdscr, _pong->max_y, _pong->max_x );
}

struct Pong *pong_create(	int x, int y,
				int max_x, int max_y,
				int next_x, int next_y,
				int x_direction, int y_direction,
				char element[PONG_ELEMENT_SIZE] )
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

void pong_next(struct Pong* _pong)
{
	_pong->next_x = _pong->x + _pong->x_direction;
	_pong->next_y = _pong->y + _pong->y_direction;

	// Calculate for x-axis
	if(_pong->next_x >= _pong->max_x || _pong->next_x < 0) {
		_pong->x_direction *= -1;
	} else {
		_pong->x += _pong->x_direction;
	}

	// Calculate for y-axis
	if(_pong->next_y >= _pong->max_y || _pong->next_y < 0) {
		_pong->y_direction *= -1;
	} else {
		_pong->y += _pong->y_direction;
	}

}

void pong_status(struct Pong* _pong)
{
	printf("\nx, y: (%d, %d)\n", _pong->x, _pong->y);
	printf("\nnext_x, next_y: (%d, %d)\n", _pong->next_x, _pong->next_y);
	printf("\nmax_x: %d, max_y: %d\n", _pong->max_x, _pong->max_y);
	printf("x axis direction: %s\n", _pong->x_direction < 0 ? "backwards" : "forwards");
	printf("y axis direction: %s\n", _pong->y_direction < 0 ? "backwards" : "forwards");
}

void pong_destroy(struct Pong* _pong)
{
	// Release "malloc" allocated memory
	assert(_pong != NULL);
	free(_pong);
}

void end_screen()
{
	// End screen, window clean-up
	endwin();
}

