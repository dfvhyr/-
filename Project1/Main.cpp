#include"head.h"
#include"UI.h"
#include"Init.h"
#include"Game.h"

int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HIGH);	//初始化图形环境

	DrawGameWindow();						//画出UI界面

	InitGame();								//全局游戏初始化

	PlayGame();								//开始游戏主要流程

	closegraph();							// 关闭图形环境
}
