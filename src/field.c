/* field.c - Library for drawing borders/Windows */

#include <unistd.h>
#include "include/field.h"

void draw_borders(WINDOW *screen)
{
	int x, y, i;

	getmaxyx(screen, y, x);

	// Draw 4 Corners

	mvwprintw(screen, 0, 0, CORNERS);
	mvwprintw(screen, y - 1, 0, CORNERS);
	mvwprintw(screen, 0, x - 1, CORNERS);
	mvwprintw(screen, y - 1, x - 1, CORNERS);
	
	// Draw Sides

	for( i = 1; i < (y - 1); ++i )
	{
		mvwprintw(screen, i, 0, BORDERS_Y);
		mvwprintw(screen, i, x - 1, BORDERS_Y);
	}

	// Draw Top/Bottom

	for( i = 1; i < (x - 1); ++i)
	{
		mvwprintw(screen, 0, i, BORDERS_X);
		mvwprintw(screen, y - 1, i, BORDERS_X);
	}
}
