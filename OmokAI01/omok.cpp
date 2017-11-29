#include "omok.h"

int    COMOK::arrBoard[SIZE + 2][SIZE + 2] = {LINE,};
int    COMOK::lx = 0;
int    COMOK::ly = 0;
int    COMOK::x = CENTER;
int    COMOK::y = CENTER;
time_t COMOK::t1 = clock() - 500;
time_t COMOK::t2 = clock();
bool   COMOK::undoflag = 0;

COMOK::COMOK()
{
}

//�ٵ��� ���۵� �� �ʱ�ȭ 
void COMOK::initOmok()
{
	drawBoard();
	initBoard();
	undoflag = 0;
	t2 = clock();
	// 1�ʿ� �ѹ��� �׸��µ� ������ �α� ���ؼ�
	// ��������� 500msec���� Ŀ��ó�� ���ڰŸ��� �ȴ�. 
	t1 = clock() - 500;
	pDraw()->infoKey();
}

//Ŀ���� �̵��ϱ��� ���� �ٵ����� �����Ѵ�. 
void COMOK::setBoard(int x, int y)
{
	pDraw()->printData(x, y, arrBoard[y][x]);
	// Ŀ���� �̵����϶� Ŀ���� ������ �ʰ� �Ѵ�.
	// �������� �� ������ �ʾ� �����̵��� �ð� ����  
	t2 = clock() - 400;
	t1 = clock() - 900; 
}

// Ŀ���� ����� Ŀ��ó�� ���̰� �Ѵ�.
void COMOK::cursorView(int x, int y)
{
	// Ŀ���� 1�ʴ����� �׷��ش�. 
	if(clock() - t1 >= 1000)
	{
		pDraw()->printData(x, y, CURSOR);
		t1 = clock();
	}
	// Ŀ�� ��ġ�� �ٵ����� 1�� ������ �׷��ش�. 
	if(clock() - t2 >= 1000)
	{
		pDraw()->printData(x, y, arrBoard[y][x]);
		t2 = clock();
	}
}

// �Ѽ� ������ �����Լ� 
int COMOK::undo()
{
	if(!undoflag) return NOTUNDO;

	pDraw()->printData(lx, ly, LINE);
	arrBoard[ly][lx] = LINE;
	undoflag = false;
	
	return CHANGE;
} 

void COMOK::undoSet()
{
	lx = x;
	ly = y;
	undoflag = true;
}

// �ٵ����� �׸���. 
void COMOK::drawBoard()
{
	pDraw()->printNum();
	for(int i = 1; i <= SIZE; i++)
		for(int j = 1; j <= SIZE; j++)
			pDraw()->printData(j, i, LINE);
} 

// ���� ���̸� �迭�� ��鵹�� �����Ѵ�.
// ó�� �浹�� �߾ӿ� �Ѽ� ���� �����Ѵ�. 
void COMOK::initBoard()
{
	for(int i = 0; i < SIZE + 2; i++)
		for(int j = 0; j <= SIZE + 2; j++)
			arrBoard[i][j] = LINE;
	arrBoard[CENTER][CENTER] = BLACK_STONE;
} 

// �ٵϾ� ���� �ڸ��� üũ�Ѵ�. 
bool COMOK::isOccupy()
{
	return arrBoard[y][x] != LINE;
}

// �ٵϾ��� ���� �Ǹ� ���忡 �ٵϾ��� �׸���
// ���� �迭�� �����Ѵ�.  
void COMOK::saveBoard(int stone)
{
	pDraw()->printData(x, y, stone);
	pDraw()->stonePoint(x, y);
	arrBoard[y][x] = stone;
	undoSet();
}

// Game class���� �޾ƿ� ��ǥ�� �����Ѵ�. 
void COMOK::setXY(int ax, int ay)
{
	x = ax;
	y = ay;
}

// ������ �����Լ�
// ������ �������� üũ�ϰ�
// ������ �Ǹ� ������ �Ѵ�.
// �������� �������� �˻��Ͽ� ����� �����Ѵ�. 
int COMOK::placement(int ax, int ay, int nStone)
{
	setXY(ax, ay);
	if(isOccupy()) return OCCUPIED;
	
	int returnValue = CHANGE;
	orule.SetBoard(arrBoard);
	if(orule.IsFive(x, y, nStone) || orule.IsSix(x, y, nStone)) returnValue = FIVEMOK;
	saveBoard(nStone);
	
	return returnValue;
}

CBLACKSTONE::CBLACKSTONE()
{
}

int CBLACKSTONE::placement(int ax, int ay, int nStone)
{
	int returnValue = CHANGE;

	orule.SetBoard(arrBoard);
	ai.play(x, y, nStone, &orule);
	if(orule.IsFive(x, y, nStone) || orule.IsSix(x, y, nStone)) returnValue = FIVEMOK;
	saveBoard(nStone);
	
	return returnValue;
}
