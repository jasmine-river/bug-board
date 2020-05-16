#pragma once
#include <list>  /* list */
#include <utility>  /* pair */
#include <string>
using namespace std;

class Bug
{
protected:
	int id, size, direction;
	pair<int, int> position;
	bool alive;
	list<pair<int, int>> path;

public:
	virtual void move() = 0;
	bool isWayBlocked();
	Bug(int, int, int, int, int);

	// Getters
	int getID();
	int getSize();
	string getDirectionInText();
	string getPositionInBrackets();
	string getStatusInText();
	string getPathInText();
};