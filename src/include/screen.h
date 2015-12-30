/* screen.h */
/* Library header for "screen.c" */

#ifndef __SCREEN_H_
#define __SCREEN_H_

	/* INCLUDES */

	#include <ncurses.h>

	/* CONSTANTS */
	#ifndef X_Y_OFFSET
	#define X_Y_OFFSET 4 /* MAX_X - X_Y_OFFSET, MAX_Y - X_Y_OFFSET */
	#endif

	#ifndef CHAR_PRINT_DELAY
	#define CHAR_PRINT_DELAY 5000 /* usleep(CHAR_PRINT_DELAY) */
	#endif

	#ifndef PAUSE_SCREEN
	#define PAUSE_SCREEN 2 /* IN SECONDS FOR sleep() */
	#endif

	#ifndef PRE_BORDER_DELAY
	#define PRE_BORDER_DELAY 300000 /* usleep(PRE_BORDER__DELAY) */
	#endif
	

	/* PROTOTYPES  */

	extern void screen_draw(WINDOW *screen, char* message);

#endif
