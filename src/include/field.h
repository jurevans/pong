/* field.h */
/* Library header for "field.c" */

#ifndef __FIELD_H_
#define __FIELD_H_

	/* INCLUDES */

	#include <ncurses.h>

	/* CONSTANTS */

	#define BORDER_X_SIZE 1
	#define BORDER_Y_SIZE 1

	#define SCORE_SIZE 	3
	#define CORNERS		"+"
	#define BORDERS_X 	"-"
	#define BORDERS_Y 	"|"

	/* PROTOTYPES  */

	extern void draw_borders(WINDOW *screen);

	extern int key_pressed(void);

#endif

