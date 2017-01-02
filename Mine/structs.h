#pragma once

typedef char myBool;
#define TRUE 1
#define FALSE 0

/*雷的被标记状态枚举*/
typedef enum
{
	none,
	mine,
	unsure,
	open
}mineState;

/*表示雷的结构体*/
typedef struct
{
	myBool isMine;
	myBool isOpen;
	int num;
	int lastTime;
	mineState currentState;
}Mine;

/*表示游戏状态的枚举*/
typedef enum
{
	gaming,
	lost,
	win,
}gameState;

/*游戏主控结构体*/
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

/*消息类型枚举*/
typedef enum
{
	left,
	right,
}msgType;

/*消息结构体*/
typedef struct
{
	msgType mt;
	int time;
	int msgX;
	int msgY;
}msg;