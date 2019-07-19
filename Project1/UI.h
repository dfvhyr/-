#include"head.h"

//������Ϸ����
void DrawGameWindow()
{
	//�Ȼ���Χǽ
	setcolor(BLACK);					//���õ�ǰ��ͼ��ǰ����ɫ
	setlinestyle(PS_SOLID);			// ���õ�ǰ������ʽ��PS_SOLIDΪʵ��
	setfillcolor(BLUE);				//���õ�ǰ�����ɫ

	//��������Χǽ
	for (int x = WALL_SQUARE_WIDTH; x <= GAME_WALL_WIDTH; x += WALL_SQUARE_WIDTH)
	{
		//fillrectangleʹ�õ�ǰ���κ͵�ǰ�����ʽ���б߿�ľ���
		//����Ϊ�������Ͻ�x��y���꣬���½�x��y����
		fillrectangle(x - WALL_SQUARE_WIDTH, 0, x, WALL_SQUARE_WIDTH); //��
		fillrectangle(x - WALL_SQUARE_WIDTH, GAME_WALL_HTGH - WALL_SQUARE_WIDTH, x, GAME_WALL_HTGH);//��
	}
	//��������Χǽ
	for (int y = WALL_SQUARE_WIDTH; y <= GAME_WALL_HTGH; y += WALL_SQUARE_WIDTH)
	{
		
		fillrectangle(0, y, WALL_SQUARE_WIDTH, y + WALL_SQUARE_WIDTH);//��
		fillrectangle(GAME_WALL_WIDTH - WALL_SQUARE_WIDTH, y, GAME_WALL_WIDTH, y + WALL_SQUARE_WIDTH);//��
	}

	//�����ұ�ͳ�Ʒ�������ض���

	//�����ָ���
	setcolor(WHITE);
	setlinestyle(PS_DASH, 2);											//PS_DASHΪ����
	line(GAME_WALL_WIDTH + 20, 0, GAME_WALL_WIDTH + 20, GAME_WALL_HTGH);//���ߡ������ֱ�Ϊ�����յ��x��y����

	//��������
	LOGFONT font;												//�������ԵĽṹ��
	gettextstyle(&font);										//��ȡ��ǰ������ʽ
	settextstyle(18, 0, "����");
	font.lfQuality = ANTIALIASED_QUALITY;						//�������Ч��Ϊ����� 

	//��ʾԤ����״
	outtextxy(GAME_WALL_WIDTH + 80, 30, "Ԥ��");			//��ָ��λ������ַ���������Ϊ��һ���ַ���x��y���ꣻ��������ַ�

	outtextxy(GAME_WALL_WIDTH + 80, 170, "����");

	outtextxy(GAME_WALL_WIDTH + 65, 250, "����˵��");
	outtextxy(GAME_WALL_WIDTH + 40, 290, "w a s d���Ʒ���");
	outtextxy(GAME_WALL_WIDTH + 40, 335, "�ո� ��ͣ");

	//��ʾ����
	setcolor(RED);

	outtextxy(GAME_WALL_WIDTH + 90, 200, "0");

	//ʹ�� API �����޸Ĵ�������  
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, "����˹����");	//����ָ�����ڱ��������ı�
}

//����Ϸ����ʾ����
void DisplayRock(int i, int j, RockLocation_t*  LocatePtr, bool displayed)
{
	int color;int lineColor = WHITE;	//����������ɫ���ߵ���ɫ
	int xRock = 0;int yRock = 0;		//���Ͻǵ�x��y����
	int boardFalg = 0;

	if (displayed == true)
	{
		color = RED, boardFalg = 1;//���displayedΪtrue�Ļ������������ɫ����Ϊred��game_board��Ӧ��λ������Ϊ1��
	}
	else
	{
		color = BLACK, lineColor = BLACK, boardFalg = 0;//���Ϊfalse�����������ɫ����Ϊblack��game_board��Ӧ��λ������Ϊ0��
	}

	setcolor(lineColor);
	setfillcolor(color);

	setlinestyle(PS_SOLID);//����Ϊʵ�ߣ�
	xRock = LocatePtr->left;
	yRock = LocatePtr->top;

	for (int u = 0; u < 4; u++)
	{
		int x = xRock;
		for (int v = 0; v < 4; v++)
		{
			if(tetris[i][j].rock[u][v] == 1)
			{
				fillrectangle(x, yRock, x + ROCK_SQUARE_WIDTH, yRock + ROCK_SQUARE_WIDTH);//����Ϊ�������ϽǺ����½ǵ�x��y����
			}
			x += ROCK_SQUARE_WIDTH;
		}
		yRock += ROCK_SQUARE_WIDTH;
	}
}