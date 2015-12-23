/* user.h */
/* User/Player library */

#ifndef __USER_H_
	/* CONSTANTS */

	#ifndef MAX_SCORE
	#define MAX_SCORE 3
	#endif

	/* STRUCTURES */

	struct User {
		int score;
		char username[30];
		int turn;
	};

	/* PROTOTYPES */

	extern struct User* user_create( int score, char username[30], int turn );
	extern void user_destroy( struct User* _user );

#endif
