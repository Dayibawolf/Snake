#include "Body.h"


void Body::append(int xx, int yy)
{
	x.push_back(0);
	y.push_back(0);
	if (x.size() > 1)
	{
		for (int i = x.size()-1; i > 0; i--)
		{
			x[i] = x[i - 1];
			y[i] = y[i - 1];
		}
	}
	x[0] = xx;
	y[0] = yy;
}

int Body::size()
{
	return x.size();
}

void Body::move(int xx, int yy)
{
	lastx = x.back();
	lasty = y.back();
	for (int i = x.size() - 1; i > 0; i--)
	{
		x[i] = x[i - 1];
		y[i] = y[i - 1];
	}
	x[0] = x[0] + xx;
	y[0] = y[0] + yy;
}

int Body::endx()
{
	return x.back();
}

int Body::endy()
{
	return y.back();
}

void Body::setfood(Body &b)
{
	bool yes;
	do
	{
		yes = true;
		srand((unsigned)time(0));
		lastx = rand() % 20;
		lasty = rand() % 20;
		for (int i = 0; i < b.size(); i++)
		{
			if (lastx == b.x[i] && lasty == b.y[i]) yes = false;
		}
	} while (!yes);
}

Body::Body()
{
}


Body::~Body()
{
}
