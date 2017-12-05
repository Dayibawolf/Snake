#pragma once
#include<iostream>
#include<string>
#include<conio.h>
#include"Body.h"
#include"Display.h"
using namespace std;

class Control
{
private:
	HWND          hSelf, hOther;  //用于判断是否为活动窗口
	int           level = 0, score = 0;
	bool          exit = false;
	Body          snake, food;
	Display       dis;
	unsigned char key;
	COORD         direct;
	COORD         UP = { 0,-1 };
	COORD         DOWN = { 0,1 };
	COORD         LEFT = { -1,0 };
	COORD         RIGHT = { 1,0 };

private:
	friend bool operator != (COORD &a, COORD &b);
public:
	bool IsActiveWindow();
	bool isgameover(Body snake);
	void initial();
	void rungame();
	bool GetMouseClickPos(COORD *pos);
	void ClickOrOuttime(bool *flag, COORD* pos, int second);
	void SlectLevel();
	Control();
	~Control();
};

