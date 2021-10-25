#pragma once
#include <string>
#include <vector>

enum class Direction {
	North,
	East,
	South,
	West
};
struct Position{
	int x, y;
	Direction facing;
};

class Robot
{
public:
	void Place(std::vector<std::string> tokens);

	void Move();

	void Left();

	void Right();

	void Report();
private:
	bool StringToDirection(Position& p, std::string inp);
	bool convertToPosition(Position& p, std::string x, std::string y, std::string facing);
	bool IsPositionOnBoard(Position p);

	Position mCurrentPosition = {0, 0, Direction::North};
	bool mIsRobotPlaced = false;
};

