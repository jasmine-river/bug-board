#pragma once
#include "Bug.h"
using namespace std;

class Crawler : public Bug
{
public:
	Crawler(int, int, int, int, int);
	virtual void move();
	~Crawler();
};