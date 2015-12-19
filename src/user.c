/*
 * User
 * user.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include "include/user.h"

struct User* user_create( int score, char username[15] )
{
	struct User* _user = malloc(sizeof(struct User));

	assert(_user != NULL);

	_user->score = score;

	strcpy(_user->username, username);

	return _user;
}

void user_destroy( struct User* _user )
{
	assert(_user != NULL);
	free(_user);
}


