#include"head.h"

//画出游戏界面
void DrawGameWindow()
{
	//先画出围墙
	setcolor(BLACK);					//设置当前绘图的前景颜色
	setlinestyle(PS_SOLID);			// 设置当前画线样式，PS_SOLID为实线
	setfillcolor(BLUE);				//设置当前填充颜色

	//画出上下围墙
	for (int x = WALL_SQUARE_WIDTH; x <= GAME_WALL_WIDTH; x += WALL_SQUARE_WIDTH)
	{
		//fillrectangle使用当前线形和当前填充样式画有边框的矩形
		//参数为矩形左上角x，y坐标，右下角x，y坐标
		fillrectangle(x - WALL_SQUARE_WIDTH, 0, x, WALL_SQUARE_WIDTH); //上
		fillrectangle(x - WALL_SQUARE_WIDTH, GAME_WALL_HTGH - WALL_SQUARE_WIDTH, x, GAME_WALL_HTGH);//下
	}
	//画出左右围墙
	for (int y = WALL_SQUARE_WIDTH; y <= GAME_WALL_HTGH; y += WALL_SQUARE_WIDTH)
	{
		
		fillrectangle(0, y, WALL_SQUARE_WIDTH, y + WALL_SQUARE_WIDTH);//左
		fillrectangle(GAME_WALL_WIDTH - WALL_SQUARE_WIDTH, y, GAME_WALL_WIDTH, y + WALL_SQUARE_WIDTH);//右
	}

	//画出右边统计分数及相关东西

	//画出分割线
	setcolor(WHITE);
	setlinestyle(PS_DASH, 2);											//PS_DASH为虚线
	line(GAME_WALL_WIDTH + 20, 0, GAME_WALL_WIDTH + 20, GAME_WALL_HTGH);//画线。参数分别为起点和终点的x，y坐标

	//设置字体
	LOGFONT font;												//字体属性的结构体
	gettextstyle(&font);										//获取当前字体样式
	settextstyle(18, 0, "宋体");
	font.lfQuality = ANTIALIASED_QUALITY;						//设置输出效果为抗锯齿 

	//显示预览形状
	outtextxy(GAME_WALL_WIDTH + 80, 30, "预览");			//在指定位置输出字符串。参数为第一个字符的x，y坐标；待输出的字符

	outtextxy(GAME_WALL_WIDTH + 80, 170, "分数");

	outtextxy(GAME_WALL_WIDTH + 65, 250, "操作说明");
	outtextxy(GAME_WALL_WIDTH + 40, 290, "w a s d控制方向");
	outtextxy(GAME_WALL_WIDTH + 40, 335, "空格 暂停");

	//显示分数
	setcolor(RED);

	outtextxy(GAME_WALL_WIDTH + 90, 200, "0");

	//使用 API 函数修改窗口名称  
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, "俄罗斯方块");	//更改指定窗口标题栏的文本
}

//在游戏区显示方块
void DisplayRock(int i, int j, RockLocation_t*  LocatePtr, bool displayed)
{
	int color;int lineColor = WHITE;	//方块的填充颜色和线的颜色
	int xRock = 0;int yRock = 0;		//左上角的x，y坐标
	int boardFalg = 0;

	if (displayed == true)
	{
		color = RED, boardFalg = 1;//如果displayed为true的话，将方块块颜色设置为red，game_board对应的位置设置为1；
	}
	else
	{
		color = BLACK, lineColor = BLACK, boardFalg = 0;//如果为false，将方块块颜色设置为black，game_board对应的位置设置为0；
	}

	setcolor(lineColor);
	setfillcolor(color);

	setlinestyle(PS_SOLID);//设置为实线，
	xRock = LocatePtr->left;
	yRock = LocatePtr->top;

	for (int u = 0; u < 4; u++)
	{
		int x = xRock;
		for (int v = 0; v < 4; v++)
		{
			if(tetris[i][j].rock[u][v] == 1)
			{
				fillrectangle(x, yRock, x + ROCK_SQUARE_WIDTH, yRock + ROCK_SQUARE_WIDTH);//参数为矩形左上角和右下角的x，y坐标
			}
			x += ROCK_SQUARE_WIDTH;
		}
		yRock += ROCK_SQUARE_WIDTH;
	}
}