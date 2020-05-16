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
	Bug* killer;

public:
	virtual void move() = 0;
	bool isWayBlocked();
	Bug(int, int, int, int, int);
	virtual ~Bug();

	// Getters & Setters
	int getID();
	int getSize();
	int getDirection();
	string getDirectionInText();
	pair<int, int> getPosition();
	string getPositionInBrackets();
	string getStatusInText();
	string getPathInText();
	Bug* getKiller();
	void setSize(int);
	void changeStatus();
	void setKiller(Bug*);
};