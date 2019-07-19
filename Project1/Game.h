#include"head.h"
#define _CRT_SECURE_NO_WARNINGS 1

bool MoveAble(int i, int j, RockLocation_t* currentLocatePtr, int f_direction);
void SetGameBoardFlag(int i, int j, RockLocation_t* curRockLocation);
int UserHitKeyBoard(char userHit, int i, int j, RockLocation_t* curRockLocation);
void FullLine();
void UpdateSocres(int scores);
void DelCurLine(int rowIdx);
bool IsGameOver();
bool IsTouch(int i, int j, int x, int y);

void PlayGame()
{
	char userHit = 0;						//�û��û����̵ļ�ֵ
	int Shape = 0;int Kind = 0;				//������������ת����
	int NextShape = 0; int NextKind = 0;	//��һ��������������ת����

	RockLocation_t curRockLocation;			//��ʼ�����ɵķ�������꣨���Ͻ�x��y��
	curRockLocation.left = initRockLocation.left;
	curRockLocation.top = initRockLocation.top;

	DWORD oldtime = 0;
	srand((unsigned int)time(NULL));						//���������
	Shape = rand() % 7;	NextShape = (rand()*Shape) % 7;		//������ɵ�ǰ����һ�����������
	Kind = rand() % 4;	NextKind = (rand()*Kind) % 4;		//������ɵ�ǰ����һ���������ת����

	//�ڳ�ʼλ�ú�Ԥ������ʾ������״
	DisplayRock(Shape,Kind, &initRockLocation, 1);
	DisplayRock(NextShape, NextKind, &preRockLocation, 1);

	bool moveAbled = false;

	while (true)
	{
		//�жϵ�ǰ�����ܷ��������ƣ�
		moveAbled = MoveAble(Shape, Kind, &curRockLocation, DIRECT_DOWN);
		if (!moveAbled) 
		{
			//�ѵ�ǰ����ֹͣ��λ�õ�game_board��ֵ�޸�Ϊ1
			SetGameBoardFlag(Shape, Kind, &curRockLocation);

			//�ж��Ƿ����С����Ѿ����У����������У��������ƣ��÷�����
			FullLine();

			//�ж���Ϸ�Ƿ����
			if (IsGameOver())
			{
				MessageBox(NULL, "��Ϸ����", "GAME OVER", MB_OK);
				exit(0);
			}

			//Ϊ�´�����ģ����׼���������ɵķ��飬�������µ�Ԥ������
			DisplayRock(NextShape, NextKind, &preRockLocation, false);
			Shape = NextShape; Kind = NextKind;
			NextShape = rand() % 7; NextKind = rand() % 4;
			DisplayRock(Shape, Kind, &initRockLocation, 1);
			DisplayRock(NextShape, NextKind, &preRockLocation, 1);
			// ִ��δ��ɵĻ�������
			FlushBatchDraw();				

			//�����������λ������
			curRockLocation.left = initRockLocation.left;
			curRockLocation.top = initRockLocation.top;
		}

		//�ж��û��Ƿ��û����̣���������Ӧ���¼�
		if (_kbhit()) 
		{
			userHit = _getch();
			if (userHit == 'w' || userHit == 'W')
			{
				Kind= UserHitKeyBoard(userHit, Shape, Kind, &curRockLocation);
			}
			else
				UserHitKeyBoard(userHit, Shape, Kind, &curRockLocation);

		}

		//���û�û�в��������Զ�����һ����λ����ÿ��15�֣����������ٶȼӿ�һ������
		DWORD newtime = GetTickCount();
		if (newtime - oldtime >= SPEED - (game_socres / 15)*SPEED_UP && moveAbled == TRUE)
		{
			oldtime = newtime;
			DisplayRock(Shape, Kind, &curRockLocation, false);
			curRockLocation.top += ROCK_SQUARE_WIDTH;   
		}
		
		//�����·���
		DisplayRock(Shape, Kind, &curRockLocation, 1);
		// ִ��δ��ɵĻ�������
		FlushBatchDraw();
		//���û���Ӧ��ʱ��
		Sleep(20);
	}
}


//�����������
int UserHitKeyBoard(char userHit, int i, int j, RockLocation_t* curRockLocation)
{
	switch (userHit)
	{
	case 'W':
	case 'w':
		if (MoveAble(i, j, curRockLocation, DIRECT_UP))
		{
			DisplayRock(i, j, curRockLocation, false);
			j = (j + 1) % 4;
		}
		return j;
		break;
	case 'S':
	case 's':
		if (MoveAble(i, j, curRockLocation, DIRECT_DOWN))
		{
			DisplayRock(i, j, curRockLocation, false);
			curRockLocation->top += 2 * (ROCK_SQUARE_WIDTH);
			if (!MoveAble(i, j, curRockLocation, DIRECT_DOWN))
			{
				curRockLocation->top -= ROCK_SQUARE_WIDTH;
			}
		}
		break;
	case 'A':
	case 'a': 
		if (MoveAble(i, j, curRockLocation, DIRECT_LEFT))
		{
			DisplayRock(i, j, curRockLocation, false);
			curRockLocation->left -= ROCK_SQUARE_WIDTH;
		}
		break;
	case 'D':
	case 'd': 
		if (MoveAble(i, j, curRockLocation, DIRECT_RIGHT))
		{
			DisplayRock(i, j, curRockLocation, false);
			curRockLocation->left += ROCK_SQUARE_WIDTH;
		}
		break;
	case ' ': 
		while (1)
		{
			userHit = _getch();
			if (userHit == ' ')
				break;
		}
		break;
	default:
		break;
	
	}
	return 0;
}

//�ж��Ƿ����У�����������Ȼ�����÷�
void FullLine()
{
	//�����һ�㿪ʼ���μ��
	for (int i = yROCK_SQUARE_NUM; i > 0; i--)
	{
		int sum = 0;
		for (int j = 1; j <= xROCK_SQUARE_NUM; j++)
		{
			sum = sum + game_board[i][j];
		}
		if (sum == xROCK_SQUARE_NUM) //���У�������ǰ�У����·���
		{
			DelCurLine(i);
			game_socres += 3;
			UpdateSocres(game_socres);
		}
	}
}

//���µ÷�ֵ��ʾ
void UpdateSocres(int scores)
{
	setcolor(RED);
	TCHAR s[3];
	sprintf_s(s, "%d", scores);
	outtextxy(GAME_WALL_WIDTH + 90, 200, s);// ��ָ��λ������ַ���	
}

//������ǰ������ָ�����У��������������ƶ�
void DelCurLine(int y)
{
	//������ǰ��
	setcolor(BLACK);
	setfillcolor(BLACK);
	for (int i = 1; i <= xROCK_SQUARE_NUM; i++)
	{
		fillrectangle(i*ROCK_SQUARE_WIDTH,
			y*ROCK_SQUARE_WIDTH,
			(i + 1) * ROCK_SQUARE_WIDTH,
			(y + 1)*ROCK_SQUARE_WIDTH);
	}

	//���������������
	int cnt = 0;
	while (cnt != xROCK_SQUARE_NUM) //ֱ�������ǿ��е�Ϊֹ  
	{
		cnt = 0;
		for (int i = 1; i <= xROCK_SQUARE_NUM; i++)
		{
			game_board[y][i] = game_board[y - 1][i];

			//���������һ��  
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillrectangle(i*ROCK_SQUARE_WIDTH,
				(y - 1) * ROCK_SQUARE_WIDTH,
				(i + 1) * ROCK_SQUARE_WIDTH,
				y*ROCK_SQUARE_WIDTH);

			//��ʾ�����һ��  
			if (game_board[y][i] == 1)
			{
				setcolor(WHITE);
				setfillcolor(RED);
				fillrectangle(i*ROCK_SQUARE_WIDTH,
					y*ROCK_SQUARE_WIDTH,
					(i + 1) * ROCK_SQUARE_WIDTH,
					(y + 1)*ROCK_SQUARE_WIDTH);
			}
			
			if (game_board[y][i] == 0)
				cnt++;            //�п��ܳ���ͬʱ��ȥ���е������ͳ����һ���ǲ��Ƕ��ǿո�  
		} 
		y--;
	}
}

//�ж��Ƿ��������������ƶ����飬���ܷ���true���񷵻�false
bool MoveAble(int i,int j, RockLocation_t* currentLocatePtr, int f_direction)
{
	int rockX;
	int rockY;

	rockX = currentLocatePtr->left;
	rockY = currentLocatePtr->top;

	//�ж��ܷ��ƶ�(��ɨ�輴���ƶ���λ��,�Ƿ���Χǽ����������)
	switch (f_direction)
	{
		//����
	case DIRECT_UP:
		return IsTouch(i, (j + 1) % 4, rockX, rockY); break;
		//�����ƶ�
	case DIRECT_DOWN:
		return IsTouch(i, j, rockX, rockY + WALL_SQUARE_WIDTH);break;
		//�����ƶ�
	case DIRECT_LEFT:
		return IsTouch(i, j, rockX - WALL_SQUARE_WIDTH, rockY); break;
		//�����ƶ�
	case DIRECT_RIGHT:
		return IsTouch(i, j, rockX + WALL_SQUARE_WIDTH, rockY); break;
	default:
		break;
	}
	return true;
}

//�ж��Ƿ������������ǽ��
bool IsTouch(int i, int j, int x, int y)
{
	for (int u = 0; u < 4; u++)
	{
		for (int v = 0; v < 4; v++)
		{
			//��Ϊ����
			if (tetris[i][j].rock[u][v] == 1)
			{
					
				if (game_board[(y + u * WALL_SQUARE_WIDTH)/ WALL_SQUARE_WIDTH]
					[(x + v * WALL_SQUARE_WIDTH)/ WALL_SQUARE_WIDTH] != 0)
						return false;
			}
		}
	}
	return true;
}

//����Ϸgame_board���ñ�Ǳ�ʾ�˴��Ѿ�������ռ����
void SetGameBoardFlag(int i, int j, RockLocation_t* curRockLocation)
{
	int rockX;
	int rockY;

	rockX = curRockLocation->left;
	rockY = curRockLocation->top;

	for (int u = 0; u < 4; u++)
	{
		for (int v = 0; v < 4; v++)
		{
			if (tetris[i][j].rock[u][v] == 1)
			{
				game_board[(rockY + u * WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH]
					[(rockX + v * WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH] = 1;
			}
			
		}
	}
}

//�ж���Ϸ�Ƿ����
bool IsGameOver()
{
	bool topLineHaveRock = false;//�����Ƿ��з���
	bool bottomLineHaveRock = false;

	for (int i = 1; i < xROCK_SQUARE_NUM; ++i)
	{
		if (game_board[1][i] == 1)
			topLineHaveRock = true;
		if (game_board[yROCK_SQUARE_NUM][i] == 1)
			bottomLineHaveRock = true;
	}
	if (bottomLineHaveRock && topLineHaveRock)
		return true;
	else
		return false;
}
