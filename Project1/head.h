#ifndef _HEAD_H_
#define _HEAD_H_

#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS 1

//�������صĲ���
#define WALL_SQUARE_WIDTH 20									//Χǽ����Ŀ��
#define xWALL_SQUARE_NUM 15										//x�᷽��ķ������Ŀ
#define yWALL_SQUARE_WIDTH 23									//y�᷽��ķ������Ŀ
#define GAME_WALL_WIDTH  (WALL_SQUARE_WIDTH*xWALL_SQUARE_NUM)	//��Ϸ����Ŀ�� 300 
#define GAME_WALL_HTGH (WALL_SQUARE_WIDTH*yWALL_SQUARE_WIDTH)	//��Ϸ����ĸ߶� 460

#define WINDOW_WIDTH 480 // ��Ϸ�ܴ��ڿ�� 480 
#define WINDOW_HIGH 460  // ��Ϸ�ܴ��ڸ߶� 460

//�������˹�������ز���
#define ROCK_SQUARE_WIDTH WALL_SQUARE_WIDTH							//����˹����Ĵ�С����Χǽ���� 20
#define xROCK_SQUARE_NUM  ((GAME_WALL_WIDTH -40)/ROCK_SQUARE_WIDTH) // ��Ϸ��x��ŵĶ���˹������Ŀ��13
#define yROCK_SQUARE_NUM  ((GAME_WALL_HTGH -40)/ROCK_SQUARE_WIDTH)  // ��Ϸ��y��ŵĶ���˹������Ŀ��21

//�����ƶ��������ز���
#define DIRECT_UP    3  
#define DIRECT_DOWN  2      
#define DIRECT_LEFT  -1  
#define DIRECT_RIGHT 1 

//���巽��������ٶ�
#define SPEED 500													//��ʼ�ٶ�
#define SPEED_UP 100												//�ﵽһ����ֵ�󷽿��ƶ����ٵ�����

/*���ݽṹ-���Ա�(�ṹ������)*/
typedef struct ROCK
{
	int rock[4][4];//��ŷ������״
} RockType;

//������ͼ�δ����е�λ��(����λ4*4�������Ͻ�����)  
typedef struct LOCATE
{
	int left;
	int top;
} RockLocation_t;

//ȫ�ֱ���-��Ϸ���״̬����(����ʾ��ǰ������Щλ���з����Χǽ)  
int game_board[yROCK_SQUARE_NUM + 2][xROCK_SQUARE_NUM + 2] = { 0 };
//ȫ�ַ���
int game_socres = 0; 

// ����˹������7�����ͣ�ÿ��������4����ת��ʽ
RockType tetris[7][4] = { 0 };

//Ԥ�����ķ����λ��
RockLocation_t preRockLocation = { GAME_WALL_WIDTH + 70,70 };
//ÿ�����ɳ�ʼ�������λ��
RockLocation_t initRockLocation = { (WALL_SQUARE_WIDTH + 100), WALL_SQUARE_WIDTH };

//�����ļ��еĺ���
// ���������Լ���������Draw.h��
void DrawGameWindow();
void DisplayRock(int i,int j, RockLocation_t*  LocatePtr, bool displayed);

//��ʼ��InitԴ�ļ�
void InitGame();
void ShapeRock();

//game.h
void PlayGame();
bool IsGameOver();

#endif