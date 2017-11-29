#ifndef __DRAW_H__
#define __DRAW_H__

#include "console.h"

// �ٵ����� ũ�⸦ ��ũ�η� ���� ����
// �ٵ����� ũ��� 19 X 19������ 
// �������� ��� 15 X 15�� �Ѵ�. 
// x�� y�� ũ�Ⱑ ������ �ϳ��� ���� 
#define SIZE       15
#define CENTER     ((SIZE + 2) / 2)
#define FINISH    -1
#define TIED       2

// �ٵ����� ����� ���, ���� ���� ������ �Ѵ�.
// �ٵϵ��� ����� ���������� �Ѵ�.
enum {BLACK_STONE, WHITE_STONE, CURSOR, BLACKWIN, WHITEWIN, TIE, LINE, WALL}; 
enum {OCCUPIED = 10, SAMSAM, SASA, SIXMOK, NOTUNDO, FIVEMOK, CHANGE, PASS};
enum {HIDE, SHOW};

// ȭ���� �׷��� Draw class�� �����.
// �� class�� ���� ����Ͽ��� �� �����Ͽ� �� ����Ѵ�. 
class CDRAW
{
private :
	CDRAW();
	~CDRAW() {;}
	// ���Ӻ����� �»�� ��ġ 
	int nX, nY;
	
public :
	static CDRAW *getInstance();
	int    getLineNumber(int x, int y);
	int    GetMenu(char *cTitle);
	int    GetMenu();
	void   printData(int &x, int &y, int type);
	void   printNum();
	void   drawTime(time_t sec);
	void   showMsg(int msg);
	void   errMsg(int msg);
	bool   endMsg(int stone);
	void   CursorView(char show);
	void   gotoxy(int x, int y);
	void   SetColor(int color);
	void   SetColor(int color, int bgcolor);
	void   infoKey();
	void   Notify(int type); 
	void   computerStoneColor(int nColor);
	void   stonePoint(int x, int y);
	void   clearBuffer();
};

#endif

#define pDraw CDRAW::getInstance

