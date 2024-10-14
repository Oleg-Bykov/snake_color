#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <dos.h>
#include <windows.h>

#define MAX_X 15
#define MAX_Y 15
#define MAX_SNAKE_LENGTH 6

typedef enum 
{
	UP,
	DOWN,
	LEFT,
	RIGHT
} Direction;

typedef struct tail_t
{
	int x;
	int y;
} tail_t;
	
typedef struct snake_t
{
	int x;
	int y;
	struct tail_t * tail;
	size_t tsize;
	Direction direction;
}  snake_t;
	
typedef struct food_t
{
	int x;
	int y;
	int isEaten;
} food_t;

// --> x
// || Y
// \/
// @**
struct snake_t initSnake(int x, int y, size_t tsize)
{
	struct snake_t snake;
	snake.x = x;
	snake.y = y;
	snake.tsize = tsize;
	snake.tail = (tail_t *) malloc (sizeof(tail_t) * 100);
	for (int i =0; i < tsize; ++i){
		snake.tail[i].x = x + i +1;
		snake.tail[i].y = y;
		}
		snake.direction = LEFT;
	
	return snake;
}

food_t initFood()
{
	food_t food;
	food.x = rand() % MAX_X;
	food.y = rand() % MAX_Y;
	food.isEaten = 0;
	return food;
}
	
void printSnake(struct snake_t snake, struct snake_t snake2, food_t food)
{
		char matrix[MAX_X][MAX_Y];
		for (int i = 0; i < MAX_X; ++i)
		{
			for (int j = 0; j < MAX_Y; ++j)
			{
				matrix[i][j] = ' ';
			}
		}
		matrix[food.x][food.y] = '$';
		
		matrix[snake.x][snake.y] = '@';
		
		matrix[snake2.x][snake2.y] = '%';
		for (int i = 0; i < snake.tsize; ++i)
		{
			matrix[snake.tail[i].x][snake.tail[i].y] = '*';
		}
		for (int i = 0; i < snake2.tsize; ++i)
		{
			matrix[snake2.tail[i].x][snake2.tail[i].y] = '-';
		}
		for (int j = 0; j < MAX_Y; ++j)
		{
			for (int i = 0; i < MAX_X; ++i)
			{
				printf("%c", matrix[i][j]);
			}
				printf("\n");
		}
}

snake_t move(snake_t snake, food_t *food)
{
	for (int i = snake.tsize; i > 0; i--)
	{
		snake.tail[i] = snake.tail[i-1];
	}
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;
	
	switch(snake.direction)
	{
		case UP:
		{
			snake.y = snake.y - 1;
			if (snake.y < 0)
			{
				snake.y = MAX_Y -1;
			}
			break;
		}
		case DOWN:
		{
			snake.y = snake.y + 1;
			if (snake.y == MAX_Y)
			{
				snake.y = 0;
			}
			break;
		}
		case LEFT:
		{
			snake.x = snake.x - 1;
			if (snake.x < 0)
			{
				snake.x = MAX_X -1;
			}
			break;
		}
		case RIGHT:
		{
			snake.x = snake.x + 1;
			if (snake.x == MAX_X)
			{
				snake.x = 0;
			}
			break;
		}
	}
	if (snake.x == food->x && snake.y == food->y)
	{
		food->isEaten++;
		snake.tsize++;
	}
	
		
	return snake;
}
void printLevel(snake_t snake)
{
	int i=snake.tsize;
	printf("level is %d\n",i-1);
}

void input(snake_t *snake)
{
	if (kbhit()){
		switch (getch()) {
			case 'w':
				snake->direction = UP;
				break;
			case 's':
				snake->direction = DOWN;
				break;
			case 'a':
				snake->direction = LEFT;
				break;
			case 'd':
				snake->direction = RIGHT;
				break;
		}
	}

}

void speed(snake_t snake)
{
	float i=MAX_SNAKE_LENGTH-snake.tsize;
	
	sleep(i);
} 

void generateSnakeDirection(snake_t *snake,food_t food)
{
	if ((snake->direction == LEFT || snake-> direction == RIGHT) && snake->y == food.y ){
		return;
	}
	if ((snake->direction == LEFT || snake-> direction == RIGHT) && snake->y != food.y ){
		if (food.x == snake->x){
			if (abs(food.y == snake->y)<=MAX_Y/2)
			{
				snake->direction = food.y - snake->y > 0? DOWN : UP;
			}
			else
			{
				snake->direction = food.y - snake->y > 0? UP : DOWN;
			}
		}
		return;
	}
	if ((snake->direction == UP || snake-> direction == DOWN) && snake->x == food.x ){
		return;
	}
	if ((snake->direction == UP || snake-> direction == DOWN) && snake->x != food.x ){
		if (food.y == snake->y){
			if (abs(food.x == snake->x)<=MAX_X/2)
			{
				snake->direction = food.x - snake->x > 0? RIGHT : LEFT;
			}
			else
			{
				snake->direction = food.y - snake->y > 0? LEFT : RIGHT;
			}
		}
		return;
	}
	
}
		
int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	struct snake_t snake = initSnake( 10, 5, 2);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	
	struct snake_t snake2 = initSnake( 2, 2, 2);
	food_t food = initFood();

	printSnake(snake, snake2, food);

	while(snake.tsize<MAX_SNAKE_LENGTH)
	{
		input(&snake);
		generateSnakeDirection(&snake2, food);
		snake = move(snake, &food);
		snake2 = move(snake2, &food);
		if (food.isEaten)
		{
			food = initFood();
		}
		
		//speed(snake2);
		sleep(1);
		system("cls");
		printSnake(snake, snake2, food);
		

	}
	printLevel(snake2);
	getchar();
	return 0;
}

