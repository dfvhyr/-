#include"head.h"

//��ȫ����Ϸ��Ϸ���ʼ�����߽��ʼ��Ϊ1
void InitGame()	
{
	for (int i = 0; i < xROCK_SQUARE_NUM + 2; i++)
	{
		game_board[0][i] = 2;  //�ϱ߽�
		game_board[yROCK_SQUARE_NUM + 1][i] = 2; //�±߽�
	}
	for (int i = 0; i < yROCK_SQUARE_NUM + 2; i++)
	{
		game_board[i][0] = 2; //��߽�
		game_board[i][xROCK_SQUARE_NUM + 1] = 2; //�ұ߽�
	}
	//��ȡ����˹���� 
	ShapeRock();
}

//�ѷ�����״��������
void ShapeRock()
{
	tetris[0][0].rock[0][1] = 1; 
	tetris[0][0].rock[1][0] = 1; 
	tetris[0][0].rock[1][1] = 1; 
	tetris[0][0].rock[1][2] = 1; 


	tetris[0][1].rock[0][0] = 1;
	tetris[0][1].rock[1][0] = 1;
	tetris[0][1].rock[2][0] = 1;
	tetris[0][1].rock[1][1] = 1;


	tetris[0][2].rock[0][0] = 1;
	tetris[0][2].rock[0][1] = 1;
	tetris[0][2].rock[0][2] = 1;
	tetris[0][2].rock[1][1] = 1;


	tetris[0][3].rock[1][0] = 1;
	tetris[0][3].rock[0][1] = 1;
	tetris[0][3].rock[1][1] = 1;
	tetris[0][3].rock[2][1] = 1;


	tetris[1][0].rock[0][0] = 1;
	tetris[1][0].rock[1][0] = 1;
	tetris[1][0].rock[2][0] = 1;
	tetris[1][0].rock[2][1] = 1;


	tetris[1][1].rock[0][0] = 1;
	tetris[1][1].rock[0][1] = 1;
	tetris[1][1].rock[0][2] = 1;
	tetris[1][1].rock[1][0] = 1;


	tetris[1][2].rock[0][0] = 1;
	tetris[1][2].rock[0][1] = 1;
	tetris[1][2].rock[1][1] = 1;
	tetris[1][2].rock[2][1] = 1;


	tetris[1][3].rock[0][2] = 1;
	tetris[1][3].rock[1][0] = 1;
	tetris[1][3].rock[1][1] = 1;
	tetris[1][3].rock[1][2] = 1;


	tetris[2][0].rock[0][1] = 1;
	tetris[2][0].rock[1][1] = 1;
	tetris[2][0].rock[2][0] = 1;
	tetris[2][0].rock[2][1] = 1;


	tetris[2][1].rock[0][0] = 1;
	tetris[2][1].rock[1][0] = 1;
	tetris[2][1].rock[1][1] = 1;
	tetris[2][1].rock[1][2] = 1;


	tetris[2][2].rock[0][0] = 1;
	tetris[2][2].rock[0][1] = 1;
	tetris[2][2].rock[1][0] = 1;
	tetris[2][2].rock[2][0] = 1;


	tetris[2][3].rock[0][0] = 1;
	tetris[2][3].rock[0][1] = 1;
	tetris[2][3].rock[0][2] = 1;
	tetris[2][3].rock[1][2] = 1;

	tetris[3][0].rock[0][0] = 1;
	tetris[3][0].rock[0][1] = 1;
	tetris[3][0].rock[1][1] = 1;
	tetris[3][0].rock[1][2] = 1;


	tetris[3][1].rock[0][1] = 1;
	tetris[3][1].rock[1][0] = 1;
	tetris[3][1].rock[1][1] = 1;
	tetris[3][1].rock[2][0] = 1;


	tetris[3][2].rock[0][0] = 1;
	tetris[3][2].rock[0][1] = 1;
	tetris[3][2].rock[1][1] = 1;
	tetris[3][2].rock[1][2] = 1;


	tetris[3][3].rock[0][1] = 1;
	tetris[3][3].rock[1][0] = 1;
	tetris[3][3].rock[1][1] = 1;
	tetris[3][3].rock[2][0] = 1;


	tetris[4][0].rock[0][1] = 1;
	tetris[4][0].rock[0][2] = 1;
	tetris[4][0].rock[1][0] = 1;
	tetris[4][0].rock[1][1] = 1;


	tetris[4][1].rock[0][0] = 1;
	tetris[4][1].rock[1][0] = 1;
	tetris[4][1].rock[1][1] = 1;
	tetris[4][1].rock[2][1] = 1;


	tetris[4][2].rock[0][1] = 1;
	tetris[4][2].rock[0][2] = 1;
	tetris[4][2].rock[1][0] = 1;
	tetris[4][2].rock[1][1] = 1;


	tetris[4][3].rock[0][0] = 1;
	tetris[4][3].rock[1][0] = 1;
	tetris[4][3].rock[1][1] = 1;
	tetris[4][3].rock[2][1] = 1;


	tetris[5][0].rock[0][0] = 1;
	tetris[5][0].rock[1][0] = 1;
	tetris[5][0].rock[2][0] = 1;
	tetris[5][0].rock[3][0] = 1;


	tetris[5][1].rock[0][0] = 1;
	tetris[5][1].rock[0][1] = 1;
	tetris[5][1].rock[0][2] = 1;
	tetris[5][1].rock[0][3] = 1;


	tetris[5][2].rock[0][0] = 1;
	tetris[5][2].rock[1][0] = 1;
	tetris[5][2].rock[2][0] = 1;
	tetris[5][2].rock[3][0] = 1;


	tetris[5][3].rock[0][0] = 1;
	tetris[5][3].rock[0][1] = 1;
	tetris[5][3].rock[0][2] = 1;
	tetris[5][3].rock[0][3] = 1;


	tetris[6][0].rock[0][0] = 1;
	tetris[6][0].rock[0][1] = 1;
	tetris[6][0].rock[1][0] = 1;
	tetris[6][0].rock[1][1] = 1;


	tetris[6][1].rock[0][0] = 1;
	tetris[6][1].rock[0][1] = 1;
	tetris[6][1].rock[1][0] = 1;
	tetris[6][1].rock[1][1] = 1;


	tetris[6][2].rock[0][0] = 1;
	tetris[6][2].rock[0][1] = 1;
	tetris[6][2].rock[1][0] = 1;
	tetris[6][2].rock[1][1] = 1;


	tetris[6][3].rock[0][0] = 1;
	tetris[6][3].rock[0][1] = 1;
	tetris[6][3].rock[1][0] = 1;
	tetris[6][3].rock[1][1] = 1;
}