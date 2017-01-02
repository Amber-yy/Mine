#pragma once

typedef char myBool;
#define TRUE 1
#define FALSE 0

/*�׵ı����״̬ö��*/
typedef enum
{
	none,
	mine,
	unsure,
	open
}mineState;

/*��ʾ�׵Ľṹ��*/
typedef struct
{
	myBool isMine;
	myBool isOpen;
	int num;
	int lastTime;
	mineState currentState;
}Mine;

/*��ʾ��Ϸ״̬��ö��*/
typedef enum
{
	gaming,
	lost,
	win,
}gameState;

/*��Ϸ���ؽṹ��*/
typedef struct
{
	int numOfMine;
	int restMine;
	int x;
	int y;
	int coverX;
	int coverY;
	int fontColor;
	int fillColor;
	int fontSize;
	gameState currentState;
	char *musicRoute;
	char *coverImage;
	Mine **allMines;
}gameControl;

/*��Ϣ����ö��*/
typedef enum
{
	left,
	right,
}msgType;

/*��Ϣ�ṹ��*/
typedef struct
{
	msgType mt;
	int time;
	int msgX;
	int msgY;
}msg;