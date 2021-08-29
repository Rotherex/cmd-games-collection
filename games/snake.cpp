#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>

bool gameOver;

const int gameWidth = 20;
const int gameHeight = 20;
int posX, posY, fruitX, fruitY, score;

int tailX[100], tailY[100];
int nTail;

enum class Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

void endScreen();

void Setup()
{
	gameOver = false;

	posX = gameWidth / 2;
	posY = gameHeight / 2;

	dir = Direction::STOP;

	fruitX = rand() % gameWidth;
	fruitY = rand() % gameHeight;

	nTail = 0;
	score = 0;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = Direction::LEFT;
			break;
		case 'd':
			dir = Direction::RIGHT;
			break;
		case 'w':
			dir = Direction::UP;
			break;
		case 's':
			dir = Direction::DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Draw()
{
	system("cls");

	for (int i = 0; i < gameWidth + 2; i++)
	{
		std::cout << "#";
	};

	std::cout << std::endl;

	for (int i = 0; i < gameHeight; i++)
	{
		for (int j = 0; j < gameWidth; j++)
		{
			if (j == 0)
			{
				std::cout << "#";
			}

			if (i == posY && j == posX)
			{
				std::cout << "O";
			}
			else if(i == fruitY && j == fruitX)
			{
				std::cout << "F";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						std::cout << "o";
						print = true;
					}
				}
				if (!print)
					std::cout << " ";
			}

			if (j == gameWidth - 1) 
			{
				std::cout << "#";
			}
		}

		std::cout << std::endl;
	};

	for (int i = 0; i < gameWidth + 2; i++)
	{
		std::cout << "#";
	};

	std::cout << std::endl;
	std::cout << "Score: " << score << std::endl;
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = posX;
	tailY[0] = posY;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case Direction::LEFT:
		posX--;
		break;
	case Direction::RIGHT:
		posX++;
		break;
	case Direction::UP:
		posY--;
		break;
	case Direction::DOWN:
		posY++;
		break;
	default:
		break;
	}

	// wall collision detect

	if (posX >= gameWidth) posX = 0; else if (posX < 0) posX = gameWidth - 1;
	if (posY >= gameHeight) posY = 0; else if (posY < 0) posY = gameHeight - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == posX && tailY[i] == posY)
			gameOver = true;

	if (posX == fruitX && posY == fruitY)
	{
		score += 10;
		fruitX = rand() % gameWidth;
		fruitY = rand() % gameHeight;
		nTail++;
	}
}

void main()
{
	srand(time(NULL));

	Setup();
	
	while (!gameOver)
	{
		// main game loop

		Draw();
		Input();
		Logic();

		Sleep(10);
	}

	endScreen();
}

void endScreen()
{
	system("cls");

	std::cout << "You lost! Final score: " << score << std::endl;
	std::cout << "Play again? [Y]es, [N]o" << std::endl;

	char input = _getch();

	if (input == 'Y' || 'y') {
		main();
	}
	else {
		exit(1);
	}
}
