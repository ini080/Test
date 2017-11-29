#include "draw.h"

CDRAW *CDRAW::getInstance()
{
	static CDRAW draw;
	return &draw;
}

CDRAW::CDRAW()
{
	nX = (40 - SIZE - 1) / 2;
	nY = 11 - SIZE / 2;
}

/* ========================================================================== */
/* ȭ���� Ŀ���� ���̰ų� ����� */
void CDRAW::CursorView(char show)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}

/* ========================================================================== */
/* x, y ��ǥ�� Ŀ���� �����̴� �Լ� */
void CDRAW::gotoxy(int x, int y) /*Ŀ���̵� �Լ� �κ�*/
{
    COORD XY = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}

/* ========================================================================== */
/* �ܼ� ������ �����ϴ� �Լ� */
void CDRAW::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/* ========================================================================== */
/* �ܼ� ������ ���ڿ� ������ �����ϴ� �Լ� */
void CDRAW::SetColor(int color, int bgcolor) 
{

    color &= 0xf;
    bgcolor &= 0xf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}

// ���� �޽����� ȭ�鿡 ������ش�. 
void CDRAW::errMsg(int msg)
{
	msg -= 10;
	const char *str[] = {
		"�̹� ���� ���� �ֽ��ϴ�.\n�ٸ� ���� �����ϼ���.",
		"��� �Դϴ�.\n�ٸ� ���� �����ϼ���.",
		"��� �Դϴ�.\n�ٸ� ���� �����ϼ���.",
		"���� ������ �� �� �����ϴ�.\n�ٸ� ���� �����ϼ���.",
		"�� ���� ���� �� �ֽ��ϴ�"
	};
	MessageBox(NULL, str[msg], "Warning!", MB_OK);
}

void CDRAW::showMsg(int msg)
{
	const char *str[] = {
		"���� �� �����Դϴ�.",
		"���� �� �����Դϴ�.",
		"       ",
		"�� ���Դϴ�.       ",
		"�� ���Դϴ�.       ",
		"���º��Դϴ�.      ",
	};
	
    SetColor(GRAY);
    gotoxy((nX + SIZE + 1) * 2, nY);
    printf("%s", str[msg]);
}

void CDRAW::computerStoneColor(int nColor)
{
	int len;
	const char *strName[] = {
		"COMPUTER ",
		"PLAYER   ",
	};

	const char *strStone = "��";
	len = strlen(strName[0]) + 2;
	
    SetColor(nColor, DARK_YELLOW);
    gotoxy((nX - 1) * 2 - len, nY);
    printf("%s", strStone);
    SetColor(GRAY, DARK_YELLOW);
    printf("%s", strName[0]);
    SetColor(nColor ==  BLACK ? WHITE : BLACK, DARK_YELLOW);
    gotoxy((nX - 1) * 2 - len, nY + 1);
    printf("%s", strStone);
    SetColor(GRAY, DARK_YELLOW);
    printf("%s", strName[1]);
}

void CDRAW::stonePoint(int x, int y)
{
    SetColor(GRAY);
    gotoxy((nX + SIZE + 1) * 2, nY + 1);
    printf("���� ��ġ : %c%d ", 'A' + x - 1, 15 - y + 1);
}

void CDRAW::infoKey()
{
	const char *str[] = {
		"�����̽��� : ��  ��",
		"��  ��  Ű : ��  ��",
		"    U      : ������",
		"Delete Key : PASS      ",
		" ",
		"��� ���� ��������",
		"PASS�ϸ� ���º�"
	};
	
	SetColor(GRAY);
	for(int i = 0; i < 7; i++)
	{
    	gotoxy((nX + SIZE + 1) * 2, nY + 3 + i);
    	printf(str[i]);
	}
}

// ���а� ������ ���ڸ� �˸��� 
// �ѹ��� �� ������ �����. 
bool CDRAW::endMsg(int stone)
{
	const char *winner[] = {"    �� ���Դϴ�.\n    �� ���� �� �Ͻðڽ��ϱ�?     ",
							"    �� ���Դϴ�.\n    �� ���� �� �Ͻðڽ��ϱ�?     ",
							"    ���º��Դϴ�.\n    �� ���� �� �Ͻðڽ��ϱ�?     "};
	showMsg(stone + 3);
	if(MessageBox(NULL, winner[stone], "�� ��", MB_YESNO) == IDYES) return true;
	else return false; 
}

// �ٵ��ǰ� ���� �׸���. 
void CDRAW::printData(int &x, int &y, int type)
{
 	if(x < 1)          x = 1;
	else if(y < 1)     y = 1;
	else if(x > SIZE)  x = SIZE;
	else if(y > SIZE)  y = SIZE;

	const int color[] = {BLACK, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK};
    const char *shape[] = {"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��"};
	
    SetColor(color[type], DARK_YELLOW);
    // ������ ������ 9���� ����� �����ϱ� 
	// ��� �׷��� ���� ��ǥ�� �ְ� ����� �����´�. 
    if(type == LINE) type = getLineNumber(x, y);
    // ������ 0-8���� �̰�, �� �ڿ� ���� ��ġ�Ǿ� ������ 9�� �����ش�. 
    else type += 9;
    gotoxy((x + nX - 1) * 2, y + nY - 1);
    printf("%s", shape[type]);
    SetColor(GRAY);
}

// ���ο� �������� ��ǥ�� ���ڿ� ���ĺ����� ǥ�����ش�.
// ���γ� ���ο� ���ڳ� ���ĺ����� �����ϸ� ��ǥ�� ǥ���� ��
// ȥ���� �� �� ������ ������ ǥ���Ѵ�. 
void CDRAW::printNum()
{
    SetColor(BLACK, DARK_YELLOW);
    //x���� ��� 
    for(int i = 0; i < SIZE; i++) 
    {
    	gotoxy((nX + i) * 2, nY + SIZE);
    	printf("%2c", i + 'A');
	}
	//y���� ��� 
    for(int i = 0, j = SIZE; i < SIZE; i++, j--) 
    {
    	gotoxy((nX - 1) * 2, nY + j - 1);
    	printf("%2d", i + 1);
	}
	gotoxy((nX - 1) * 2, nY + SIZE);
	printf("  ");
    SetColor(GRAY);
}

//������
//������
//������
//������ �Ʒ��� ���� �Ѵ�. 
//0 1 2
//������
//3 4 5
//������
//6 7 8
//������
// �� ����� �ٵ����� ������̴�
// �ٵ����� ��� ����� 
// �� 9���� ��縸 ������ �׷��� �� �ִ�. 
// x�� 0�϶��� ���� ��
// y�� 0�϶��� ���� ���� 
// x,y���� ���� ����� ��ȣ�� ��ȯ�Ѵ�. 

// �ٵ��� ��ü�� �׷��ְ� �ٽ� �׷��� ������
// �׷��� �ϸ� ���� Size�� 19�� �ϰ� ������
// ��ü�� �����ؾ� �ǰ�, ���� ȭ���� ���� �Ÿ� �� �־
// �ʿ��� ���� �׶��׶� �׷��ַ� �̷� �۾��� �Ѵ� ���̴�. 
int CDRAW::getLineNumber(int x, int y)
{
	// ���� ������ 
	if(x == 1)
	{
		// x, y�� �� 0�̸� ���� ��� �𼭸� 
		if(y == 1) return 0;
		// ���� �ϴ� �𼭸� 
		else if(y == SIZE) return 6;
		// ���� ������ 
		else return 3;
	}
	// ������ ������ 
	else if(x == SIZE)
	{
		// ������ ��� �𼭸� 
		if(y == 1) return 2;
		// ������ �ϴ� �𼭸� 
		else if(y == SIZE) return 8;
		// ������ ������ 
		else return 5;
	}
	// ���� ������
	else if(y == 1) return 1;
	// �Ʒ��� ������
	else if(y == SIZE) return 7;
	// ������ ��� + ��� 
	else return 4;
}

//���� �ð��� ȭ�鿡 ǥ�����ش�. 
void CDRAW::drawTime(time_t sec)
{
	int hh, mm;
	
    hh = sec / 3600;
    mm = (sec % 3600) / 60;
    sec = sec %= 60;

	SetColor(SKY_BLUE);
	gotoxy(nX * 2 - 2, nY + SIZE +  1);
	printf("%02d : %02d : %02d", hh, mm, sec);
	SetColor(GRAY);
}
