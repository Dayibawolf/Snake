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
	if (snake.x[0] < 0 || snake.x[0]>19) return true;  //�ж��Ƿ�ײǽ
	if (snake.y[0] < 0 || snake.y[0]>19) return true;
	for (int i = 1; i < snake.size(); i++)  // �ж��Ƿ�Ե��Լ�
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
	snake.append(1, 1);   //�����ߵ�����
	snake.append(2, 1);
	snake.append(3, 1);
	snake.append(4, 1);
	food.setfood(snake);   //����ʳ��
	dis.ifshowdw(false);
	dis.gmregion();    //������Ϸ����
	dis.showscore();     //��ʾ��ǰ��Ϸ�÷�
	dis.showtime();     //��ʾʱ��
	dis.showhelp(10-level);   //��ʾ������Ϣ
	dis.drawsnake(snake);     //������
	dis.drawfood(food);     //��ʾʳ��
}

void Control::rungame()
{
	initial();      //��ʼ����Ϸ
	while (true)
	{
		if (!IsActiveWindow()) dis.pause();
		Sleep(level*50);
		if (kbhit())  
		{
			key = getch();    //��ȡ��������
			if (key == '\r') dis.pause();
			if (key == 'q' || key == 'Q') exit = true;
			if (key == 0xE0)
			{
				key = getch();
				switch (key)   //ѡ����
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
			while (kbhit()) getch();  //������������
		}
		if (snake.x[0] + direct.X == food.lastx && snake.y[0] + direct.Y == food.lasty)
		{
			snake.append(food.lastx, food.lasty);  //�Ե�ʳ���߱߱䳤
			dis.drawsnake(snake);     //��ʾ���º����
			food.setfood(snake);      //����ʳ��
			dis.drawfood(food);       //��ʾʳ��
			score = snake.size() - 4; //����÷�
			dis.showscore(score);     //��ʾ�÷�
			if (score == 25) level = 1;  //�ﵽ25��ʱ����
		}
		else
		{
			snake.move(direct.X, direct.Y);

			//�ж���Ϸ�Ƿ����
			if (isgameover(snake) || exit) break;

			dis.drawsnake(snake);  //�������º����
			dis.cleantail(snake);
		}
		dis.showtime();   //����ʱ��
	}
	dis.gameover(); //��ʾ��Ϸ����
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
	if (level < 1 || level>9) cout << "������󣡣����������룺";
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
	direct = { 1,0 };  //����
}


Control::~Control()
{
}

bool operator!=(COORD & a, COORD & b)
{
	if(a.X != b.X && a.Y != b.Y) return true;
	else return false;
}
