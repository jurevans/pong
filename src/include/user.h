/* user.h */
/* User/Player library */

#ifndef __USER_H_
	/* CONSTANTS */

	/* STRUCTURES */

	struct User {
		int score;
		char username[15];
	};

	/* PROTOTYPES */

	extern struct User* user_create( int score, char username[15] );
	extern void user_destroy( struct User* _user );

#endif
