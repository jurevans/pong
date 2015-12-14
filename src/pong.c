// pong.c

#include <ncurses.h>
#include <unistd.h>
#include "pong.h"

int main(int argc, char *argv[])
{
	int x = 0,
            y = 0,
	    max_y = 0,
	    max_x = 0,
	    next_y = 0,
	    next_x = 0,
            x_direction = 1,
	    y_direction = 1;

	initscr();
	noecho();
	curs_set(FALSE);

	// Global var `stdscr` is created by call to `initscr()`


	while(1) 
	{
		// Handle window resizes:
		getmaxyx(stdscr, max_y, max_x);

		clear();
	
		mvprintw(y, x, "o");
		refresh();

		usleep(DELAY);
		
		next_x = x + x_direction;
		next_y = y + y_direction;

		if(next_x >= max_x || next_x < 0) {
			x_direction *= -1;
		} else {
			x += x_direction;
		}

		if(next_y >= max_y || next_y < 0) {
			y_direction *= -1;
		} else {
			y += y_direction;
		}
	}

	endwin();

	return 0;
}
