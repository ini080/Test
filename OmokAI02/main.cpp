// ���� ���α׷��� ���� 1016�� 12�� 2�� 08�� 45�� 
// ó�� ��ǥ�� ȭ�鿡 �ٵ����� �׸���
// ���ϴ� ��ġ�� �ٵϾ��� �׷� �ִ´�.
// ������ ����Ǵ� ���� ���� ���θ� �˻��Ѵ�.
// ��� ���� �����ϰ� 
// 5�� �������� ���� ���̸� �¸��� �����Ѵ�. 
// ���а� ������ ������ �����ϰ� 
// "��"�� �Ǵ� "��"�� �¸� �Ͽ��ٰ� �˸���.
// �ѹ��� �� ������ �����.

// ������ �� �Ǽ��� �� ������ 
// �ѹ��� �����⸦ �����Ѵ�. 

// ������ ���� ������ ������� ��ǥ�� ǥ�����ش�. 


#include "game.h"

int main()
{
	int   type, mode;
	char  cTitle[128];
	CGAME game;
	
	pDraw()->CursorView(HIDE);
	while(true)
	{
		SetConsoleTitle("OMOK GAME - Made by LJW");
		type = pDraw()->GetMenu(cTitle);
		if(type == ESC) break;
		else SetConsoleTitle(cTitle);
		mode = pDraw()->GetMenu();
		
		while(game.playGame(type, mode));
	}

	pDraw()->CursorView(SHOW);
	return 0;
}
