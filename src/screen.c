/**
 * screen.c - Library for drawing message Windows 
 */

#include <string.h>
#include <unistd.h>

#include "include/pong.h"

void screen_draw(WINDOW* screen, char* message)
{
	int i;
	int max_x, max_y, next_x, next_y;

	// Because I like to be explicit on my strings
	char y_char[2] = {'|', '\0'};
	char x_char[2] = {'-', '\0'};

	getmaxyx( stdscr, max_y, max_x );

	int x_offset = (int)(max_x / X_Y_OFFSET);
	int y_offset = (int)(max_y / X_Y_OFFSET);

	next_x = x_offset;
	next_y = y_offset;

	// Place text in center of screen
	mvwprintw(screen, (int)(max_y / 2), (int)(max_x / 2) - (int)(strlen(message) / 2), message);
	wrefresh(screen);
	
	usleep(PRE_BORDER_DELAY);
	
	// Draw Sides

	// TOP
	for( i = 1; i < (max_x - (int)(x_offset * 2) + strlen(y_char)); ++i )
	{
		next_x++;

		mvwprintw(screen, y_offset, next_x, x_char);
		wrefresh(screen);


		usleep(CHAR_PRINT_DELAY);
	}

	// RIGHT
	
	for( i = 1; i < (max_y - (int)(y_offset * 2)) ; ++i )
	{
		next_y++;

		mvwprintw(screen, next_y, next_x, y_char);
		wrefresh(screen);

		usleep(CHAR_PRINT_DELAY);
	}

	// BOTTOM

	for( i = 1; i < (max_x - (int)(x_offset * 2) + strlen(y_char)); ++i )
	{

		mvwprintw(screen, next_y, next_x, x_char);
		wrefresh(screen);

		next_x--;

		usleep(CHAR_PRINT_DELAY);
	}

	// LEFT
	
	next_x += strlen(y_char);

	for( i = 1; i < (max_y - (int)(y_offset * 2) - strlen(x_char)); ++i )
	{
		next_y--;

		mvwprintw(screen, next_y, next_x, y_char);
		wrefresh(screen);

		usleep(CHAR_PRINT_DELAY);
	}

	sleep(2);

	wclear(screen);
	delwin(screen);
	wclear(stdscr);

}
