/**
 * user.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include "include/pong.h"

struct User* user_create( char* username, int turn)
{
	struct User* _user = malloc(sizeof(struct User));

	assert(_user != NULL);

	_user->turn = turn;
	_user->score = 0; 

	system("clear");
	printf("\nEnter name for %s: ", username);
	fgets(_user->username, sizeof(_user->username), stdin);
	system("clear");

	if(_user->username[0] == '\0' || _user->username[0] == '\n') {
		strcpy(_user->username, username);
	}

	return _user;
}

void user_destroy( struct User* _user )
{
	assert(_user != NULL);
	free(_user);
}

