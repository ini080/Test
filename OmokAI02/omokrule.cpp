#include "omokrule.h"

COMOKRULE::COMOKRULE()
{
	for(int i = 0; i < SIZE + 2; i++ ) 
	{
		//�ٵ��� ���� �迭�� ���� LINE�̳� STONE�� �ƴ� 
		//�ٸ� ���ڷ� ���������ν� ������� ��Ÿ����. 
		nBoard[i][0] = nBoard[i][SIZE + 1] = WALL;
		nBoard[0][i] = nBoard[SIZE + 1][i] = WALL;
	}
}

// �����ϱ� ���� �ٵ��� ���¸� �����Ѵ�. 
void COMOKRULE::SetBoard(int (*arr)[SIZE + 2])
{
	for(int i = 1; i <= SIZE; i++)
		for(int j = 1; j <= SIZE; j++)
			nBoard[i][j] = arr[i][j];
}

// x, y��ǥ�� ���� ���ų� ����.
// ���ٴ� ���� �װ���  Line�� �ٽ� �׷��ִ� �� �ǹ��Ѵ�. 
void COMOKRULE::SetStone(int x, int y, int nStone)
{
		nBoard[y][x] = nStone;
}

// 8���� ���ڴ� 8������ ��Ÿ����.
// �迭�� ������� ��, ��, ��, ��, ����, ����, ����, �ϵ�
// (��, ��) (�� ��) (����, ����) (����, �ϵ�)�� �ѽ��̵Ǿ�
// ���� ���� �� �밢���� ������ dx, dy�� ǥ���� Table 
void COMOKRULE::GetDirTable(int &x, int &y, int nDir)
{
	//          ��  ��  ��  ��  �ϼ� ���� ���� �ϵ� 
	int dx[] = {-1,  1,  0,  0, -1,   1,  -1,   1};
	int dy[] = { 0,  0, -1,  1, -1,   1,   1,  -1};
	
	x = dx[nDir];
	y = dy[nDir];
}

// �־��� �������� ��ǥ�� �Ű� ����� ã�� 
// �װ��� �·Ḧ �˷��ش�. 
bool COMOKRULE::IsEmpty(int &x, int &y, int nStone, int nDir)
{
	int dx, dy;
	
	// ���� Table���� dx, dy���� �����´�.
	// ���� nDir�� 0�̶�� dx = -1, dy = 0�̴�. 
	GetDirTable(dx, dy, nDir);
	// x�� 1 y�� 0�̴ϱ� x += dx, y += dy �� ���Ŀ� ���ؼ� 
	// x�� ���� �۾��� �������� ����, y�� ������ ������ ���ڸ�
	// �׷��� ���η� ���ʿ� nStone�� �ƴ� ������ ���߰� �ȴ�. 
	for(;nBoard[y][x] == nStone; x += dx, y += dy);
	
	// nStone�� �ƴ϶� �ؼ� ���� LINE�̶� �� �� ����.
	// �ٸ� ���̰ų� �ٵ����� ��� �� �ϼ��� ������
	// �װ��� LINE�� ���� ���� ��ȯ�Ѵ�. 
	return nBoard[y][x] == LINE;
}

// �־��� ��ǥ�� ������ �����ϰ�,
// �־��� ����(nDir)���� 
// ���ӵ� ���� ����� ��� ��ȯ�Ѵ�. 
int COMOKRULE::GetStoneCount(int x, int y, int nStone, int nDir)
{
	int dx, dy; 
	int tx = x;
	int ty = y;
	int cnt = 0;
	
	// ������ ���� Line�� �ƴϸ� ������ �� ������
	// 0�� return�Ѵ�. 
	if(nBoard[y][x] != LINE) return 0;
	SetStone(x, y, nStone);
	
	// ���� Table���� dx, dy���� ������ 
	GetDirTable(dx, dy, nDir);
	//������ ���������� nDir�������� ���� ���� ������ ����. 
	for(;nBoard[y][x] == nStone; x += dx, y += dy) cnt++;
	
	// ���� Table�� �ϳ��� �Ǿ��ְ�, 
	// ������ �׻� ���� �Ǵ� �ϳ����� �Ǿ� �־� 
	// nDir�� Ȧ���� ���� -1�� ������ �˻��Ͽ��� �Ѵ�.
	// �׷��� �ʰ� ���� �����̶�� ������ +1�Ѵٸ�
	// ���� nDir�� ��(1)�̶�� ��(0)���� �˻��ؾ� �Ǵµ�
	// +1�ؼ� 2�� �Ǹ� ��(0)�� �ƴ� ��(2)�� �˻��ϰ� �ȴ�. 
	// �̸� �����ϱ� ���� 3�� �����ڸ� �̿���
	// ���ǿ� �´� ������ �μ��� �ѱ�� �Ͽ���. 
	GetDirTable(dx, dy, nDir % 2 ? nDir - 1 : nDir + 1);
	
	// x, y���� ������ ������ �ϴ��� ó�� ��ǥ�� ����� ������
	// ó�� ��ǥ���� ���� �������� ��ĭ �Űܼ� �װ���������
	// ���� ������ ����. 
	// ������ �� ���Ҵ� ���� �����⿡ �ߺ��� ���ϱ� ���ؼ���. 
	x = tx + dx;
	y = ty + dy;
	for(; nBoard[y][x] == nStone; x += dx, y += dy) cnt++;
	
	// ���� ������ �� �������� ���� ����. 
	SetStone(tx, ty, LINE);
	return cnt;
}

// ������ �Ͽ����� �������� �˻��Ѵ�. 
bool COMOKRULE::IsFive(int x, int y, int nStone)
{
	// ���� Table�� ���� 8�̴ϱ� 8���� �˻��ϰ�
	// �������� +=2�ΰ�
	// �Ʒ� GetStoneCount()�Լ� �ȿ��� �糡�� �˻��ϱ� �����̴�. 
	for(int i = 0; i < 8; i += 2)
	{
		if(GetStoneCount(x, y, nStone, i) == 5) return true;
	}
	return false;
}

// ���� ���� ���������� �˻�������,
// nDir���⿡ ���ؼ��� �˻��Ѵ�.
// �̴� Four�� OpenFour�� �Ǵ��� �˾ƺ��� ���Ͽ� 
// ����� ���� �ϳ��� ���ƺ��鼭
// ������ �Ǵ��� �˻��ϱ� ���ؼ���. 
bool COMOKRULE::IsFive(int x, int y, int nStone, int nDir)
{
	if(GetStoneCount(x, y, nStone, nDir) == 5) return true;
	return false;
}

// ������ �˻��ϴ� �Ͱ� ���� 6�� �̻����� �˻��Ѵ�. 
bool COMOKRULE::IsSix(int x, int y, int nStone)
{
	for(int i = 0; i < 8; i += 2)
	{
		if(GetStoneCount(x, y, nStone, i) >= 6) return true;
	}
	return false;
}

// ������ ������ 4������ �˻��Ѵ�. 
bool COMOKRULE::IsFour(int x, int y, int nStone, int nDir)
{
	// ������ ��ǥ x, y�� ����ϱ� ���� ���� 
	int tx, ty;
	
	// �� ���⿡ ���Ͽ� �糡�� �˻��ϴµ�
	// �ѽ��� ��ǥ�� ù��°���� �˻��ϱ� ���Ͽ� 
	nDir % 2 ? nDir -= 1 : nDir;
	// ��ǥ�� ������ �Ѵ� 
	SetStone(x, y, nStone);
	// ���� �糡�� �˻� 
	for(int i = 0; i < 2; i++)
	{
		// ������ ��ǥ�� �߽����� �־��� ����(nDir)�� ���Ͽ�
		// �������� �̵��ϸ鼭 ����� ã�� �װ��� ��ǥ�� ���;� �Ǳ⿡
		// ������ ��ǥ�� ������ �ȴ�. ���� ������ �˻��ϱ����Ͽ�
		// ����� ������ �ʿ��ϰ�, �Ź� �Ʒ��� ���� 
		// ������ ��ǥ�� �޾Ƽ� �˻簡 ����Ǿ�� �Ѵ�. 
		tx = x;
		ty = y;
		// ����� ������ �� ��ǥ�� �޾ƿ´�. 
		if(IsEmpty(tx, ty, nStone, nDir + i))
		{
			// �� ������� ������ �Ǵ��� �˻��Ѵ�. 
			if(IsFive(tx, ty, nStone, nDir + i))
			{
				// ������ �Ǿ��ٸ� 4�̱� ������ 
				// ���� ���� ���� �����Ѵ�. 
				SetStone(x, y, LINE);
				return true;
			}
		}
	}
	
	// �˻縦 �غ����� 4�� �ƴ϶� �ص� ���� ����. 
	SetStone(x, y, LINE);
	return false;
}

// ���� �������� 4���̰� ���� ���� �������� ������ �Ǹ� 
// ����4�� �ȴ�. 
int COMOKRULE::IsOpenFour(int x, int y, int nStone, int nDir)
{
	int tx, ty;
	// ����4�� �ɶ��� ���ʿ� ���� �������� 
	// ���� ��� ������ �Ǿ�� �Ǳ⶧����
	// �ΰ��� 4�� �Ǵ��� �˻縦 ���� ���� 
	int sum = 0;
	
	nDir % 2 ? nDir -= 1 : nDir;
	SetStone(x, y, nStone);
	for(int i = 0; i < 2; i++)
	{
		tx = x;
		ty = y;
		// ��������� Four()�Լ��� ����. 
		if(IsEmpty(tx, ty, nStone, nDir + i))
		{
			if(IsFive(tx, ty, nStone, nDir + i)) sum++;
		}
	}
	SetStone(x, y, LINE);
	
	// �������� ��ΰ� ������ �Ǿ������� ����4�̴�. 
	if(sum == 2) 
	{
		// ����4�� ���� Ư���ϰ� ���ٿ� 44�� �ɼ� �ִ�.
		// 1234567   12345678
		// 0 0 0 0   00  0 00
		// ���� ���� ��Ȳ���� 4��ġ�� ���� ���̸�
		// ������ ��� 4�� �Ǿ� ���ٿ��� 44�� �߻��Ѵ�.
		// ������ 0000 �̿Ͱ��� �����϶��� 4�� �ϳ��̱� ������
		// �˻縦 �Ͽ� ������ ��Ȯ�ϰ� �Ѵ�. 
		if(GetStoneCount(x, y, nStone, nDir) == 4) sum = 1;
	}
	// sum�� 2�� �ƴϸ� ����4�� �ƴϹǷ� 0 
	else sum = 0;
	
	return sum;
}

bool COMOKRULE::IsDoubleFour(int x, int y, int nStone)
{
	int cnt = 0;
	
	//��ǥ�� �߽����� ������ �ٿ����Ͽ� 4�� �˻��Ѵ�. 
	for(int i = 0; i < 8; i += 2)
	{
		// OpenFour()������ �� �ٿ� 44�� ���� �� ������ �˻��ϰ� 
		if(IsOpenFour(x, y, nStone, i) == 2) return true;
		// ����4�� 4�̴� 4�� �˻��Ͽ� 2�� �̻��̸� 44�̴�. 
		else if(IsFour(x, y, nStone, i)) cnt++;
		
		if(cnt >= 2) return true;
	}
	
	return false;
}
 
bool COMOKRULE::IsOpenThree(int x, int y, int nStone, int nDir)
{
	int tx, ty;
	
	nDir % 2 ? nDir -= 1 : nDir;
	SetStone(x, y, nStone);
	for(int i = 0; i < 2; i++)
	{
		tx = x;
		ty = y;
		if(IsEmpty(tx, ty, nStone, nDir + i))
		{
			// 33�� ���� �ϳ� �� ������ �� �ݵ�� ����4�̾�� �ǰ�, 
			// �� �� ���� �ڸ��� 44, 6��, �Ǵٸ� 33 
			// �� �ݼ��ڸ��� �ƴϾ�� �ȴ�.
			if((IsOpenFour(tx, ty, nStone, nDir) == 1) && (!IsForbidden(tx, ty, nStone))) 
			{
				// �� ������ �����ϴ� �ڸ��̸� 3�̹Ƿ� ���� �����ϰ� ���� �����Ѵ�. 
				SetStone(x, y, LINE);
				return true;
			}
		}
	}
	
	SetStone(x, y, LINE);
	return false;
}

// 33�� �˻��Ѵ�. 
bool COMOKRULE::IsDoubleThree(int x, int y, int nStone)
{
	int cnt = 0;
	
	for(int i = 0; i < 8; i += 2)
	{
		if(IsOpenThree(x, y, nStone, i)) cnt++;
		if(cnt >= 2) return true;
	}
	
	return false;
}

// �ݼ��ڸ��� �˻��Ѵ�. 
bool COMOKRULE::IsForbidden(int x, int y, int nStone)
{
	if(IsDoubleFour(x, y, nStone)) return true;
	else if(IsDoubleThree(x, y, nStone)) return true;
	else if(IsSix(x, y, nStone)) return true;
	else return false;
}

bool CNORMALRULE::IsOpenThree(int x, int y, int nStone, int nDir)
{
	int tx, ty;
	
	nDir % 2 ? nDir -= 1 : nDir;
	SetStone(x, y, nStone);
	for(int i = 0; i < 2; i++)
	{
		tx = x;
		ty = y;
		if(IsEmpty(tx, ty, nStone, nDir + i))
		{
			// 33�� ���� �ϳ� �� ������ �� �ݵ�� ����4�̾�� �ǰ�, 
			// �� �� ���� �ڸ��� 44, 6��, �Ǵٸ� 33 
			// �� �ݼ��ڸ��� �ƴϾ�� �ȴ�.
			if((IsOpenFour(tx, ty, nStone, nDir) == 1) && (!IsDoubleThree(tx, ty, nStone))) 
			{
				// �� ������ �����ϴ� �ڸ��̸� 3�̹Ƿ� ���� �����ϰ� ���� �����Ѵ�. 
				SetStone(x, y, LINE);
				return true;
			}
		}
	}
	
	SetStone(x, y, LINE);
	return false;
}
