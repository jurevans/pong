/* paddle.h */
/* Paddle library */

#ifndef __PADDLE_H_
	/* CONSTANTS */

	#ifndef PADDLE_CHAR
	#define PADDLE_CHAR "|"
	#endif

	#include <ncurses.h>

	/* STRUCTURES */

	struct Paddle {
		int x_pos;
		int y_pos;
		int height;
		int width;
		char paddle_char[2];
	};

	/* PROTOTYPES */

	extern struct Paddle* paddle_create( int x_pos, int y_pos, 
					     int height, int width, 
					     char* paddle_char );

	extern void paddle_draw(WINDOW* screen, struct Paddle* paddle);

	extern void paddle_destroy( struct Paddle* _paddle );

#endif
