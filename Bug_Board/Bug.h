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

	// Getters & Setters
	int getID();
	int getSize();
	int getDirection();
	string getDirectionInText();
	pair<int, int> getPosition();
	string getPositionInBrackets();
	string getStatusInText();
	list<pair<int, int>> getPath();
	string getPathInText();
	void setSize(int);
	void changeStatus();
};