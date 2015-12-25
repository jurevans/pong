/* paddle.h */
/* Paddle library */

#ifndef __PADDLE_H_
	/* CONSTANTS */

	#ifndef PADDLE_CHAR
	#define PADDLE_CHAR "|"
	#endif

/*
	Down Arrow  0x1B 0x5B 0x42 // getch(); // DOWN
//	Left Arrow  0x1B 0x5B 0x44
//	Right Arrow 0x1B 0x5B 0x43
	Up Arrow    0x1B 0x5B 0x41 // getch(); // UP
*/

	// Paddle Height is determined by MAX_Y / PADDLE_HEIGHT
	#ifndef PADDLE_HEIGHT
	#define PADDLE_HEIGHT 4
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
