#include "omokai.h"

COMOKAI::COMOKAI()
{
	for(int i = 0; i < SIZE + 2; i++ ) 
	{
		nBoard[i][0] = nBoard[i][SIZE + 1] = WALL;
		nBoard[0][i] = nBoard[SIZE + 1][i] = WALL;
	}
}

void COMOKAI::SetBoard(int (*arr)[SIZE + 2], COMOKRULE *pr)
{
	pRule = pr;
	
	for(int i = 1; i <= SIZE; i++)
		for(int j = 1; j <= SIZE; j++)
			nBoard[i][j] = arr[i][j];
	
	pRule->SetBoard(arr);
}

void COMOKAI::initWeight()
{
	for(int i = 1; i <= SIZE; i++)
	{
		for(int j = 0; j <= SIZE; j++)
		{
			nWeight[i][j] = 0;
		}
	}
}

bool COMOKAI::IsEmpty(int x, int y, int nStone)
{
	return nBoard[y][x] == LINE;
}

void COMOKAI::GetRect(Point &p1, Point &p2)
{
	p1.x = p1.y = SIZE;
	p2.x = p2.y = 0;
	for(int i = 1; i <= SIZE; i++)
	{
		for(int j = 0; j <= SIZE; j++)
		{
			if(nBoard[i][j] == 	BLACK_STONE || nBoard[i][j] == 	WHITE_STONE)
			{
				if(p1.x > j) p1.x = j;
				if(p2.x < j) p2.x = j;
				if(p1.y > i) p1.y = i;
				if(p2.y < i) p2.y = i;
			}
		}
	}
}

void COMOKAI::setRect()
{
	GetRect(l, r);
	
	l.x -= 2; if(l.x < 1   ) l.x = 1;
	l.y -= 2; if(l.y < 1   ) l.y = 1;
	r.x += 2; if(r.x > SIZE) r.x = SIZE;
	r.y += 2; if(r.y > SIZE) r.y = SIZE;
}

int COMOKAI::IsThree(int x, int y, int nStone, int nDir)
{
	int tx, ty;
	int cnt = 0;
	
	nDir % 2 ? nDir -= 1 : nDir;
	pRule->SetStone(x, y, nStone);
	for(int i = 0; i < 2; i++)
	{
		tx = x;
		ty = y;
		if(pRule->IsEmpty(tx, ty, nStone, nDir + i))
		{
			if(pRule->IsFour(tx, ty, nStone, nDir)) 
				if(pRule->IsOpenFour(tx, ty, nStone, nDir) == 0) cnt++;
		}
	}
	
	pRule->SetStone(x, y, LINE);
	return cnt;
}

int COMOKAI::IsOpenThree(int x, int y, int nStone, int nDir)
{
	int tx, ty;
	int cnt = 0;
	
	nDir % 2 ? nDir -= 1 : nDir;
	pRule->SetStone(x, y, nStone);
	for(int i = 0; i < 2; i++)
	{
		tx = x;
		ty = y;
		if(pRule->IsEmpty(tx, ty, nStone, nDir + i))
		{
			if(pRule->IsOpenFour(tx, ty, nStone, nDir) == 1) cnt++;
		}
	}
	
	pRule->SetStone(x, y, LINE);
	return cnt;
}

int COMOKAI::IsOpenTwo(int x, int y, int nStone, int nDir)
{
	int tx, ty;
	int cnt = 0;
	
	nDir % 2 ? nDir -= 1 : nDir;
	pRule->SetStone(x, y, nStone);
	for(int i = 0; i < 2; i++)
	{
		tx = x;
		ty = y;
		if(pRule->IsEmpty(tx, ty, nStone, nDir + i))
		{
			if(IsOpenThree(tx, ty, nStone, nDir) == 2) cnt++;
		}
	}
	
	pRule->SetStone(x, y, LINE);
	return cnt;
}

int COMOKAI::IsTwo(int x, int y, int nStone, int nDir)
{
	int tx, ty;
	int cnt = 0;
	
	nDir % 2 ? nDir -= 1 : nDir;
	pRule->SetStone(x, y, nStone);
	for(int i = 0; i < 2; i++)
	{
		tx = x;
		ty = y;
		if(pRule->IsEmpty(tx, ty, nStone, nDir + i))
		{
			if(IsThree(tx, ty, nStone, nDir) == 1) cnt++;
		}
	}
	
	pRule->SetStone(x, y, LINE);
	return cnt;
}

int COMOKAI::IsFour(int x, int y, int nStone, int nDir)
{
	int tx, ty;
	int cnt = 0;
	
	nDir % 2 ? nDir -= 1 : nDir;
	for(int i = 0; i < 2; i++)
	{
		if(pRule->IsFour(x, y, nStone, nDir + i))
			if(pRule->IsOpenFour(x, y, nStone, nDir) == 0) cnt++;
	}
	return cnt;
}

bool COMOKAI::IsFourThree(int x, int y, int nStone)
{
	int fCnt = 0;
	int tCnt = 0;
	
	for(int i = 0; i < 8; i += 2)
	{
		if(pRule->IsFour(x, y, nStone, i)) fCnt++;
		else if(tCnt = IsOpenThree(x, y, nStone, i));
		
		if(fCnt && tCnt) return true;
	}
	
	return false;
}
 
bool COMOKAI::IsDoubleThree(int x, int y, int nStone)
{
	int cnt = 0;
	
	for(int i = 0; i < 8; i += 2)
	{
		if(pRule->IsOpenFour(x, y, nStone, i) == 1) cnt++;
		
		if(cnt >= 2) return true;
	}
	
	return false;
}

bool COMOKAI::IsDoubleFour(int x, int y, int nStone)
{
	for(int i = 0; i < 8; i += 2)
	{
		if(pRule->IsDoubleFour(x, y, nStone)) return true;
	}
	return false;
}

int COMOKAI::IsOpenFour(int x, int y, int nStone, int nDir)
{
	int cnt = 0;
	for(int i = 0; i < 2; i++)
	{
		if(pRule->IsOpenFour(x, y, nStone, nDir + 1) == 1) cnt++;
	}
	return cnt;
}

int COMOKAI::yourOpenFour(int x, int y, int nStone, int nDir)
{
	int cnt = 0;
	for(int i = 0; i < 2; i++)
	{
		if(IsOpenFour(x, y, nStone, nDir)) cnt++;
	}
	return cnt;
}

int COMOKAI::OpenFour(int x, int y, int nStone, int nDir)
{
	int tx, ty;
	
	nDir % 2 ? nDir -= 1 : nDir;
	pRule->SetStone(x, y, nStone);
	for(int i = 0; i < 2; i++)
	{
		tx = x;
		ty = y;
		if(pRule->IsEmpty(tx, ty, nStone, nDir + i))
		{
			if(pRule->IsFive(tx, ty, nStone, nDir + 1) || pRule->IsSix(tx, ty, nStone)) return 1;
		}
	}
	pRule->SetStone(x, y, LINE);
	
	return 0;
}

bool COMOKAI::IsFive(int x, int y, int nStone)
{
	for(int i = 0; i < 8; i += 2)
	{
		if(pRule->IsFive(x, y, nStone)) return true;
	}
	return false;
}

bool COMOKAI::IsSix(int x, int y, int nStone)
{
	for(int i = 0; i < 8; i += 2)
	{
		if(pRule->IsSix(x, y, nStone)) return true;
	}
	return false;
}

void COMOKAI::fillWeight(int myStone, bool isRenju) 
{
	int cnt;
	int yourStone = (myStone + 1) % 2;
	
	// �Ʒ� �Լ��� ������� ������ ���Ͽ� �ô�. 
	// ������ ���� ���� ������ �ϴ� �˰����̶�
	// �� �� ���� ���� ���ϰ� �ּ��� ���� �ѻ��̴�. 
	int arrWeight[] = {2, 5, 10, 30, 35, 300};
	int (COMOKAI::*fp[6])(int, int, int, int) = {IsTwo, IsOpenTwo, IsThree, IsOpenThree, IsFour, yourOpenFour};
	
	// �����Ͽ� ��ü������ ������ �ʿ��ؼ� 
	// ���� ������ �Ǹ� �׶� ������ ÷���ϰڽ�.
	// OpenFour�� ��� ����� ���� ���� ��� ���� ���� ���
	// ������ �켱���� �ַ��� ������ �޸� �غý�.
	
	// ����4�� �ִµ��� ����� 43�ڸ��� ������ �װ� ���� ���Ƽ� 
	// ���ַ꿡�� ���� 6���� �� �� �ֱ� ������ 6��� �� �ִ� 
	// OpenFour�� ���� ���Ͽ� �����ϰ� �����غ��� ������ ����
	// ���� ���� �ý��۰� ���������� �պ��� �� �� 
	isOpenFour = false;
	for(int i = l.y; i <= r.y; i++)
	{
		for(int j = l.x; j <= r.x; j++)
		{
			for(int f = 0; f < 6; f++)
			{
				if(!IsEmpty(j, i, myStone)) continue;
				cnt = 0;
				arrWeight[5] = 300;
				for(int n = 0; n < 8; n += 2)
				{
					if(f ==5 && isRenju) cnt = IsOpenFour(j, i, myStone, n);
					else cnt = IsOpenFour(j, i, myStone, n);
					cnt = (this->*fp[f])(j, i, myStone, n);
					if(f == 5) 
					{
						if(cnt) isOpenFour = true;
						else arrWeight[5] = 100;
					}
					cnt += (this->*fp[f])(j, i, yourStone, n);
					nWeight[i][j] += cnt * arrWeight[f];
				}
			}
		}
	}
}

bool COMOKAI::findPutPoint(int &x, int &y, int nStone, bool (COMOKAI::*fp)(int, int, int))
{
	for(int i = l.y; i <= r.y; i++)
	{
		for(int j = l.x; j <= r.x; j++)
		{
			if(!IsEmpty(j, i, nStone)) continue;
			if((this->*fp)(j, i, nStone))
			{
				x = j;
				y = i;
				return true;
			}
		}
	}
	return false;
}

void COMOKAI::findPutOnPoint(int &x, int &y, int nStone)
{
	int max = -1;
	for(int i = l.y; i <= r.y; i++)
	{
		for(int j = l.x; j <= r.x; j++)
		{
			if(!IsEmpty(j, i, nStone)) continue;
			if(max < nWeight[i][j])
			{
				x = j;
				y = i;
				max = nWeight[i][j];
			}
		}
	}
}

void COMOKAI::play(int &x, int &y, int myStone)
{
	int yourStone = (myStone + 1) % 2;

	initWeight();
	GetRect(l, r);
	setRect();
	fillWeight(myStone, false);
	for(int i = l.y; i <= r.y; i++)
	{
		for(int j = l.x; j <= r.x; j++)
		{
			if(!IsEmpty(j, i, myStone)) continue;
			if(findPutPoint(j, i, myStone, IsFive))  {x = j; y = i; return;}
			if(findPutPoint(j, i, myStone, IsSix))  {x = j; y = i; return;}
			if(findPutPoint(j, i, yourStone, IsFive))  {x = j; y = i; return;}
			if(findPutPoint(j, i, yourStone, IsSix))  {x = j; y = i; return;}
			if(findPutPoint(j, i, myStone, IsFourThree))  {x = j; y = i; return;}
			if(findPutPoint(j, i, myStone, IsDoubleFour))  {x = j; y = i; return;}
			//if(isOpenFour) break;
			if(findPutPoint(j, i, yourStone, IsFourThree)) {x = j; y = i; return;}
			if(findPutPoint(j, i, yourStone, IsDoubleFour)) {x = j; y = i; return;}
		}
	}
	
	findPutOnPoint(x, y, myStone);
}

void CNORMALAI::findPutOnPoint(int &x, int &y, int nStone)
{
	int max = -1;
	for(int i = l.y; i <= r.y; i++)
	{
		for(int j = l.x; j <= r.x; j++)
		{
			if(!IsEmpty(j, i, nStone)) continue;
			if(pRule->IsDoubleThree(j, i, nStone)) continue;
			if(max < nWeight[i][j])
			{
				x = j;
				y = i;
				max = nWeight[i][j];
			}
		}
	}
}

void CNORMALAI::play(int &x, int &y, int myStone)
{
	int yourStone = (myStone + 1) % 2;
	GetRect(l, r);
	setRect();
	initWeight();
	fillWeight(myStone, false);
	for(int i = l.y; i <= r.y; i++)
	{
		for(int j = l.x; j <= r.x; j++)
		{
			if(!IsEmpty(j, i, myStone)) continue;
			if(findPutPoint(j, i, myStone, IsFive))  {x = j; y = i; return;}
			if(findPutPoint(j, i, myStone, IsSix))  {x = j; y = i; return;}
			if(findPutPoint(j, i, yourStone, IsFive))  {x = j; y = i; return;}
			if(findPutPoint(j, i, yourStone, IsSix))  {x = j; y = i; return;}
			if(findPutPoint(j, i, myStone, IsFourThree))  {x = j; y = i; return;}
			if(findPutPoint(j, i, myStone, IsDoubleFour))  {x = j; y = i; return;}
			//if(isOpenFour) break;
			if(findPutPoint(j, i, yourStone, IsFourThree))  {x = j; y = i; return;}
			if(findPutPoint(j, i, yourStone, IsDoubleFour)) {x = j; y = i; return;}
		}
	}
	
	findPutOnPoint(x, y, myStone);
}

void CRENJUBLACK::findPutOnPoint(int &x, int &y, int nStone)
{
	int max = -1;
	for(int i = l.y; i <= r.y; i++)
	{
		for(int j = l.x; j <= r.x; j++)
		{
			if(!IsEmpty(j, i, nStone)) continue;
			if(pRule->IsForbidden(j, i, nStone)) continue;
			if(max < nWeight[i][j])
			{
				x = j;
				y = i;
				max = nWeight[i][j];
			}
		}
	}
}

void CRENJUBLACK::play(int &x, int &y, int myStone)
{
	int yourStone = (myStone + 1) % 2;

	GetRect(l, r);
	setRect();
	initWeight();
	fillWeight(myStone, true);
	for(int i = l.y; i <= r.y; i++)
	{
		for(int j = l.x; j <= r.x; j++)
		{
			if(!IsEmpty(j, i, myStone)) continue;
			if(findPutPoint(j, i, myStone, IsFive))  {x = j; y = i; return;}
			if(findPutPoint(j, i, yourStone, IsFive))  {x = j; y = i; return;}
			if(findPutPoint(j, i, yourStone, IsSix))  {x = j; y = i; return;}
			if(findPutPoint(j, i, myStone, IsFourThree))  {x = j; y = i; return;}
			//if(isOpenFour) break;
			if(findPutPoint(j, i, yourStone, IsFourThree)) {x = j; y = i; return;}
			if(findPutPoint(j, i, yourStone, IsDoubleFour)) {x = j; y = i; return;}
		}
	}
	findPutOnPoint(x, y, myStone);
	
}
