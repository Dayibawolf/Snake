#pragma once
#include"Body.h"
#define Xbegin 4
#define Ybegin 4
class Display
{
public:
	void cleanscreen();
	void initialscreen();
	void setpos(int x, int y);
	void setoutcolor(int color);
	void gmregion();
	void drawsnake(Body &snake);
	void cleantail(Body &snake);
	void drawfood(Body &food);
	void ifshowdw(bool Y);
	void showhelp(int level =0, int pos_X = Xbegin + 43, int pos_Y = Ybegin + 12);
	void showscore(int score = 0, int pos_X = Xbegin + 43, int pos_Y = Ybegin - 1);
	void showtime(int pos_X = Xbegin + 43, int pos_Y = Ybegin + 7);
	void pause(int pos_X = Xbegin + 43, int pos_Y = Ybegin + 3);
	void startmovie();
	void showslect(int pos_X = Xbegin+ 13, int pos_Y = Ybegin + 3);
	void SlectRec(int pos_X, int pos_Y);
	void ShakeWindow();
	void gameover();
	Display();
	~Display();
};

