// Main functional is working ...

// TODO LIST
// - do we need walls?
// - clean code
// - add some color

#include<stdio.h>
#include<stdlib.h>
#include "snake_lib.h"
#include <Windows.h>

void setDirection(char key, snake* player, char field[F_SIZE][F_SIZE], food* fr, int* gameOver);
void drawingField(char field[F_SIZE][F_SIZE], int state, snake* pl);
void updateSnakeInField(snake* player, char field[F_SIZE][F_SIZE]);
void placeFood(food* s_food, char field[F_SIZE][F_SIZE], snake* pl);
void setAndWrite(int x,int y, char symb);

// Getting output console
HANDLE hwd;

// Creating cursor position
COORD pos = { 0,0 };

int main()
{
	// Passing a console to hwd
	hwd = GetStdHandle(STD_OUTPUT_HANDLE);

	srand(time(NULL));

	int gameOver = 0;

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

	for (int i = 0; i < F_SIZE; i++)
	{
		for (int j = 0; j < F_SIZE; j++)
			printf("%c", field[i][j]);
		printf("\n");
	}

	// Starting game - loop util snake will not eat itself
	while (!gameOver)
	{

		// Getting input from keyboard
		if (_kbhit())
			key_pressed = _getch();

		// setting new coordinates for our snake
		setDirection(key_pressed, &player, field, &apple, &gameOver);

		// placing a food..
		placeFood(&apple, field, &player);

		// drawing field with snake
		// drawingField(field, DRAW, &player);
		delay(120);		// frame rate would be faster but as I always want to win it would be 1 sec
		// system("cls");	// clear screen - but this is very heavy operation so I will replace it later
	}

	system("cls");
	printf("OMG NOOB..\n");
	printf("GAME OVER\nYOUR SCORE: %d\n", player.length);

	system("pause");

	return 0;
}

void setDirection(char key, snake * player, char field[F_SIZE][F_SIZE], food * fruit, int* gameOver)
{
	int i = 0, j = 0;
	int len = player->length;

	// There is only 2 types of movement vertical and horizontal - vert and horiz var-s correspondingly
	int vert = 0, horiz = 0;

	// we just defining a direction using only 2 var. 
	switch (key)
	{
	case DOWN:
		vert = 1;	horiz = 0;
		break;
	case UP:
		vert = -1;	horiz = 0;
		break;
	case LEFT:
		vert = 0;	horiz = -1;
		break;
	case RIGHT:
		vert = 0; 	horiz = 1;
		break;
	}

	// checking if snake ate the fruit
	if (player->body_position[0].x + horiz == fruit->position.x && player->body_position[0].y + vert == fruit->position.y)
	{
		// if yes then updating player's params
		player->isGrow = 1;
		player->length++;

		fruit->inField = 0;
	}
	else
		player->isGrow = 0;

	// moving our snake .. cell by cell
	// probably it's better to move only last cell to step up after head
	if (player->length > 1)
	{
		i = len;
		// deleting last element in the field
		field[player->body_position[i - 1].y][player->body_position[i - 1].x] = EMPTY_SYM;

		setAndWrite(player->body_position[i-1].x, player->body_position[i - 1].y, EMPTY_SYM);

		// now moving snake's cell forward
		for (; i > 0; i--)
			player->body_position[i] = player->body_position[i - 1];
	}
	else
	{
		field[player->body_position[0].y][player->body_position[0].x] = EMPTY_SYM;

		setAndWrite(player->body_position[0].x, player->body_position[0].y, EMPTY_SYM);
	}

	player->body_position[i].x = player->body_position[i].x + horiz;
	player->body_position[i].y = player->body_position[i].y + vert;

	setAndWrite(player->body_position[i].x, player->body_position[i].y,SNAKE_SYM);

	field[player->body_position[i].y][player->body_position[i].x] = SNAKE_SYM;


	if (player->length > 1)
		for (j = 1; j < player->length; j++)
			if (player->body_position[0].x == player->body_position[j].x && player->body_position[0].y == player->body_position[j].y)
				* gameOver = 1;

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


void placeFood(food * fruit, char field[F_SIZE][F_SIZE], snake * pl)
{
	if (!fruit->inField)
	{

		fruit->inField = 1;

		int foodNotInSnake = 0, c = 0;
		while (!foodNotInSnake)
		{
			fruit->position.x = rand() % F_SIZE;
			fruit->position.y = rand() % F_SIZE;

			for (int i = 0; i < pl->length; i++)
			{
				if (pl->body_position[i].x == fruit->position.x && pl->body_position[i].y == fruit->position.y)
				{
					foodNotInSnake = 0;
					break;
				}
				else
					c++;
			}
			if (c == pl->length)
				foodNotInSnake = 1;
		}

		setAndWrite(fruit->position.x, fruit->position.y, FOOD_SYM);

		field[fruit->position.y][fruit->position.x] = FOOD_SYM;
	}
}

void setAndWrite(int x, int y, char symb)
{
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hwd, pos);

	printf("%c", symb);
}