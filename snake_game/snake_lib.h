#include<time.h>

void delay(int number_of_miliseconds)
{
	// Converting time into milli_seconds 
	int milli_seconds = number_of_miliseconds;

	// Stroing start time 
	clock_t start_time = clock();

	// looping till required time is not acheived 
	while (clock() < start_time + milli_seconds);
}

typedef struct
{
	int x;
	int y;
} coord;

typedef struct
{
	int isGrow;
	int length;					// body length
	coord body_position[300];	// storing position of each snake's cell in this array
} snake;

typedef struct 
{
	coord position;
	int inField;
} food;