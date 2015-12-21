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
#include "include/paddle.h"

int main(int argc, char *argv[]) 
{
	int parent_x, parent_y, new_x, new_y;
	int i;

	struct Ball* _ball = ball_create( 10, 10, 50, 50, 0, 0, 1, 1, "*" );
	struct User* _user_1 = user_create(0, "User 1", 1);
	struct User* _user_2 = user_create(0, "User 2", 0);
	struct Paddle* _paddle_1 = paddle_create(0, 0, 0, 2, PADDLE_CHAR);
	struct Paddle* _paddle_2 = paddle_create(0, 0, 0, 2, PADDLE_CHAR);

	char score_1[3];
	char score_2[3];

#if DEBUG_POSITION
	char status[10];
#endif

	printf("\nEnter username for Player 1: ");
	scanf("%s", _user_1->username);
	printf("\nEnter username for Player 2: ");
	scanf("%s", _user_2->username);
	printf("\n");


	// BEGIN PONG
	initscr();

	noecho();
	curs_set(FALSE);

	// Get max Window dimensions
	getmaxyx(stdscr, parent_y, parent_x);

	_paddle_1->x_pos = (BORDER_X_SIZE * 2);
	_paddle_2->x_pos = parent_x - (BORDER_X_SIZE * 2);

	// Set up Windows
	WINDOW* intro = newwin(0, 0, 0, 0);
	WINDOW* outro = newwin(0, 0, 0, 0);
	WINDOW* field = newwin(parent_y - SCORE_SIZE, parent_x, SCORE_SIZE, 0);
	WINDOW* score = newwin(SCORE_SIZE, parent_x, 0, 0);

	// Intro

	/* SEPARATE THE FOLLOWING INTO SEPERATE FUNCTION FOR DRAWING SCREENS
         *  - Intro
         *  - Score
         *  - Replay/Exit
         */
	mvwprintw(intro, (int)(parent_y / 2), (int)(parent_x / 2) - (int)(strlen("PONG") / 2), "PONG");
	wrefresh(intro);
	sleep(2);
	wclear(intro);
	delwin(intro);
	wclear(stdscr);

	// Main game loop
	while( _user_1->score < MAX_SCORE && _user_2->score < MAX_SCORE ) 
	{
		// Draw divider line:

		for(i = 0; i < parent_y - SCORE_SIZE - 2; ++i)
		{
			mvwprintw(field, i + SCORE_SIZE - 2, (int)(parent_x / 2), "|");
		}

		getmaxyx(stdscr, new_y, new_x);

		// Init Ball dimensions within Field
		getmaxyx( field, _ball->max_y, _ball->max_x );

		// Paddle height: ~33% height of field
		_paddle_1->height = (int)(new_y - (BORDER_Y_SIZE * 2) / 3);
		_paddle_2->height = (int)(new_y - (BORDER_Y_SIZE * 2) / 3);
		

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



#if DEBUG_POSITION	
		snprintf(status, sizeof(status), "%d,%d", _ball->x, _ball->y);
		mvwprintw(stdscr, SCORE_SIZE + 1, BORDER_X_SIZE + 1, status );
#endif
	
		usleep(DELAY);

		ball_next(_ball);

		mvprintw( _ball->y + BORDER_Y_SIZE + SCORE_SIZE, _ball->x + BORDER_X_SIZE, _ball->element );

		_paddle_1->height = (int)(_ball->max_y / 3);
		_paddle_1->y_pos = (int)((int)(_ball->max_y / 2) - (int)(_paddle_1->height / 2));
		_paddle_1->x_pos = BORDER_Y_SIZE;

		paddle_draw(field, _paddle_1);

		_paddle_2->height = (int)(_ball->max_y / 3);
		_paddle_2->y_pos = (int)((int)(_ball->max_y / 2) - (int)(_paddle_1->height / 2));
		_paddle_2->x_pos = _ball->max_x - _paddle_2->width - BORDER_Y_SIZE;

		paddle_draw(field, _paddle_2);


		if(_ball->next_x == _ball->max_x - BORDER_Y_SIZE)
		{
			_user_1->score++;

			
			_ball->y = 0;
			_ball->x = 0;

			_user_1->turn = 1;
			_user_2->turn = 0;
		}

		if(_ball->next_x < 0)
		{
			_user_2->score++;

			_ball->y = 0;
			_ball->x = _ball->max_x - BORDER_X_SIZE;

			_user_2->turn = 1;
			_user_1->turn = 0;

		}

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

	// Outro

	/* SEPARATE THE FOLLOWING INTO SEPERATE FUNCTION FOR DRAWING SCREENS
         *  - Intro
         *  - Score
         *  - Replay/Exit
         */
/*
	char* winner = (_user_1->score > _user_2->score) ? _user_1->username : _user_2->username;
	char* message = "";

	strcpy(message, winner);
	strcpy(message, " WINS!");
*/

	mvwprintw(outro, (int)(parent_y / 2), (int)(parent_x / 2) - (int)(strlen("GAME OVER") / 2), "GAME OVER");
	wrefresh(outro);
	sleep(2);
	wclear(outro);
	delwin(outro);
	wclear(stdscr);



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

