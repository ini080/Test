#include "game.h"

CGAME::CGAME()
{
	pOmok[0] = &black;
	pOmok[1] = &white;
}

// ������ �����Ҷ� �ʿ��� �������� �ʱ�ȭ �ϰ�,
// ȭ�鿡 ǥ�����ش�. 
void CGAME::initGame()
{
	x = y = CENTER;
	t1 = t2 = clock();
	passTriggerOn = false;
	isComputer = false;
	passCount = 0;
	stoneState[0] = 0;
	stoneState[1] = 0;
	drawTime();
	curStone = WHITE_STONE;
	pDraw()->printData(x, y, BLACK_STONE);
	pDraw()->stonePoint(x, y);
	pDraw()->showMsg(curStone);
	pOmok[curStone]->initOmok();
	pOmok[curStone]->cursorView(x, y); 
}

// main�Լ����� �� �Լ��� ȣ���ϸ� ������ ���۵ȴ�. 
bool CGAME::playGame()
{
	int result;
	
	system("cls");
	initGame();
	pDraw()->computerStoneColor();
	while(true)
	{
		// 1�ʸ��� ȭ�鿡 �ð��� ǥ���Ѵ�. 
		if(clock() - t1 >= 1000) drawTime();
		
		result = checkKey();
		switch(result)
		{
			// Ű����κ��� ESCŰ�� ������ ������ �����Ѵ�. 
			case FINISH   : return false;
			// ������ �Ǿ����� ���ڸ� �˸���, ����Ұ��� �����. 
			case FIVEMOK  : return pDraw()->endMsg(curStone);
			// ������ �Ұ����� ���� �� ������ �˸���. 
			case OCCUPIED :
			case SAMSAM   :
			case SASA     :
			case SIXMOK   : 
			case NOTUNDO  : 
				pDraw()->errMsg(result); 
				pOmok[curStone]->setBoard(x, y); 
				break;
			//������ �ưų�, �Ѽ� ������ �� ���� �ٲ۴�.  
			case PASS     : if(!passTriggerOn) passTriggerOn = true;
							stoneState[curStone]++;
			case CHANGE   : changeStone(); break;
			default       : break;
		}
		pOmok[curStone]->cursorView(x, y);
		if(checkTie()) return pDraw()->endMsg(TIED);
		Sleep(20);
	}
}

// ��� ���� �� ���ʸ� �ٲ۴�. 
void CGAME::changeStone()
{
	// ��� ���̴� ���ؼ� 2�� ������ ��ȯ�� �ȴ�. 
	curStone = (curStone + 1) % 2;
	isComputer = !isComputer;
	// ���� �� ���ʸ� �˷��ش�. 
	pDraw()->showMsg(curStone);
	if(passTriggerOn) passCount++;
}

bool CGAME::checkTie()
{
	if(!passTriggerOn) return false;

	bool isTied = false;
	if(passCount == 2)
	{
		if(stoneState[0] == 1 && stoneState[1] == 1) isTied = true;
		passTriggerOn = false;
		passCount     = 0;
		stoneState[0] = 0;  
		stoneState[1] = 0;  
	}
	return isTied;
}

// 1 �ʸ��� ȭ�鿡 �ð��� ǥ���Ѵ�. 
void CGAME::drawTime()
{
	time_t sec = (clock() - t2) / 1000;
	pDraw()->drawTime(sec);
	t1 = clock();   
}


int CGAME::getKey()
{
	int ch = getch();
	if(ch == 0 || ch == 0xE0) ch = getch();

	return ch;
}

int CGAME::checkKey()
{
    int ch, dx, dy;;

    if(isComputer) return pOmok[curStone]->placement(x, y, curStone);
	else if(kbhit()) ch = getKey();
    else return 0;
    
    dx = dy = 0;
    switch(ch)
    {
    	case UP    : --dy; break;
		case DOWN  : ++dy; break;
    	case LEFT  : --dx; break;
		case RIGHT : ++dx; break;

        case DEL   : return PASS;
        case ESC   : return FINISH;
        case ' '   : return pOmok[curStone]->placement(x, y, curStone);
        case 'u'   : 
        case 'U'   : return pOmok[curStone]->undo(); 
        default    : break;
	}
    pOmok[curStone]->setBoard(x, y);
    y += dy;
    x += dx;
    pDraw()->printData(x, y, CURSOR);

    return 0;
}
