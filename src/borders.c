/* borders.c */
#include <unistd.h>
#include "borders.h"

int main(int argc, char *argv[]) 
{
	int parent_x, parent_y, new_x, new_y;
	int i;

	initscr();

	noecho();
	curs_set(FALSE);

	// Get max Window dimensions
	getmaxyx(stdscr, parent_y, parent_x);

	// Set up Windows
	WINDOW* field = newwin(parent_y - SCORE_SIZE, parent_x, SCORE_SIZE, 0);
	WINDOW* score = newwin(SCORE_SIZE, parent_x, 0, 0);

	while(1) 
	{
		getmaxyx(stdscr, new_y, new_x);
	
		if(new_y != parent_y || new_x != parent_x) {
			parent_x = new_x;
			parent_y = new_y;

			wresize(field, new_y - SCORE_SIZE, new_x);
			wresize(score, new_y - SCORE_SIZE, 0);
			refresh();

			draw_borders(field);
			draw_borders(score);

			wclear(stdscr);
			wclear(field);
			wclear(score);
		}

		// Draw to windows (This is where we write to "Field" in play mode)
		mvwprintw(field, 1, 1, "FIELD"); // Replace with PONG

		// Draw divider line:

		for(i = 0; i < parent_y - SCORE_SIZE - 2; ++i)
		{
			mvwprintw(field, i + SCORE_SIZE - 2, (int)(parent_x / 2), "|");
		}

		mvwprintw(score, 1, 1, "SCORE");

		mvwprintw(score, 1, (int)(parent_x / 2) - 5, "01");
		mvwprintw(score, 1, (int)(parent_x / 2) + 5, "02");
		mvwprintw(score, 1, (int)(parent_x / 2), "|");

		// Refresh
		wrefresh(field);
		wrefresh(score);

		refresh();

		draw_borders(field);
		draw_borders(score);
	}


	delwin(field);
	delwin(score);

	endwin();
	
	return 0;
}

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
