#include "omok.h"

int      COMOK::arrBoard[SIZE + 2][SIZE + 2] = {LINE,};
int      COMOK::lx = 0;
int      COMOK::ly = 0;
int      COMOK::x = CENTER;
int      COMOK::y = CENTER;
time_t   COMOK::t1 = clock() - 500;
time_t   COMOK::t2 = clock();
UndoInfo COMOK::uInfo[SIZE * SIZE] = {0};
UndoInfo COMOK::rInfo[SIZE * SIZE] = {0};
int      COMOK::uTop = -1;
int      COMOK::rTop = -1;

COMOK::COMOK()
{
	x = y = CENTER;
	undoSet(BLACK_STONE);
}

//�ٵ��� ���۵� �� �ʱ�ȭ 
void COMOK::initOmok(int nStone)
{
	drawBoard();
	initBoard(nStone);
	t2 = clock();
	// 1�ʿ� �ѹ��� �׸��µ� ������ �α� ���ؼ�
	// ��������� 500msec���� Ŀ��ó�� ���ڰŸ��� �ȴ�. 
	t1 = clock() - 500;
	pDraw()->infoKey();
	uTop = rTop = -1;
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

int COMOK::undo()
{
	if(uTop < 0) return false;

	rInfo[++rTop].x = lx = uInfo[uTop].x;
	rInfo[rTop].y = ly = uInfo[uTop].y;
	rInfo[rTop].nStone = uInfo[uTop--].nStone;
	
	pDraw()->printData(lx, ly, LINE);
	arrBoard[ly][lx] = LINE;

	return CHANGE;
} 

int COMOK::redo()
{
	if(rTop < 0) return false;
	
	uInfo[++uTop].x = lx = rInfo[rTop].x;
	uInfo[uTop].y = ly = rInfo[rTop].y;
	uInfo[uTop].nStone = rInfo[rTop--].nStone;

	pDraw()->printData(lx, ly, uInfo[uTop].nStone);
	arrBoard[ly][lx] = uInfo[uTop].nStone;
	
	return CHANGE;
} 

void COMOK::undoSet(int nStone)
{
	uInfo[++uTop].x    = x;
	uInfo[uTop].y      = y;
	uInfo[uTop].nStone = nStone;
	rTop = -1;
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
void COMOK::initBoard(int nStone)
{
	for(int i = 0; i < SIZE + 2; i++)
		for(int j = 0; j <= SIZE + 2; j++)
			arrBoard[i][j] = LINE;
	arrBoard[CENTER][CENTER] = nStone;
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
	undoSet(stone);
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

	setXY(ax, ay);
	if(isOccupy()) return OCCUPIED;
	
	orule.SetBoard(arrBoard);
	if(orule.IsFive(x, y, nStone)) 
	{
		saveBoard(nStone);
		return FIVEMOK;
	}
	else if(orule.IsSix(x, y, nStone)) return SIXMOK;
	else if(orule.IsDoubleFour(x, y, nStone))  return SASA;
	else if(orule.IsDoubleThree(x, y, nStone)) return SAMSAM;

	saveBoard(nStone);
	return CHANGE;
}

CNORMAL::CNORMAL()
{
}

int CNORMAL::placement(int ax, int ay, int nStone)
{
	setXY(ax, ay);
	if(isOccupy()) return OCCUPIED;
	
	nrule.SetBoard(arrBoard);
	if(nrule.IsFive(x, y, nStone) || nrule.IsSix(x, y, nStone)) 
	{
		saveBoard(nStone);
		return FIVEMOK;
	}
	else if(nrule.IsDoubleThree(x, y, nStone)) return SAMSAM;

	saveBoard(nStone);
	return CHANGE;
}

int CGOMOKUAI::placement(int ax, int ay, int nStone)
{
	int ret = CHANGE;
	
	ai.SetBoard(arrBoard, &orule);
	ai.play(x, y, nStone);
	if(orule.IsFive(x, y, nStone) || orule.IsSix(x, y, nStone)) ret = FIVEMOK;

	saveBoard(nStone);
	return ret;
}

int CJENERALAI::placement(int ax, int ay, int nStone)
{
	int ret = CHANGE;
	
	ai.SetBoard(arrBoard, &nrule);
	ai.play(x, y, nStone);
	if(nrule.IsFive(x, y, nStone) || nrule.IsSix(x, y, nStone)) ret = FIVEMOK;

	saveBoard(nStone);
	return ret;
}

int CRENJUAI::placement(int ax, int ay, int nStone)
{
	int ret = CHANGE;
	
	ai.SetBoard(arrBoard, &orule);
	ai.play(x, y, nStone);
	if(orule.IsFive(x, y, nStone)) ret = FIVEMOK;

	saveBoard(nStone);
	return ret;
}
