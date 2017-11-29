#ifndef __OMOK_H__
#define __OMOK_H__

#include "omokai.h"

class COMOK
{
protected :
	static int arrBoard[SIZE + 2][SIZE + 2];
	static int    x, y;
	// last ������ 
	static int    lx, ly;
	// �Ѽ� ������ ���� �÷��� 
	static bool   undoflag;
	// Ŀ���� �������� �����ϱ� ���� �ð�
	static time_t t1, t2; 
	COMOKRULE orule;
	COMOKAI    ai;
	
	bool    isOccupy();
	bool    checkSamSam();
	void    undoSet();
	void    drawBoard();
	void    saveBoard(int stone);
	void    setXY(int ax, int ay);

public :
	COMOK();
	virtual ~COMOK(){;}
	
	void setBoard(int x, int y);
	void cursorView(int x, int y);
	void initOmok();
	void initBoard();
	int  undo();

	virtual int placement(int ax, int ay, int stone); 
};

class CBLACKSTONE : public COMOK
{
private :
	
public :
	CBLACKSTONE();
	~CBLACKSTONE(){;}
	
	virtual int placement(int ax, int ay, int stone); 
};

#endif


