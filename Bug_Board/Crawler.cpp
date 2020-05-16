#include "Crawler.h"
#include <list>  /* list */
#include <utility>  /* pair */
#include <stdlib.h>  /* rand */
using namespace std;

// Constructors
Crawler::Crawler(int id = 1, int x = 0, int y = 0, int direction = 1, int size = 1)
	: Bug{ id, x, y, direction, size }
{}

// Functions
void Crawler::move()
{
	// Only move if alive
	if (alive)
	{
		if (isWayBlocked())
		{
			direction = rand() % 4 + 1;
			Crawler::move();
		}
		else
		{
			switch (direction)
			{
			case 1:
				position.second--; break;
			case 2:
				position.first++; break;
			case 3:
				position.second++; break;
			case 4:
				position.first--; break;
			}
			path.push_back(position);
		}
	}
}