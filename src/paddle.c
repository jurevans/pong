/*
 * Paddle
 * paddle.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include "include/field.h"
#include "include/paddle.h"

struct Paddle* paddle_create( int x_pos, int y_pos, int height, int width, char paddle_char[2] )
{
	struct Paddle* _paddle = malloc(sizeof(struct Paddle));

	assert(_paddle != NULL);

	_paddle->x_pos = x_pos;
	_paddle->y_pos = y_pos;
	_paddle->height = height;
	_paddle->width = width;
	strcpy(_paddle->paddle_char, paddle_char);

	return _paddle;
}

void paddle_draw( WINDOW* screen, struct Paddle* _paddle )
{
	int i, j;


	for(i = 0; i < _paddle->height; i++)
	{
		for(j = 0; j < _paddle->width; j++)
		{
			mvwprintw( screen, 
				   _paddle->y_pos + BORDER_Y_SIZE + i,
				   _paddle->x_pos + BORDER_X_SIZE + j, 
				   _paddle->paddle_char );
		}
	}

}

void paddle_destroy( struct Paddle* _paddle )
{
	assert(_paddle != NULL);
	free(_paddle);
}


