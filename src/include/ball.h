/* balllib.h
 * Library header for ball in Pong game, balllib.c
 */

#ifndef __BALL_H__
#define __BALL_H__

	/* CONSTANTS */

	#ifndef DELAY
	#define DELAY 30000
	#endif

	#ifndef DEBUG_POSITION
	#define DEBUG_POSITION	0
	#endif

	#define BALL_ELEMENT_SIZE 1

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
		char element[BALL_ELEMENT_SIZE];
	};

	/* PROTOTYPES */

	extern struct Ball* ball_create( int x, int y, 
				  int max_x, int max_y,
				  int next_x, int next_y, 
				  int x_direction, int y_direction, char element[BALL_ELEMENT_SIZE] );

	extern void ball_next( struct Ball* _ball );
	extern void ball_status( struct Ball* _ball );
	extern void ball_destroy( struct Ball* _ball );
#endif
