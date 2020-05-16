#include "Bug.h"
#include <list>  /* list */
#include <utility>  /* pair */
#include <string>
using namespace std;

void Bug::move() {}

bool Bug::isWayBlocked()
{
	if ((direction == 1 && position.second == 0) || (direction == 2 && position.first == 10) || (direction == 3 && position.second == 10) || (direction == 4 && position.first == 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Bug::Bug(int id = 1, int x = 0, int y = 0, int direction = 1, int size = 1)
	: id{ id }, direction{ direction }, size{ size }
{
	alive = true;
	position.first = x;
	position.second = y;
	path.push_back(position);
}

// Getters & Setters
int Bug::getID()
{
	return id;
}

int Bug::getSize()
{
	return size;
}

int Bug::getDirection()
{
	return direction;
}

string Bug::getDirectionInText()
{
	switch (direction)
	{
	case 1:
		return "North";
	case 2:
		return "East";
	case 3:
		return "South";
	case 4:
		return "West";
	}
}

pair<int, int> Bug::getPosition()
{
	return position;
}

string Bug::getPositionInBrackets()
{
	return "(" + to_string(position.first) + "," + to_string(position.second) + ")";
}

string Bug::getStatusInText()
{
	if (alive)
	{
		return "Alive";
	}
	else
	{
		return "Dead";
	}
}

list<pair<int, int>> Bug::getPath()
{
	return path;
}

string Bug::getPathInText()
{
	string pathText;
	for (pair<int, int> position : path)
	{
		pathText += "(" + to_string(position.first) + "," + to_string(position.second) + ")";

		position != path.back() ? (pathText += ",") : (pathText += "");
	}
	return pathText;
}

void Bug::setSize(int newSize)
{
	if (newSize > 20)
	{
		size = 20;
	}
	else if (newSize < 1)
	{
		size = 1;
	}
	else
	{
		size = newSize;
	}
}

void Bug::changeStatus()
{
	if (alive)
	{
		alive = false;
	}
	else
	{
		alive = true;
	}
}