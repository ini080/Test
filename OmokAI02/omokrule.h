#ifndef __OMOKRULE_H__
#define __OMOKRULE_H__

#include "draw.h"
#include <iostream>


// openSource�� ����ϰ� �����  �۸�� ������ 
// ���� ������� ����� �˰����� �ռ��Ͽ�
// ���Ӱ� Omokrule class�� ����� ���� ���α׷��� �����غ���. 

class COMOKRULE
{
protected :
	int    nBoard[SIZE+2][SIZE+2];

public :
	COMOKRULE();
	virtual ~COMOKRULE() {;}

	void SetBoard(int (*arr)[SIZE + 2]);
	bool IsFive(int x, int y, int nStone);
	bool IsSix(int x, int y, int nStone);
	bool IsFour(int x, int y, int nStone, int nDir);
	int  IsOpenFour(int x, int y, int nStone, int nDir);
	bool IsDoubleFour(int x, int y, int nStone);
	bool IsDoubleThree(int x, int y, int nStone);

	void SetStone(int x, int y, int nStone);
	void GetDirTable(int &x, int &y, int i);
	bool IsFive(int x, int y, int nStone, int nDir);
	bool IsEmpty(int &x, int &y, int nStone, int i);
	bool IsForbidden(int x, int y, int nStone);
	int  GetStoneCount(int x, int y, int nStone, int nDir);
 	virtual bool IsOpenThree(int x, int y, int nStone, int nDir	);
};

class CNORMALRULE : public COMOKRULE
{
public :
	virtual bool IsOpenThree(int x, int y, int nStone, int nDir	);
};

#endif
