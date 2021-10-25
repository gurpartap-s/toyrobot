#include "Robot.h"
#include <iostream>

using namespace std;

std::vector<std::string> dirEnumStrings = { "North", "East", "South", "West" };

const int MinPos = 0;
const int MaxPos = 4;

bool Robot::StringToDirection(Position& p, string inp) {
	for (unsigned int iter = 0; iter < dirEnumStrings.size(); iter++) {
		if (!_stricmp(inp.c_str(), dirEnumStrings[iter].c_str())) {
			p.facing = static_cast<Direction>(iter);
			return true;
		}
	}
	cout << "Invalid direction" << endl;
	return false;
}

bool Robot::convertToPosition(Position& p, string x, string y, string facing) {
	try {
		p.x = stoi(x);
		p.y = stoi(y);

		if (!StringToDirection(p, facing))
			return false;

		return true;
	}
	catch (exception const& ex) {
		cout << ex.what() << endl;
	}

	return false;
}

bool Robot::IsPositionOnBoard(Position p) {
	if (p.x >= MinPos && p.x <= MaxPos
		&& p.y >= MinPos && p.y <= MaxPos){
		return true;
	}
	cout << "Invalid position" << endl;
	return false;
}

void Robot::Place(vector<string> tokens) {
	Position pos;
	if (!convertToPosition(pos, tokens[1], tokens[2], tokens[3])) {
		return;
	}
	if (!IsPositionOnBoard(pos)) {
		return;
	}

	mCurrentPosition = pos;
	mIsRobotPlaced = true;
}

void Robot::Move() {
	if (!mIsRobotPlaced) {
		return;
	}
	
	Position pos = mCurrentPosition;
	switch (pos.facing) {
	case Direction::North:
		pos.y++;
		break;
	case Direction::West:
		pos.x--;
		break;
	case Direction::South:
		pos.y--;
		break;
	case Direction::East:
		pos.x++;
		break;
	}
	if (!IsPositionOnBoard(pos))
		return;
	mCurrentPosition = pos;
}

void Robot::Left() {
	if (!mIsRobotPlaced) {
		return;
	}

	int dir = static_cast<int>(mCurrentPosition.facing);
	dir = (dir == 0) ? 3 : dir-1;
	mCurrentPosition.facing = static_cast<Direction>(dir);
}

void Robot::Right() {
	if (!mIsRobotPlaced) {
		return;
	}

	int dir = static_cast<int>(mCurrentPosition.facing);
	dir = (++dir)%4;
	mCurrentPosition.facing = static_cast<Direction>(dir);
}

Position Robot::Report() {
	if (!mIsRobotPlaced) {
		return {-1, -1, Direction::North};
	}
	return mCurrentPosition;
}
