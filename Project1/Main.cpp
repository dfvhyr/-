#include"head.h"
#include"UI.h"
#include"Init.h"
#include"Game.h"

int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HIGH);	//��ʼ��ͼ�λ���

	DrawGameWindow();						//����UI����

	InitGame();								//ȫ����Ϸ��ʼ��

	PlayGame();								//��ʼ��Ϸ��Ҫ����

	closegraph();							// �ر�ͼ�λ���
}
