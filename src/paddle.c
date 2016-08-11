/**
 * paddle.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "include/pong.h"

struct Paddle* paddle_create( int x_pos, int y_pos, int height, int width )
{
	struct Paddle* _paddle = malloc(sizeof(struct Paddle));

	assert(_paddle != NULL);

	_paddle->x_pos = x_pos;
	_paddle->y_pos = y_pos;
	_paddle->height = height;
	_paddle->width = width;

	return _paddle;
}

/* paddle_draw
 * WINDOW* field
 * struct Paddle*
 * int x_pos (1 or not 1 - determines LEFT or RIGHT)
 */

void paddle_draw( WINDOW* field, struct Paddle* _paddle, int x_pos )
{
	int i, j;
	int field_max_y, field_max_x;

	getmaxyx( field, field_max_y, field_max_x );

	_paddle->height = (int)(field_max_y / PADDLE_HEIGHT);

	/* X position */
	if(x_pos == 1) {
		_paddle->x_pos = BORDER_Y_SIZE;
	} else {
		_paddle->x_pos = field_max_x - _paddle->width - (BORDER_Y_SIZE * 3);
	}

	/* Draw Paddle */
	for(i = 0; i < _paddle->height; i++)
	{
		for(j = 0; j < _paddle->width; j++)
		{
			mvwprintw( field, 
				   _paddle->y_pos + BORDER_Y_SIZE + i,
				   _paddle->x_pos + BORDER_X_SIZE + j, 
				   PADDLE_CHAR );
		}
	}
}

void paddle_destroy( struct Paddle* _paddle )
{
	assert(_paddle != NULL);
	free(_paddle);
}

