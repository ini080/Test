// ���� AI ���α׷��� ���� 1016�� 12�� 22�� 13�� 10�� 
// ó�� ��ǥ�� ��ǻ�Ͱ� ������ ���� ���� �� �ִ� ������ �����غ���.


#include "game.h"

int main()
{
	pDraw()->CursorView(HIDE);
	
	CGAME game;
	while(game.playGame());

	pDraw()->CursorView(SHOW);
	return 0;
}
