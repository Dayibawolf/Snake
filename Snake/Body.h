#pragma once
#include<vector>
#include<Windows.h>
#include<ctime>
#include<cstdlib>
using namespace std;
class Body
{
public:
	vector<int> x, y;
	int lastx = -1, lasty = -1;
	void append(int xx, int yy);
	int size();
	void move(int x, int y);
	int endx();
	int endy();
	void setfood(Body &b);
	Body();
	~Body();
};

