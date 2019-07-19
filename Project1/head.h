#ifndef _HEAD_H_
#define _HEAD_H_

#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS 1

//界面的相关的参数
#define WALL_SQUARE_WIDTH 20									//围墙方块的宽度
#define xWALL_SQUARE_NUM 15										//x轴方向的方块的数目
#define yWALL_SQUARE_WIDTH 23									//y轴方向的方块的数目
#define GAME_WALL_WIDTH  (WALL_SQUARE_WIDTH*xWALL_SQUARE_NUM)	//游戏区域的宽度 300 
#define GAME_WALL_HTGH (WALL_SQUARE_WIDTH*yWALL_SQUARE_WIDTH)	//游戏区域的高度 460

#define WINDOW_WIDTH 480 // 游戏总窗口宽度 480 
#define WINDOW_HIGH 460  // 游戏总窗口高度 460

//定义俄罗斯方块的相关参数
#define ROCK_SQUARE_WIDTH WALL_SQUARE_WIDTH							//俄罗斯方块的大小等于围墙方块 20
#define xROCK_SQUARE_NUM  ((GAME_WALL_WIDTH -40)/ROCK_SQUARE_WIDTH) // 游戏区x轴放的俄罗斯方块数目：13
#define yROCK_SQUARE_NUM  ((GAME_WALL_HTGH -40)/ROCK_SQUARE_WIDTH)  // 游戏区y轴放的俄罗斯方块数目：21

//定义移动方块的相关操作
#define DIRECT_UP    3  
#define DIRECT_DOWN  2      
#define DIRECT_LEFT  -1  
#define DIRECT_RIGHT 1 

//定义方块下落的速度
#define SPEED 500													//初始速度
#define SPEED_UP 100												//达到一定分值后方块移动加速的增量

/*数据结构-线性表(结构体数组)*/
typedef struct ROCK
{
	int rock[4][4];//存放方块的形状
} RockType;

//方块在图形窗口中的位置(即定位4*4大块的左上角坐标)  
typedef struct LOCATE
{
	int left;
	int top;
} RockLocation_t;

//全局变量-游戏板的状态描述(即表示当前界面哪些位置有方块和围墙)  
int game_board[yROCK_SQUARE_NUM + 2][xROCK_SQUARE_NUM + 2] = { 0 };
//全局分数
int game_socres = 0; 

// 俄罗斯方块有7种类型，每种类型有4种旋转方式
RockType tetris[7][4] = { 0 };

//预览区的方块的位置
RockLocation_t preRockLocation = { GAME_WALL_WIDTH + 70,70 };
//每次生成初始化方块的位置
RockLocation_t initRockLocation = { (WALL_SQUARE_WIDTH + 100), WALL_SQUARE_WIDTH };

//各个文件中的函数
// 画出界面以及画出方块Draw.h中
void DrawGameWindow();
void DisplayRock(int i,int j, RockLocation_t*  LocatePtr, bool displayed);

//初始化Init源文件
void InitGame();
void ShapeRock();

//game.h
void PlayGame();
bool IsGameOver();

#endif