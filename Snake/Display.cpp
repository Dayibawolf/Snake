#include "Display.h"
#include<Windows.h>
#include<iostream>
#include<conio.h>
using namespace std;


void Display::cleanscreen()
{
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO bInfo; // 存储窗口信息
	COORD pos = { 0, 0 };
	DWORD lpNum;

	// 获取标准输出设备句柄
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	FillConsoleOutputCharacter(hOut, ' ', bInfo.dwSize.X * bInfo.dwSize.Y, pos, &lpNum);
}

void Display::initialscreen()
{
	SetConsoleTitle(TEXT("Snake game edited by Tao"));//设置cmd窗口标题
	system("mode con cols=67 lines=26");
	system("color F0");
}

void Display::setpos(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void Display::setoutcolor(int color)
{                                                      //前景色：1 蓝；2 绿； 4 红； 8 高亮
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);     //背景色：16 蓝； 32 绿； 64 红； 128 高亮
	WORD backcolor = 16|32|64|128;      //输出背景色                             
	switch (color)
	{
	case 0:
		SetConsoleTextAttribute(hOut, 4 | 8 | backcolor);  //高亮红：0
		break;                                                            
	case 1:                                                          
		SetConsoleTextAttribute(hOut, 2 | 8 | backcolor);  //高亮绿：1
		break;
	case 2:
		SetConsoleTextAttribute(hOut, 1 | 8 | backcolor);  //高亮蓝：2
		break;
	case 3:
		SetConsoleTextAttribute(hOut, 0 | backcolor);  //黑：3
		break;
	case 4:
		SetConsoleTextAttribute(hOut, 1 | 2 | 4 | backcolor);  //高亮白：4
		break;
	case 5:
		SetConsoleTextAttribute(hOut, 4 | 2 | 8 | backcolor);  //高亮黄：5
		break;
	case 6:
		SetConsoleTextAttribute(hOut, 4 |2| 8 | 0);    //高亮黄|黑 ：6
		break;
	case 7:
		SetConsoleTextAttribute(hOut, 4 | 8 | backcolor);
		break;
	case 8:
		SetConsoleTextAttribute(hOut, 4 | 8 | backcolor);
		break;
	case 9:
		SetConsoleTextAttribute(hOut, 4 | 8 | backcolor);
		break;
	}
}

void Display::gmregion()
{
	system("cls");
	setoutcolor(6);
	setpos(Xbegin, Ybegin-3);
	cout << "***************>>SNAKE<<***************";
	setoutcolor(2);
	setpos(Xbegin-2, Ybegin-1);
	for (int i = 0; i < 22;i++) cout<<"* "; // 画出上边界

	for (int i = 0; i < 20; i++)   //画出左边界
	{
		setpos(Xbegin - 2, i+ Ybegin);
		cout << "*";
	}
	for (int i = 0; i < 20; i++)    //画出右边界
	{
		setpos(Xbegin+40,i + Ybegin);
		cout << "*";
	}
	setpos(Xbegin-2, Ybegin+20);    //画出下边界
	for (int i = 0; i < 22; i++) cout << "* ";
}

void Display::drawsnake(Body &snake)
{
	srand((unsigned)time(0));
	setoutcolor(2);
	setpos(Xbegin + 2 * snake.x[0], Ybegin + snake.y[0]);
	cout << "※";
	for (int i = 1; i < snake.size()-2; i++)
	{
		setpos(Xbegin + 2 * snake.x[i], Ybegin + snake.y[i]);
		cout << "█";
	}
	setpos(Xbegin + 2 * snake.x[snake.size() - 2], Ybegin + snake.y[snake.size() - 2]);
	cout << "■";
	setpos(Xbegin + 2 * snake.x.back(), Ybegin + snake.y.back());
	cout << "◆";
}

void Display::cleantail(Body &snake)
{
	if (snake.lastx != -1 && !(snake.lastx == snake.x[0] && snake.lasty == snake.y[0]))
	{
		setpos(Xbegin + 2 * snake.lastx, Ybegin + snake.lasty);
		cout << "  ";
	}
}

//显示食物
void Display::drawfood(Body & food)
{
	setoutcolor(0);
	setpos(Xbegin + 2 * food.lastx, Ybegin + food.lasty);
	cout << "█";
}

//控制是否隐藏光标
void Display::ifshowdw(bool Y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO Cur;
	GetConsoleCursorInfo(handle, &Cur);//获取控制台光标信息  
	Cur.bVisible = Y; //隐藏控制台光标  
	SetConsoleCursorInfo(handle, &Cur);//设置控制台光标状态
}

//显示游戏帮助信息
void Display::showhelp(int level, int pos_X, int pos_Y)
{
	setoutcolor(1);
	setpos(pos_X, pos_Y);
	cout << "使用方向键控制方向:";
	setpos(pos_X, pos_Y+2);
	cout << "←↑↓→";
	setpos(pos_X, pos_Y + 4);
	cout << "暂停：Enter 键";
	setpos(pos_X, pos_Y + 6);
	cout << "退出：Q 键";
	setpos(pos_X, pos_Y + 8);
	cout << "当前游戏难度：";
	switch (level)
	{
	case 1:
		cout << "傻瓜";
		break;
	case 4:
		cout << "一般";
		break;
	case 8:
		cout << "困难";
		break;
	default:
		break;
	}
}

//显示得分模块
void Display::showscore(int score, int pos_X, int pos_Y)
{
	setoutcolor(3);
	setpos(pos_X , pos_Y);
	cout << "■>>^_^<<■";
	setoutcolor(2);
	setpos(pos_X , pos_Y +2);
	cout << "得分：" << score;
}

//显示时间
void Display::showtime(int pos_X, int pos_Y)
{
	setoutcolor(3);
	setpos(pos_X, pos_Y);
	system("time /t");
	setpos(pos_X, pos_Y+2);
	system("date /t");
}

//显示暂停信息
void Display::pause(int pos_X,int pos_Y)
{
	setoutcolor(1);
	setpos(pos_X , pos_Y + 2);
	cout << "按任意键继续...";
	while (!kbhit())
	{
		setoutcolor(1);
		setpos(pos_X , pos_Y );
		cout << "^_^ 休息一下！！";
		Sleep(600);
		setpos(pos_X , pos_Y );
		cout << "                ";
		Sleep(600);
		showtime();
	}
	while (kbhit()) getch();  //清除输入字符
	setpos(pos_X , pos_Y + 2);
	cout << "               ";
}

//显示开始动画
void Display::startmovie()
{
	ifshowdw(false);
	Body snake;
	snake.append(1, 1);
	snake.append(2, 1);
	snake.append(3, 1);
	snake.append(4, 1);
	gmregion();
	for (int i = 0; i < 4; i++)
	{
		drawsnake(snake);
		cleantail(snake);
		snake.move(1, 0);
		Sleep(100);
	}
	for (int i = 0; i < 8; i++)
	{
		drawsnake(snake);
		cleantail(snake);
		snake.move(0, 1);
		Sleep(100);
	}
	for (int i = 0; i < 4; i++)
	{
		drawsnake(snake);
		cleantail(snake);
		snake.move(-1, 0);
		Sleep(100);
	}
	for (int i = 0; i < 4; i++)
	{
		drawsnake(snake);
		cleantail(snake);
		snake.move(0, -1);
		Sleep(100);
	}
	for (int i = 0; i < 4; i++)
	{
		drawsnake(snake);
		cleantail(snake);
		snake.move(1, 0);
		Sleep(100);
	}
	for (int i = 0; i < 4; i++)
	{
		drawsnake(snake);
		cleantail(snake);
		Sleep(100);
		cout << "             ";
		Sleep(100);
	}
}

//显示游戏难度选项
void Display::showslect(int pos_X, int pos_Y)
{
	setpos(pos_X+2, pos_Y+2);
	cout << "********";
	setpos(pos_X+2, pos_Y + 3);
	cout << " 1:傻瓜";
	setpos(pos_X+2, pos_Y + 4);
	cout << "********";
	setpos(pos_X+2, pos_Y + 5);
	cout << " 2:一般";
	setpos(pos_X+2, pos_Y + 6);
	cout << "********";
	setpos(pos_X+2, pos_Y + 7);
	cout << " 3:困难";
	setpos(pos_X+2, pos_Y + 8);
	cout << "********";
	setpos(pos_X, pos_Y);
	cout << "选择游戏难度：";
	//ifshowdw(true);
}

void Display::SlectRec(int pos_X, int pos_Y)
{
	for (int i = 0; i < 4; i++)
	{
		setpos(pos_X, pos_Y);
		cout << ">>";
		setpos(pos_X + 10, pos_Y);
		cout << "<<";
		Sleep(200);
		setpos(pos_X, pos_Y);
		cout << "  ";
		setpos(pos_X + 10, pos_Y);
		cout << "  ";
		Sleep(200);
	}
}

void Display::ShakeWindow()
{
	int SHAKE = 5;
	RECT rect;
	HWND hwnd = GetForegroundWindow();
	GetWindowRect(hwnd, &rect);

	for (int i = 0; i < 6; i++)
	{
		MoveWindow(hwnd, rect.left + SHAKE, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
		Sleep(28);
		MoveWindow(hwnd, rect.left + SHAKE, rect.top - SHAKE, rect.right - rect.left, rect.bottom - rect.top, TRUE);
		Sleep(28);
		MoveWindow(hwnd, rect.left, rect.top - SHAKE, rect.right - rect.left, rect.bottom - rect.top, TRUE);
		Sleep(28);
		MoveWindow(hwnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
	}
}

//显示游戏结束信息
void Display::gameover()
{
	ShakeWindow();
	setpos(10, 20);
	cout << "Gameover!";
	system("pause");
}

Display::Display()
{
}


Display::~Display()
{
}
