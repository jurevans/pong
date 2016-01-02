/* ball.h
 * Library header for ball in Pong game, ball.c
 */

#ifndef __BALL_H__
#define __BALL_H__

#include <string.h>

/* CONSTANTS */

#ifndef DELAY
#define DELAY 30000
#endif

#ifndef DEBUG_POSITION
#define DEBUG_POSITION	0
#endif

#ifndef BALL_STRING
#define BALL_STRING "*"
#endif

/* STRUCTURES */

struct Ball {
	int x;
	int y;
	int max_x;
	int max_y;
	int next_x;
	int next_y;
	int x_direction;
	int y_direction;
	char element[strlen(BALL_STRING)];
};

/* PROTOTYPES */

extern struct Ball* ball_create( int x, int y, 
			  int max_x, int max_y,
			  int next_x, int next_y, 
			  int x_direction, int y_direction, char element[strlen(BALL_STRING)] );

extern void ball_next( struct Ball* _ball );

extern void ball_destroy( struct Ball* _ball );

#endif
