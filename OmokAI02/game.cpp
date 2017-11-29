#include "game.h"

CGAME::CGAME()
{
}

// ������ �����Ҷ� �ʿ��� �������� �ʱ�ȭ �ϰ�,
// ȭ�鿡 ǥ�����ش�. 
void CGAME::initGame(int mode)
{
	x = y = CENTER;
	t1 = t2 = clock();
	passTriggerOn = false;
	passCount = 0;
	stoneState[0] = 0;
	stoneState[1] = 0;
	drawTime();
	if(mode == 2) isComputer = true;
	else isComputer = false;
	if(mode == 4) curStone = BLACK_STONE;
	else curStone = WHITE_STONE;
	if(mode == 5) pDraw()->printData(x, y, WHITE_STONE);
	else pDraw()->printData(x, y, BLACK_STONE);
	if(mode == 1) pDraw()->computerStoneColor(BLACK);
	else if(mode == 2) pDraw()->computerStoneColor(WHITE);
	pDraw()->stonePoint(x, y);
	pDraw()->showMsg(curStone);
	if(mode == 5) pOmok[curStone]->initOmok(WHITE_STONE);
	else pOmok[curStone]->initOmok(BLACK_STONE);
	pOmok[curStone]->cursorView(x, y); 
	pDraw()->clearBuffer();
}

// main�Լ����� �� �Լ��� ȣ���ϸ� ������ ���۵ȴ�. 
bool CGAME::playGame(int type, int mode)
{
	int result;
	system("cls");
	
	pOmok[0] = factory.GetInstance(type * 10 + 0, mode);
	pOmok[1] = factory.GetInstance(type * 10 + 1, mode);
	pDraw()->Notify(type);
	initGame(mode);
	while(true)
	{
		// 1�ʸ��� ȭ�鿡 �ð��� ǥ���Ѵ�. 
		if(clock() - t1 >= 1000) drawTime();
		
		result = checkKey(mode);
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
							if(mode == 1 || mode == 2) stoneState[(curStone + 1) % 2]++;
			case CHANGE   : changeStone(mode); break;
			default       : break;
		}
		pOmok[curStone]->cursorView(x, y);
		if(checkTie()) return pDraw()->endMsg(TIED);
		Sleep(20);
	}
}

// ��� ���� �� ���ʸ� �ٲ۴�. 
void CGAME::changeStone(int mode)
{
	// ��� ���̴� ���ؼ� 2�� ������ ��ȯ�� �ȴ�. 
	if(mode == 4) curStone = BLACK_STONE;
	else if(mode == 5) curStone = WHITE_STONE;
	else curStone = (curStone + 1) % 2;
	
	//��ǻ�Ϳ� �Ѷ� ���ʸ� �˸��� ���� ������ ���� ���� 
	if(mode == 1 || mode == 2) isComputer = !isComputer;
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

int CGAME::checkKey(int mode)
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
        case 'r'   : 
        case 'R'   :
        	if(mode == 1 || mode == 2)
        	{
	        	pOmok[curStone]->redo(); 
	        	pOmok[(curStone + 1) % 2]->redo(); 
			}
			else return pOmok[curStone]->redo(); 
        case 'u'   : 
        case 'U'   : 
        	if(mode == 1 || mode == 2)
        	{
	        	pOmok[curStone]->undo(); 
	        	pOmok[(curStone + 1) % 2]->undo(); 
			}
			else return pOmok[curStone]->undo(); 
        default    : break;
	}
    pOmok[curStone]->setBoard(x, y);
    y += dy;
    x += dx;
    pDraw()->printData(x, y, CURSOR);

    return 0;
}
