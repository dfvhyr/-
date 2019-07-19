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
	char userHit = 0;						//用户敲击键盘的键值
	int Shape = 0;int Kind = 0;				//方块的种类和旋转方向
	int NextShape = 0; int NextKind = 0;	//下一个方块的种类和旋转方向

	RockLocation_t curRockLocation;			//初始化生成的方块的坐标（左上角x，y）
	curRockLocation.left = initRockLocation.left;
	curRockLocation.top = initRockLocation.top;

	DWORD oldtime = 0;
	srand((unsigned int)time(NULL));						//生成随机数
	Shape = rand() % 7;	NextShape = (rand()*Shape) % 7;		//随机生成当前和下一个方块的类型
	Kind = rand() % 4;	NextKind = (rand()*Kind) % 4;		//随机生成当前和下一个方块的旋转方向

	//在初始位置和预览区显示方块形状
	DisplayRock(Shape,Kind, &initRockLocation, 1);
	DisplayRock(NextShape, NextKind, &preRockLocation, 1);

	bool moveAbled = false;

	while (true)
	{
		//判断当前方块能否再往下移：
		moveAbled = MoveAble(Shape, Kind, &curRockLocation, DIRECT_DOWN);
		if (!moveAbled) 
		{
			//把当前方块停止的位置的game_board的值修改为1
			SetGameBoardFlag(Shape, Kind, &curRockLocation);

			//判断是否满行。若已经满行，则消除该行，整体下移，得分增加
			FullLine();

			//判断游戏是否结束
			if (IsGameOver())
			{
				MessageBox(NULL, "游戏结束", "GAME OVER", MB_OK);
				exit(0);
			}

			//为下次生成模块做准备，擦除旧的方块，并生成新的预览方块
			DisplayRock(NextShape, NextKind, &preRockLocation, false);
			Shape = NextShape; Kind = NextKind;
			NextShape = rand() % 7; NextKind = rand() % 4;
			DisplayRock(Shape, Kind, &initRockLocation, 1);
			DisplayRock(NextShape, NextKind, &preRockLocation, 1);
			// 执行未完成的绘制任务
			FlushBatchDraw();				

			//将方块的生成位置重置
			curRockLocation.left = initRockLocation.left;
			curRockLocation.top = initRockLocation.top;
		}

		//判断用户是否敲击键盘，并处理相应的事件
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

		//若用户没有操作，就自动下移一个单位。且每得15分，方块下落速度加快一个档次
		DWORD newtime = GetTickCount();
		if (newtime - oldtime >= SPEED - (game_socres / 15)*SPEED_UP && moveAbled == TRUE)
		{
			oldtime = newtime;
			DisplayRock(Shape, Kind, &curRockLocation, false);
			curRockLocation.top += ROCK_SQUARE_WIDTH;   
		}
		
		//画出新方块
		DisplayRock(Shape, Kind, &curRockLocation, 1);
		// 执行未完成的绘制任务
		FlushBatchDraw();
		//给用户反应的时间
		Sleep(20);
	}
}


//处理键盘命令
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

//判断是否满行，满行消除，然后计算得分
void FullLine()
{
	//从最底一层开始依次检查
	for (int i = yROCK_SQUARE_NUM; i > 0; i--)
	{
		int sum = 0;
		for (int j = 1; j <= xROCK_SQUARE_NUM; j++)
		{
			sum = sum + game_board[i][j];
		}
		if (sum == xROCK_SQUARE_NUM) //满行，消除当前行，更新分数
		{
			DelCurLine(i);
			game_socres += 3;
			UpdateSocres(game_socres);
		}
	}
}

//更新得分值显示
void UpdateSocres(int scores)
{
	setcolor(RED);
	TCHAR s[3];
	sprintf_s(s, "%d", scores);
	outtextxy(GAME_WALL_WIDTH + 90, 200, s);// 在指定位置输出字符串	
}

//擦除当前参数所指定的行，并将整体向下移动
void DelCurLine(int y)
{
	//擦除当前行
	setcolor(BLACK);
	setfillcolor(BLACK);
	for (int i = 1; i <= xROCK_SQUARE_NUM; i++)
	{
		fillrectangle(i*ROCK_SQUARE_WIDTH,
			y*ROCK_SQUARE_WIDTH,
			(i + 1) * ROCK_SQUARE_WIDTH,
			(y + 1)*ROCK_SQUARE_WIDTH);
	}

	//把上面的行向下移
	int cnt = 0;
	while (cnt != xROCK_SQUARE_NUM) //直到遇到是空行的为止  
	{
		cnt = 0;
		for (int i = 1; i <= xROCK_SQUARE_NUM; i++)
		{
			game_board[y][i] = game_board[y - 1][i];

			//擦除上面的一行  
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillrectangle(i*ROCK_SQUARE_WIDTH,
				(y - 1) * ROCK_SQUARE_WIDTH,
				(i + 1) * ROCK_SQUARE_WIDTH,
				y*ROCK_SQUARE_WIDTH);

			//显示下面的一行  
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
				cnt++;            //有可能出现同时消去多行的情况，统计这一行是不是都是空格  
		} 
		y--;
	}
}

//判断是否可以向各个方向移动方块，若能返回true，否返回false
bool MoveAble(int i,int j, RockLocation_t* currentLocatePtr, int f_direction)
{
	int rockX;
	int rockY;

	rockX = currentLocatePtr->left;
	rockY = currentLocatePtr->top;

	//判断能否移动(即扫描即将移动的位置,是否有围墙或其他方块)
	switch (f_direction)
	{
		//变形
	case DIRECT_UP:
		return IsTouch(i, (j + 1) % 4, rockX, rockY); break;
		//向下移动
	case DIRECT_DOWN:
		return IsTouch(i, j, rockX, rockY + WALL_SQUARE_WIDTH);break;
		//向左移动
	case DIRECT_LEFT:
		return IsTouch(i, j, rockX - WALL_SQUARE_WIDTH, rockY); break;
		//向右移动
	case DIRECT_RIGHT:
		return IsTouch(i, j, rockX + WALL_SQUARE_WIDTH, rockY); break;
	default:
		break;
	}
	return true;
}

//判断是否碰触到方块或墙壁
bool IsTouch(int i, int j, int x, int y)
{
	for (int u = 0; u < 4; u++)
	{
		for (int v = 0; v < 4; v++)
		{
			//若为方块
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

//给游戏game_board设置标记表示此处已经被方块占据了
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

//判断游戏是否结束
bool IsGameOver()
{
	bool topLineHaveRock = false;//顶行是否有方块
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
