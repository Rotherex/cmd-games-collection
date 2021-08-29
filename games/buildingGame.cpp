#include <iostream>
#include <conio.h>
#include <string>

#include <cstdio>
#include <map>

char map[10][10];

struct Vector2 {
	int x;
	int y;
};

int blocksMined;
int frames;

Vector2 playerPos;

enum class Direction
{
	Up,
	Right,
	Down,
	Left
};


Vector2 neighbourPostionInDirection(const Vector2& initialPosition, Direction direction)
{
	Vector2 newPosition;

	switch (direction)
	{
	case Direction::Up:
		newPosition = { playerPos.x - 1, playerPos.y };
		break;

	case Direction::Down:
		newPosition = { playerPos.x + 1, playerPos.y };
		break;

	case Direction::Left:
		newPosition = { playerPos.x, playerPos.y - 1 };

		break;

	case Direction::Right:
		newPosition = { playerPos.x, playerPos.y + 1 };

		break;
	}

	return newPosition;
};

void setPositionToNeighbour(const Vector2& positionToSet, bool IS_BLOCK_PLACED)
{
	if (!IS_BLOCK_PLACED) {

		map[playerPos.x][playerPos.y] = '.';

	}
	else {
		map[playerPos.x][playerPos.y] = '#';
	}
	map[positionToSet.x][positionToSet.y] = 'P';

	playerPos.x = positionToSet.x;
	playerPos.y = positionToSet.y;
};

void removeBlockFromDirection(Direction dir)
{
	switch (dir)
	{
	case Direction::Up:
		map[playerPos.x - 1][playerPos.y] = '.';
		break;

	case Direction::Down:
		map[playerPos.x + 1][playerPos.y] = '.';
		break;

	case Direction::Left:
		map[playerPos.x][playerPos.y - 1] = '.';
		break;

	case Direction::Right:
		map[playerPos.x][playerPos.y + 1] = '.';
		break;
	}

	blocksMined += 1;
};

bool isPlayerOutOfBounds(Direction dir)
{
	switch (dir)
	{
	case Direction::Up:
		if (playerPos.x == 0) return true;
		break;

	case Direction::Down:
		if (playerPos.x == 9) return true;
		break;

	case Direction::Left:
		if (playerPos.y == 0) return true;
		break;

	case Direction::Right:
		if (playerPos.y == 9) return true;
		break;
	}

	return false;
}

void placeBlockBelowPlayer() {
	// no params or returning, hardcoded placing below the player

	map[playerPos.x][playerPos.y] = '#';

	blocksMined -= 1;
}

bool checkCollisions(Direction collisionDir)
{
	Vector2 newPos = neighbourPostionInDirection(playerPos, collisionDir);
	return map[newPos.x][newPos.y] == '#';
};

class Command
{
public:
	virtual void execute(char userCom) = 0;
};

class MoveCommand : public Command
{
private:

	Vector2 newPos;

	void playerMove(Direction dir)
	{

		newPos = neighbourPostionInDirection(playerPos, dir);

		if (!checkCollisions(dir)) {
			if(!isPlayerOutOfBounds(dir)) setPositionToNeighbour(newPos, false);
		}
		else {
			// we know theres a collision for a block, remove it.

			removeBlockFromDirection(dir);

			if (!isPlayerOutOfBounds(dir)) setPositionToNeighbour(newPos, false);
		}

	}

public:

	virtual void execute(char userCom) override
	{
		switch (userCom)
		{
		case 'w':
			playerMove(Direction::Up);
			break;
		case 'a':
			playerMove(Direction::Left);
			break;
		case 's':
			playerMove(Direction::Down);
			break;
		case 'd':
			playerMove(Direction::Right);
			break;
		};
	}
};

class PlaceCommand : public Command
{
private:
	Direction dir = Direction::Up;
	Vector2 newPos;

	void placeBlock()
	{
		// if player has enough blocks, place one of them, no need todo a func for checking the value

		if (blocksMined > 0) {
			
			newPos = neighbourPostionInDirection(playerPos, dir);

			placeBlockBelowPlayer();

			setPositionToNeighbour(newPos, true);
		}
	}

public:
	virtual void execute(char userCom) override {
		// we are not using the userCom for anything deal with it :trol:

		placeBlock();
	}
};

void generateMap()
{
	for (int i = 4; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			map[i][j] = '#';
		}
	}

	for (int k = 0; k < 4; k++) {
		for (int l = 0; l < 10; l++) {
			map[k][l] = '.';
		}
	}

	map[3][7] = 'P';
}

void drawMap()
{
	system("cls");

	std::cout << "Amount of blocks: " << std::to_string(blocksMined) << std::endl;
	std::cout << "Amount of turns: " << std::to_string(frames) << std::endl;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {

			std::cout << map[i][j] << ' ';
		}

		std::cout << '\n';
	}
}

char checkForInput()
{
	return (char)_getch();
}

int main()
{
	playerPos.x = 3;
	playerPos.y = 7;

	std::map<std::string, Command*> commandMap = {
		{"move", new MoveCommand()},
		{"place", new PlaceCommand()},
	};

	generateMap();

	for (; ;) {

		drawMap();

		char userInput = checkForInput();

		if (userInput == 'w'
			|| userInput == 'a'
			|| userInput == 's'
			|| userInput== 'd')
		{
			commandMap["move"]->execute(userInput);
		}

		if (userInput == 'p')
		{
			commandMap["place"]->execute(userInput);
		}
		frames += 1;

		std::cout << playerPos.y;
	}
}
