/* field.c - Library for drawing borders/Windows */

#include <unistd.h>
#include "include/field.h"

void borders_draw(WINDOW* screen)
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

	for( i = 1; i < (x - 1); ++i )
	{
		mvwprintw(screen, 0, i, BORDERS_X);
		mvwprintw(screen, y - 1, i, BORDERS_X);
	}
}

int key_pressed(void)
{
	int ch = getch();

	if (ch != ERR) {
		ungetch(ch);
		return 1;
	} else {
		return 0;
	}
}

void divider_draw( WINDOW *field )
{
	int field_max_y, field_max_x, i;

	getmaxyx( field, field_max_y, field_max_x );

	for(i = 0; i < field_max_y - SCORE_SIZE + 1; ++i)
	{
		mvwprintw(field, i + SCORE_SIZE - 2, (int)(field_max_x / 2), "|");
	}
}

