#pragma once
#include "Bug.h"
using namespace std;

class Hopper : public Bug
{
private:
	int hopLength;

public:
	Hopper(int, int, int, int, int, int);
	virtual void move();
	bool canHopFullLength();
	~Hopper();

	// Getters
	int getHopLength();
};