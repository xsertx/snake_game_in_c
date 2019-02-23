// DONE
// snake is alive!
// snake can move (w/a/s/d)
// apple is growing
// snake can eat apple

// TODO LIST
// - snake don't know what is collisions need to teach her manners!
// - do we need walls?
// - fps .. sucks
// - clean code
// - sometimes apple randomly trying to grow on snake's body.. as a result fruit disappear on the map.
// - add some color


#include<stdio.h>
#include<stdlib.h>
#include "snake_lib.h"
#include <Windows.h>

#define UP 119
#define DOWN 115
#define LEFT 97
#define RIGHT 100

#define F_SIZE 20

#define CLEAR 0
#define DRAW 1

#define SNAKE_SYM 143
#define EMPTY_SYM 178
#define FOOD_SYM 157


#define RAND_MAX F_SIZE

void setDirection(char key, snake* player, char field[F_SIZE][F_SIZE], food* fr);

void drawingField(char field[F_SIZE][F_SIZE]);
void updateSnakeInField(snake* player, char field[F_SIZE][F_SIZE]);

void placeFood(food* s_food, char field[F_SIZE][F_SIZE]);

int main()
{
	srand(time(NULL));

	char key_pressed = DOWN;
	int direction;

	// snake initialization
	snake player;
	player.length = 1;
	int X = 4, Y = 4;
	player.body_position[0].x = X;
	player.body_position[0].y = Y;
	player.isGrow = 0;

	char field[F_SIZE][F_SIZE];
	// clearing our field
	drawingField(field, CLEAR, &player);

	// placing our snake in initial coordinates
	field[X][Y] = SNAKE_SYM;

	food apple;
	apple.inField = 0;

	// Starting game - loop util snake will not eat itself
	while (1)
	{

		// Getting input from keyboard
		if (_kbhit())
			key_pressed = _getch();

		// setting new coordinates for our snake
		setDirection(key_pressed, &player, field, &apple);

		// placing a food..
		placeFood(&apple, field);

		// drawing field with snake
		drawingField(field, DRAW, &player);
		delay(300);		// frame rate would be faster but as I always want to win it would be 1 sec
		system("cls");	// clear screen - but this is very heavy operation so I will replace it later
	}

	system("pause");

	return 0;
}

void setDirection(char key, snake * player, char field[F_SIZE][F_SIZE], food * fruit)
{
	int i = 0, j = 0;
	int len = player->length;
	switch (key)
	{
	case DOWN:
		// checking for what our snake is eating..
		if (player->body_position[0].x == fruit->position.x && player->body_position[0].y + 1 == fruit->position.y)
		{
			player->isGrow = 1;
			player->length++;

			fruit->inField = 0;
		}
		else
		{
			player->isGrow = 0;
		}

		if (player->length > 1)
		{
			i = len;
			field[player->body_position[i - 1].y][player->body_position[i - 1].x] = EMPTY_SYM;
			for (; i > 0; i--)
			{
				player->body_position[i] = player->body_position[i - 1];
			}
		}
		else
			field[player->body_position[0].y][player->body_position[0].x] = EMPTY_SYM;

		player->body_position[i].y = player->body_position[i].y + 1;

		field[player->body_position[i].y][player->body_position[i].x] = SNAKE_SYM;

		break;
	case UP:
			// checking for what our snake is eating..
			if (player->body_position[0].x == fruit->position.x && player->body_position[0].y - 1 == fruit->position.y)
			{
				player->isGrow = 1;
				player->length++;

				fruit->inField = 0;
			}
			else
			{
				player->isGrow = 0;
			}

			if (player->length > 1)
			{
				i = len;
				field[player->body_position[i - 1].y][player->body_position[i - 1].x] = EMPTY_SYM;
				for (; i > 0; i--)
				{
					player->body_position[i] = player->body_position[i - 1];
				}
			}
			else
				field[player->body_position[0].y][player->body_position[0].x] = EMPTY_SYM;

			player->body_position[i].y = player->body_position[i].y - 1;

			field[player->body_position[i].y][player->body_position[i].x] = SNAKE_SYM;
		break;
	case LEFT:

			// checking for what our snake is eating..
			if (player->body_position[0].x - 1 == fruit->position.x && player->body_position[0].y == fruit->position.y)
			{
				player->isGrow = 1;
				player->length++;

				fruit->inField = 0;
			}
			else
			{
				player->isGrow = 0;
			}

			if (player->length > 1)
			{
				i = len;
				field[player->body_position[i - 1].y][player->body_position[i - 1].x] = EMPTY_SYM;
				for (; i > 0; i--)
				{
					player->body_position[i] = player->body_position[i - 1];
				}
			}
			else
				field[player->body_position[0].y][player->body_position[0].x] = EMPTY_SYM;

			player->body_position[i].x = player->body_position[i].x - 1;

			field[player->body_position[i].y][player->body_position[i].x] = SNAKE_SYM;
		
		break;
	case RIGHT:
		// checking for what our snake is eating..
		if (player->body_position[0].x + 1 == fruit->position.x && player->body_position[0].y == fruit->position.y)
		{
			player->isGrow = 1;
			player->length++;

			fruit->inField = 0;
		}
		else
		{
			player->isGrow = 0;
		}

		if (player->length > 1)
		{
			i = len;
			field[player->body_position[i - 1].y][player->body_position[i - 1].x] = EMPTY_SYM;
			for (; i > 0; i--)
			{
				player->body_position[i] = player->body_position[i - 1];
			}
		}
		else
			field[player->body_position[0].y][player->body_position[0].x] = EMPTY_SYM;

		player->body_position[i].x = player->body_position[i].x + 1;

		field[player->body_position[i].y][player->body_position[i].x] = SNAKE_SYM;
		break;

	}
}

//useless ? 
void updateSnakeInField(snake * player, char field[F_SIZE][F_SIZE])
{
	for (int i = 0; i < player->length; i++)
	{
		field[player->body_position[i].x][player->body_position[i].y] = SNAKE_SYM;
	}
}

void drawingField(char field[F_SIZE][F_SIZE], int state, snake * pl)
{
	if (state == CLEAR)
		for (int i = 0; i < F_SIZE; i++)
			for (int j = 0; j < F_SIZE; j++)
				field[i][j] = EMPTY_SYM;

	if (state == DRAW)
	{
		printf("SCORE : %d\n", pl->length);

		for (int i = 0; i < F_SIZE; i++)
		{
			for (int j = 0; j < F_SIZE; j++)
				printf("%c", field[i][j]);
			printf("\n");
		}
	}
}

void placeFood(food * fruit, char field[F_SIZE][F_SIZE])
{
	if (!fruit->inField)
	{
		fruit->inField = 1;
		fruit->position.x = rand() % F_SIZE;
		fruit->position.y = rand() % F_SIZE;
		field[fruit->position.y][fruit->position.x] = FOOD_SYM;
	}
}