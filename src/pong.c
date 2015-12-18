/* 
 * Pong
 * Version 0.1
 * pong.c
 * Author: Justin R. Evans
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <assert.h>

#include "include/field.h"
#include "include/ball.h"

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

/*
int main(int argc, char *argv[])
{
	struct Ball* _ball = ball_create( 0, 0, 50, 50, 0, 0, 1, 1, "*" );

#if DEBUG_POSITION
	char status[10];
#endif
	init_screen(_ball);

	// Main Loop:
	while(1) 
	{
		// Handle window resizes
		getmaxyx( stdscr, _ball->max_y, _ball->max_x );

		clear();

#if DEBUG_POSITION	
		snprintf(status, sizeof(status), "%d,%d", _ball->x, _ball->y);
		mvwprintw(stdscr, 0, 0, status );
#endif
		mvprintw( _ball->y, _ball->x, _ball->element );

		refresh();

		usleep(DELAY);

		ball_next(_ball);
	}

	end_screen();

	// Let's see where our guy ended up!
	ball_status(_ball);

	ball_destroy(_ball);

	return 0;
}
*/
