// ToyRobot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Robot.h"

using namespace std;

extern std::vector<std::string> dirEnumStrings;

vector<string> tokenize(const string& line, const string& delims)
{
    vector<string> tokens;
    size_t start = line.find_first_not_of(delims), end = 0;

    while ((end = line.find_first_of(delims, start)) != string::npos)
    {
        tokens.push_back(line.substr(start, end - start));
        start = line.find_first_not_of(delims, end);
    }
    if (start != string::npos)
        tokens.push_back(line.substr(start));

    return tokens;
}

bool convertToPosition(Position &p, string x, string y, string facing) {
    try {
        p.x = stoi(x);
        p.y = stoi(y);
    
        if (!_stricmp(facing.c_str(),"NORTH")) {
            p.facing = Direction::North;
        }
        else if (!_stricmp(facing.c_str(), "SOUTH")) {
            p.facing = Direction::South;
        }
        else if (!_stricmp(facing.c_str(), "EAST")) {
            p.facing = Direction::East;
        }
        else if (!_stricmp(facing.c_str(), "WEST")) {
            p.facing = Direction::West;
        }
        else {
            cout << "Incorrect direction" << endl;
            return false;
        }
        return true;
    }
    catch (exception const& ex) {
        cout << ex.what() << endl;
    }

    return false;
}
int main()
{
    string delims = " ,";
    ifstream infile("test_data.txt");
    string line;

    Robot rb;

    while (getline(infile, line)) {
        auto tokens = tokenize(line, delims);
        if (tokens.size() == 0)
            continue;
        if (!_stricmp(tokens[0].c_str(), "PLACE")) {
            if (tokens.size() < 4) {
                cout << "Incorrect PLACE command format" << endl;
            }
            else {
                rb.Place(tokens);
            }
        }
        else if (!_stricmp(tokens[0].c_str(),"MOVE")) {
            rb.Move();
        }
        else if (!_stricmp(tokens[0].c_str(), "LEFT")) {
            rb.Left();
        }
        else if (!_stricmp(tokens[0].c_str(), "RIGHT")) {
            rb.Right();
        }
        else if (!_stricmp(tokens[0].c_str(), "REPORT")) {
            auto pos = rb.Report();
            if (pos.x != -1) {
                cout << pos.x << "," << pos.y << "," << dirEnumStrings[static_cast<int>(pos.facing)] << endl;
            }
        }
        else {
            cout << "Unsupported command" << endl;
        }
    }
}
