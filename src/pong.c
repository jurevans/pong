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
#include "include/user.h"

int main(int argc, char *argv[]) 
{
	int parent_x, parent_y, new_x, new_y;
	int i;

	struct Ball* _ball = ball_create( 10, 10, 50, 50, 0, 0, 1, 1, "*" );
	struct User* _user_1 = user_create(0, "User 1");
	struct User* _user_2 = user_create(0, "User 2");

	char score_1[3];
	char score_2[3];

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

		// Draw divider line:

		for(i = 0; i < parent_y - SCORE_SIZE - 2; ++i)
		{
			mvwprintw(field, i + SCORE_SIZE - 2, (int)(parent_x / 2), "|");
		}


#if DEBUG_POSITION	
		snprintf(status, sizeof(status), "%d,%d", _ball->x, _ball->y);
		mvwprintw(stdscr, SCORE_SIZE + 1, BORDER_X_SIZE + 1, status );
#endif
	
		usleep(DELAY);

		ball_next(_ball);

		mvprintw( _ball->y + BORDER_Y_SIZE + SCORE_SIZE, _ball->x + BORDER_X_SIZE, _ball->element );

		if(_ball->next_x == _ball->max_x - BORDER_Y_SIZE)
			_user_1->score++;

		if(_ball->next_x < 0)
			_user_2->score++;

		// Get current scores:
	
		snprintf(score_1, 3, "%d", _user_1->score);
		snprintf(score_2, 3, "%d", _user_2->score);

		mvwprintw(score, 1, (int)(parent_x / 2) - 5, score_1);
		mvwprintw(score, 1, (int)(parent_x / 2) + 5, score_2);
		mvwprintw(score, 1, (int)(parent_x / 2), "|");

		mvwprintw(score, 1, (BORDER_Y_SIZE * 2), _user_1->username);
		mvwprintw(score, 1, parent_x - strlen(_user_2->username) - (BORDER_Y_SIZE * 2), _user_2->username);


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

	ball_status(_ball);

	/* CLEANUP */
	ball_destroy(_ball);
	user_destroy(_user_1);
	user_destroy(_user_2);

	
	return 0;
}

