/** 
 * pong.h
 * Library header for Pong game components
 */

#ifndef _PONG_H_
#define _PONG_H_

#define VERSION "0.6.2"

/**
 * Include required libraries for defining prototypes
 * Standard Library <string.h> is needed
 * libncurses5-dev is required
 */

#include <string.h>
#include <ncurses.h>

/**
 * Definitions and Macros 
 */

/**
 * DELAY :: Determines speed of Game loop, e.g, usleep(DELAY)
 */
#ifndef DELAY
#undef DELAY
#define DELAY 30000
#endif

/**
 * DEBUG_POSITION :: Setting to 1 will enable display of ball x/y coordinates in field window
 */
#define DEBUG_POSITION	0

/**
 * BALL_STRING :: Set the character or string used as the pong ball
 */
#define BALL_STRING "*"

/**
 * PADDLE_CHAR :: Set the character used to draw Paddles
 */
#define PADDLE_CHAR "|"

/** 
 * PADDLE_HEIGHT :: Paddle Height is determined by MAX_Y / PADDLE_HEIGHT 
 */
#define PADDLE_HEIGHT 4

/**
 * X_Y_OFFSET :: MAX_X - X_Y_OFFSET, MAX_Y - X_Y_OFFSET  (Macro-worthy? I'll have to check)
 */
#define X_Y_OFFSET 4 

/**
 * CHAR_PRINT_DELAY :: Wait usleep(CHAR_PRINT_DELAY) between printing screen letters 
 */
#define CHAR_PRINT_DELAY 5000 

/**
 * PAUSE_SCREN :: IN SECONDS FOR sleep() 
 */
#define PAUSE_SCREEN 2 

/**
 * PRE_BORDER_DELAY :: Set delay borfer animation to usleep(PRE_BORDER_DELAY)
 */
#define PRE_BORDER_DELAY 300000

#define MAX_SCORE 10

#define BORDER_X_SIZE 1
#define BORDER_Y_SIZE 1

#define SCORE_SIZE 	3
#define CORNERS		"+"
#define BORDERS_X 	"-"
#define BORDERS_Y 	"|"

/**
 *  STRUCTURES 
 */

/**
 * Ball Structure
 * int x, y, max_x, max_y, next_x, next_y, dir
 */
struct Ball {
	int x;
	int y;
	int max_x;
	int max_y;
	int next_x;
	int next_y;
	int dir_x;
	int dir_y;
};

/**
 * Paddle Structure
 */
struct Paddle {
	int x_pos;
	int y_pos;
	int height;
	int width;
};

struct User {
	int score;
	char username[30];
	int turn;
};

/**
 * PROTOTYPES 
 */

extern void borders_draw(WINDOW* screen);

extern void divider_draw(WINDOW* field); 

extern int key_pressed(void);

extern struct Ball* ball_create( int x, int y, 
			  	 int max_x, int max_y,
			  	 int next_x, int next_y, 
			  	 int dir_x, int dir_y );

extern void ball_next( struct Ball* _ball );

extern void ball_destroy( struct Ball* _ball );

extern struct Paddle* paddle_create( int x_pos, int y_pos, 
				     int height, int width );

extern void paddle_draw( WINDOW* field, struct Paddle* paddle, int x_pos );

extern void paddle_destroy( struct Paddle* _paddle );

extern void screen_draw(WINDOW *screen, char* message);

extern struct User* user_create( int score, char username[30], int turn );

extern void user_destroy( struct User* _user );

#endif /** END if __PONG_H__ */
