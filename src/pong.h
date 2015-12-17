// pong.h

// CONSTANTS
#ifndef DELAY
#define DELAY 30000
#endif

#ifndef DEBUG_POSITION
#define DEBUG_POSITION	1
#endif

#define PONG_ELEMENT_SIZE 1
#define BORDER_X_SIZE 1
#define BORDER_Y_SIZE 1

/* STRUCTURES */

struct Pong {
	int x;
	int y;
	int max_x;
	int max_y;
	int next_x;
	int next_y;
	int x_direction;
	int y_direction;
	char element[PONG_ELEMENT_SIZE];
};

/* PROTOTYPES */

struct Pong* pong_create( int x, int y, 
			  int max_x, int max_y,
			  int next_x, int next_y, 
			  int x_direction, int y_direction, char element[PONG_ELEMENT_SIZE] );

void pong_next( struct Pong* _pong );
void pong_status( struct Pong* _pong );
void pong_destroy( struct Pong* _pong );

void init_screen( struct Pong* _pong);
void end_screen(void);

