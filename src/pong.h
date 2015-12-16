// pong.h

// CONSTANTS
#ifndef DELAY
#define DELAY 30000
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

struct Borders {
	int pad_t;			// Offset TOP
	int pad_r;			// Offset RIGHT
	int pad_b;			// Offset BOTTOM
	int pad_l;			// Offset LEFT
	char element_x[BORDER_X_SIZE];	// String for X (top/bottom)
	char element_y[BORDER_Y_SIZE];	// String for Y (left/right)
};

/* PROTOTYPES */

struct Pong* pong_create( int x, int y, 
			  int max_x, int max_y,
			  int next_x, int next_y, 
			  int x_direction, int y_direction, char element[PONG_ELEMENT_SIZE] );

struct Borders* borders_create( int pad_t, int pad_r, int pad_b, int pad_l,
				char element_x[BORDER_X_SIZE], char element_y[BORDER_Y_SIZE] );

void pong_next( struct Pong* _pong );
void pong_status( struct Pong* _pong );
void pong_destroy( struct Pong* _pong );

void init_screen( struct Pong* _pong);
void end_screen();

