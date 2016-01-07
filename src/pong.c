/* 
 * Pong
 * pong.c
 * Author: Justin R. Evans
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <assert.h>

#include "include/pong.h"

int main(int argc, char* argv[]) 
{
	int 	max_x, max_y, 
		new_x, new_y, 
		key, 
		field_max_x, field_max_y;

	struct Ball* _ball = ball_create( 0, 0, 50, 50, 0, 0, 1, 1 );
	struct User* _user_1 = user_create( 0, "Player 1", 1 );
	struct User* _user_2 = user_create( 0, "Player 2", 0 );
	struct Paddle* _paddle_1 = paddle_create( 0, 0, 0, 2 );
	struct Paddle* _paddle_2 = paddle_create( 0, 0, 0, 2 );

	char score_1[3];
	char score_2[3];

#if DEBUG_POSITION
	char status[10];
#endif

	/* Get Player 1 Name */
	system("clear");
	printf("\nEnter name for Player 1: ");
	scanf("%s", _user_1->username);
	system("clear");

	/* Get Player 2 Name */
	printf("\nEnter name for Player 2: ");
	scanf("%s", _user_2->username);
	system("clear");

	/* Initialize NCurses Screen, Set Options  */
	initscr();
	cbreak();
	noecho();
    	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	keypad(stdscr, TRUE); 

	/* Get Max Screen dimensions */
	getmaxyx(stdscr, max_y, max_x);

	/* Set up Windows */
	WINDOW* intro = newwin(0, 0, 0, 0);
	WINDOW* outro = newwin(0, 0, 0, 0);
	WINDOW* field = newwin(max_y - SCORE_SIZE, max_x, SCORE_SIZE, 0);
	WINDOW* score = newwin(SCORE_SIZE, max_x, 0, 0);

	/* Init Paddles */
	getmaxyx( field, field_max_y, field_max_x );

	/* Paddle 1 - Initial Y value */
	_paddle_1->y_pos = (int)((int)(field_max_y / 2) - 
		(int)((int)(field_max_y / PADDLE_HEIGHT) / 2));

	/* Paddle 2 - Initial Y value */
	_paddle_2->y_pos = _paddle_1->y_pos;

	/* Show Intro Screen */
	screen_draw(intro, "PONG");

	/* Main game loop */
	while( _user_1->score < MAX_SCORE && _user_2->score < MAX_SCORE ) 
	{
		/* Draw divider line: */

		divider_draw( field );

		/* Init Ball dimensions within Field */
		getmaxyx( field, _ball->max_y, _ball->max_x );

		/* Get Key Press from Player */
		/* TODO, among many other to-dos...: Make constants for Player 2 keys if on same keyboard... */
		if( key_pressed() ) {
			key = getch();

			/* Make the following "ifs" more DRY!!! */

			if( key == KEY_UP && _paddle_1->y_pos >= BORDER_X_SIZE ) {
				_paddle_1->y_pos -= 2;

			}

			if( key == KEY_DOWN && (_paddle_1->y_pos + _paddle_1->height + (BORDER_X_SIZE * 2)) < field_max_y ) {
				_paddle_1->y_pos += 2;
			}

			if( key == 'a'  && _paddle_2->y_pos >= BORDER_X_SIZE ) {
				_paddle_2->y_pos -= 2;
			}
	
			if( key == 'z'  
				&& (_paddle_2->y_pos + _paddle_2->height + (BORDER_X_SIZE * 2)) < field_max_y ) {

				_paddle_2->y_pos += 2;
			}

			wclear(field);
			divider_draw( field );
		}

		/* Render paddles */
		paddle_draw(field, _paddle_1, 1);
		paddle_draw(field, _paddle_2, 2);

		_ball->max_y -= (BORDER_Y_SIZE * 2);
		_ball->max_x -= (BORDER_X_SIZE * 2);

		/* Detect Screen Resize */

		getmaxyx(stdscr, new_y, new_x);

		if(new_y != max_y || new_x != max_x) {
			max_x = new_x;
			max_y = new_y;

			wresize(field, new_y - SCORE_SIZE, new_x);
			wresize(score, new_y - SCORE_SIZE, 0);
			refresh();

			wclear(stdscr);
			wclear(field);
			wclear(score);

			borders_draw(field);
			borders_draw(score);
		}


#if DEBUG_POSITION	
		snprintf(status, sizeof(status), "%d,%d", _ball->x, _ball->y);
		mvwprintw(stdscr, SCORE_SIZE + 1, BORDER_X_SIZE + 1, status );
#endif

		/* Wait for just a [usleep amount of DELAY] */
		usleep(DELAY);

		/* Print Pong at next location */
		ball_next(_ball);
		mvprintw( _ball->y + BORDER_Y_SIZE + SCORE_SIZE, _ball->x + BORDER_X_SIZE, BALL_STRING );
		
		/* Detect Ball collision with Paddle 1 or 2 :: Determine turn for User 1 or 2 */
		
		/* Check Paddle-LEFT */

		int i; // Determine x,y coordinate, Y is VARIABLE

		for(i = _paddle_1->y_pos; i < _paddle_1->y_pos + _paddle_1->height; ++i)
		{
			if( (_ball->y == i) && (_ball->x == _paddle_1->x_pos + 2) )
			{
				_ball->dir_x *= -1; // switch directions!
				
				break;
			}
		}

		/* Check Paddle-RIGHT */

		i = 0;

		for(i = _paddle_2->y_pos; i < _paddle_2->y_pos + _paddle_2->height; ++i)
		{
			if( (_ball->y == i) && (_ball->x == _paddle_2->x_pos) )
			{
				_ball->dir_x *= -1; // switch directions!
				
				break;
			}
		}

		/* Did Player 1 score? */
		if(_ball->next_x == _ball->max_x - BORDER_Y_SIZE)
		{
			_user_1->score++;

			_ball->y = 0;
			_ball->x = 0;

			_user_1->turn = 1;
			_user_2->turn = 0;
		}

		/* Did Player 2 score? */
		if(_ball->next_x < 0)
		{
			_user_2->score++;

			_ball->y = 0;
			_ball->x = _ball->max_x - BORDER_X_SIZE;

			_user_1->turn = 0;
			_user_2->turn = 1;
		}

		/* Get and print current scores: */
		snprintf(score_1, 3, "%d", _user_1->score);
		snprintf(score_2, 3, "%d", _user_2->score);

		mvwprintw(score, 1, (int)(max_x / 2) - 5, score_1);
		mvwprintw(score, 1, (int)(max_x / 2) + 5, score_2);
		mvwprintw(score, 1, (int)(max_x / 2), "|");

		mvwprintw(score, 1, (BORDER_Y_SIZE * 2), _user_1->username);
		mvwprintw(score, 1, max_x - strlen(_user_2->username) - (BORDER_Y_SIZE * 2), _user_2->username);

		/* Draw borders */
		borders_draw(field);
		borders_draw(score);

		/* Refresh Screens after updates */
		wrefresh(field);
		wrefresh(score);

		refresh();
	}

	/* Clean up field and score windows */
	delwin(field);
	delwin(score);

	/* Clear Game Screens */
	wclear(stdscr);
	refresh();

	/* Show Outro Screen */
	screen_draw(outro, "GAME OVER");

	/* CLEANUP */
	endwin();

	/* TODO: Possible DEALLOC Stack for these? */

	ball_destroy(_ball);
	user_destroy(_user_1);
	user_destroy(_user_2);

	return 0;
}

