#ifndef __GAME_H__
#define __GAME_H__

#include "omok.h"

// Game������ �����ϴ� class 
class CGAME
{
private :
	// t1 : 1�ʸ��� ȭ�鿡 �ð��� ǥ�����ֱ� ���� ����
	// ���ʸ��� �ʱ�ȭ 
	// t2 : ������ ���� �ɶ� �ʱ�ȭ �Ͽ� 
	// ������ ����� ������ �����ϸ鼭 ���ؽð��� �ȴ�. 
	// t3 : �ð������� �ʿ��Ҷ� ����� ���� 
	time_t  t1, t2, t3;
	//���� ������ �� ��
	int     curStone;
	// omok�� x, y�� ���� ��ǥ�� �����Ѵ�. 
	int     x, y; 
	
	// ���ºθ� �˱� ���ؼ� ������ �̷��� ���� �ʿ��ϴ�.
	// ������ pass��  �ϸ� passTrigger�� On���°� �ȴ�.
	// �׷� passCounter�� ���۵ǰ�
	// �������� �鵹�� �浹�� �������� �������� 
	// �ƴϸ� ���� ���� �������� pass�� ������ 
	// �Ǵ��ϱ� ���Ͽ� stoneState�� �迭�� �����. 
	// ���º����� �˸��°� �ǿܷ� �����ϴ�. 
	bool    passTriggerOn; 
	bool    isComputer;
	int     passCount;
	int     stoneState[2];

	COMOK       white;
	CBLACKSTONE black;
	
	COMOK      *pOmok[2];
	
	bool        checkTie();  
	void        drawTime();
	void        initGame();
	void        changeStone(); 
	int         getKey();
	int         checkKey();
	
public :
	CGAME();
	~CGAME() {;}
	
	bool    playGame();
};

#endif
