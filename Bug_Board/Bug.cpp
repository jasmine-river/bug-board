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

// Getters
int Bug::getID()
{
	return id;
}

int Bug::getSize()
{
	return size;
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

string Bug::getPositionInBrackets()
{
	return "(" + to_string(position.first) + "," + to_string(position.second) + ")";
}

string Bug::getStatus()
{
	if (alive)
	{
		return "alive";
	}
	else
	{
		return "dead";
	}
}