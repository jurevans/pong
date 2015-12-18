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
	struct Ball* _ball = ball_create( 0, 0, 50, 50, 0, 0, 1, 1, "*" );

#if DEBUG_POSITION
	char status[10];
#endif

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
		// Init Ball dimensions within Field
		getmaxyx( field, _ball->max_y, _ball->max_x );

		_ball->max_y -= (BORDER_Y_SIZE * 2);
		_ball->max_x -= (BORDER_X_SIZE * 2);
	
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

#if DEBUG_POSITION	
		snprintf(status, sizeof(status), "%d,%d", _ball->x, _ball->y);
		mvwprintw(stdscr, 1, 8, status );
#endif
	
		usleep(DELAY);

		ball_next(_ball);
		mvprintw( _ball->y + BORDER_Y_SIZE + SCORE_SIZE, _ball->x + BORDER_X_SIZE, _ball->element );

		// Refresh
		wrefresh(field);
		wrefresh(score);

		refresh();

		draw_borders(field);
		draw_borders(score);
	}


	delwin(field);
	delwin(score);

	ball_status(_ball);

	ball_destroy(_ball);

	

	endwin();
	
	return 0;
}

