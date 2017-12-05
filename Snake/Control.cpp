#include "Control.h"
#define up 72
#define down 80
#define left 75
#define right 77
#define Key_Down(key) ((GetAsyncKeyState(key)&0x8000)? 1:0)



bool Control::IsActiveWindow()
{
	hSelf = GetConsoleWindow();
	hOther = GetForegroundWindow();
	if (hSelf == hOther) return true;
	else 	return false;
}

bool Control::isgameover(Body snake)
{
	if (snake.x[0] < 0 || snake.x[0]>19) return true;  //判断是否撞墙
	if (snake.y[0] < 0 || snake.y[0]>19) return true;
	for (int i = 1; i < snake.size(); i++)  // 判断是否吃到自己
	{
		if (snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i])
			return true;
	}
	return false;
}

void Control::initial()
{
	dis.initialscreen();
	dis.startmovie();
	dis.showslect();
	SlectLevel();

	level = 10 - level;
	snake.append(1, 1);   //构造蛇的身体
	snake.append(2, 1);
	snake.append(3, 1);
	snake.append(4, 1);
	food.setfood(snake);   //放置食物
	dis.ifshowdw(false);
	dis.gmregion();    //画出游戏区域
	dis.showscore();     //显示当前游戏得分
	dis.showtime();     //显示时间
	dis.showhelp(10-level);   //显示帮助信息
	dis.drawsnake(snake);     //画出蛇
	dis.drawfood(food);     //显示食物
}

void Control::rungame()
{
	initial();      //初始化游戏
	while (true)
	{
		if (!IsActiveWindow()) dis.pause();
		Sleep(level*50);
		if (kbhit())  
		{
			key = getch();    //读取键盘输入
			if (key == '\r') dis.pause();
			if (key == 'q' || key == 'Q') exit = true;
			if (key == 0xE0)
			{
				key = getch();
				switch (key)   //选择方向
				{
				case up:
					if (direct != DOWN)
						direct = UP;
					break;
				case down:
					if (direct != UP)
						direct = DOWN;
					break;
				case left:
					if (direct != RIGHT)
						direct = LEFT;
					break;
				case right:
					if (direct != LEFT)
						direct = RIGHT;
					break;
				default:
					break;
				}
			}
			while (kbhit()) getch();  //清除多余的输入
		}
		if (snake.x[0] + direct.X == food.lastx && snake.y[0] + direct.Y == food.lasty)
		{
			snake.append(food.lastx, food.lasty);  //吃到食物蛇边变长
			dis.drawsnake(snake);     //显示更新后的蛇
			food.setfood(snake);      //放置食物
			dis.drawfood(food);       //显示食物
			score = snake.size() - 4; //计算得分
			dis.showscore(score);     //显示得分
			if (score == 25) level = 1;  //达到25分时加速
		}
		else
		{
			snake.move(direct.X, direct.Y);

			//判断游戏是否结束
			if (isgameover(snake) || exit) break;

			dis.drawsnake(snake);  //画出更新后的蛇
			dis.cleantail(snake);
		}
		dis.showtime();   //更新时间
	}
	dis.gameover(); //显示游戏结束
}

bool Control::GetMouseClickPos(COORD *pos)
{
	HWND hwnd = GetForegroundWindow();
	POINT poi;
		if (Key_Down(MOUSE_MOVED))
		{
			GetCursorPos(&poi);
			ScreenToClient(hwnd, &poi);
			if (!Key_Down(MOUSE_MOVED))
			{
				*pos = { short(poi.x / 8), short(poi.y / 16) };
				return true;
			}
		}
	else return false;
}

void Control::ClickOrOuttime(bool * flag, COORD * pos, int second)
{
	DWORD Tcur = GetTickCount(), Tsta = GetTickCount();
	while (Tcur - Tsta < second * 1000)
	{
		Tcur = GetTickCount();
		if (*flag = GetMouseClickPos(pos)) break;
	}
}

void Control::SlectLevel()
{
	/*while (cin >> level)
	{
	if (level < 1 || level>9) cout << "输入错误！！请重新输入：";
	else break;
	}*/
	COORD pos;
	Display dis;
	while (1)
	{
		if (GetMouseClickPos(&pos))
		{
			if (pos.X >= 19 && pos.X <= 27)
			{
				if (pos.Y >= 9 && pos.Y < 11)
				{
					level = 1;
					dis.SlectRec(17, 10);
					break;
				}
				else if (pos.Y > 11 && pos.Y < 13)
				{
					level = 4;
					dis.SlectRec(17, 12);
					break;
				}
				else if (pos.Y > 13 && pos.Y <= 15)
				{
					level = 8;
					dis.SlectRec(17, 14);
					break;
				}
			}
		}
	}
}

Control::Control()
{
	direct = { 1,0 };  //向右
}


Control::~Control()
{
}

bool operator!=(COORD & a, COORD & b)
{
	if(a.X != b.X && a.Y != b.Y) return true;
	else return false;
}
