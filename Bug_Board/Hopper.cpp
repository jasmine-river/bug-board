#include "Hopper.h"
#include <list>  /* list */
#include <utility>  /* pair */
#include <stdlib.h>  /* rand */
using namespace std;

// Constructors
Hopper::Hopper(int id = 1, int x = 0, int y = 0, int direction = 1, int size = 1, int hopLength = 2)
	: Bug{ id, x, y, direction, size },
		hopLength{ hopLength }
{}

// Functions
void Hopper::move()
{
	if (isWayBlocked())
	{
		direction = rand() % 4 + 1;
		Hopper::move();
	}
	else if (!canHopFullLength())
	{
		switch (direction)
		{
		case 1:
			position.second = 0; break;
		case 2:
			position.first = 10; break;
		case 3:
			position.second = 10; break;
		case 4:
			position.first = 0; break;
		}
		path.push_back(position);
	}
	else
	{
		switch (direction)
		{
		case 1:
			position.second -= hopLength; break;
		case 2:
			position.first += hopLength; break;
		case 3:
			position.second += hopLength; break;
		case 4:
			position.first -= hopLength; break;
		}
		path.push_back(position);
	}
}

bool Hopper::canHopFullLength()
{
	if ((direction == 1 && (position.second - hopLength) < 0) || (direction == 2 && (position.first + hopLength) > 10) || (direction == 3 && (position.second + hopLength) > 10) || (direction == 4 && (position.first - hopLength) < 0))
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Getters
int Hopper::getHopLength()
{
	return hopLength;
}