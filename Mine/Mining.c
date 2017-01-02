#include <time.h>
#include <stdlib.h>
#include "structs.h"
#include "core.h"

#define STARTTIME -100
#define DBCLICK 500

extern void getmsg(msg *);
extern void updateGame(gameControl *t);
extern void waitNewGame();
extern void showGameFace(gameControl *);

static void resetMine(gameControl *,int,int);
static void settleGame(gameControl *,msg *);

void Mining(gameControl *t)
{
	msg message;

	while (TRUE)
	{
		showGameFace(t);
		while (TRUE)
		{

			getmsg(&message);
			if (message.mt == left)
			{

				if ((0 <= message.msgX)&&(message.msgX < t->x))
				{	
					if ((0 <= message.msgY)&&(message.msgY < t->y))
					{
						resetMine(t, message.msgX , message.msgY );
						break;
					}

				}

			}

		}
		
		while (TRUE)
		{
			settleGame(t,&message);
			updateGame(t);
			if (t->currentState != gaming)
			{
				waitNewGame();
				break;
			}
			getmsg(&message);
		}
		
	}

}

void settleGame(gameControl *t,msg *message)
{
	if (t->currentState != gaming)
	{
		return;
	}

	Mine **mines = t->allMines;
	int xMine = t->x, yMine = t->y;
	int clickedX = message->msgX, clickedY = message->msgY;
	mineState cms = mines[clickedY][clickedX].currentState;
	myBool isLeft=FALSE, isRight=FALSE;

	if (message->mt == left)
	{
		isLeft = TRUE;
	}
	else
	{
		isRight = TRUE;
	}

	if (cms == none)//没有被标记
	{
		if (isRight)
		{
			mines[clickedY][clickedX].currentState = mine;
		}
		else if (isLeft)
		{
			mines[clickedY][clickedX].isOpen = TRUE;
			mines[clickedY][clickedX].currentState = open;
			if (mines[clickedY][clickedX].isMine)
			{
				t->currentState = lost;
				return;
			}

			int numOfMine = 0;

			for (int i = clickedY - 1; (i < yMine)&&(i<=clickedY+1); i++)
			{
				if (i < 0)
				{
					continue;
				}

				for (int j = clickedX - 1;(j < xMine) && (j<=clickedX + 1); j++)
				{
					if (j < 0)
					{
						continue;
					}

					if (i == clickedY&&j == clickedX)
					{
						continue;
					}

					if (mines[i][j].isMine)
					{
						numOfMine++;
					}
				}

			}

			mines[clickedY][clickedX].num = numOfMine;

			t->restMine--;
			if (t->restMine == t->numOfMine)
			{
				t->currentState = win;
				return;
			}

			if (numOfMine == 0)
			{

				for (int i = clickedY - 1; (i < yMine) && (i <= clickedY + 1); i++)
				{
					if (i < 0)
					{
						continue;
					}

					for (int j = clickedX - 1; (j < xMine) && (j <= clickedX + 1); j++)
					{
						if (j < 0)
						{
							continue;
						}

						if (i == clickedY&&j == clickedX)
						{
							continue;
						}

						if (mines[i][j].isOpen)
						{
							continue;
						}

						message->time = STARTTIME;
						message->msgX = j;
						message->msgY = i;

						settleGame(t, message);

					}

				}

			}//numOfMine==0


		}//isLeft

	}//none
	else if (cms == mine)//被标记为雷
	{
		if (isRight)
		{
			mines[clickedY][clickedX].currentState = unsure;
		}
	}
	else if (cms == unsure)//被标记为不确定
	{
		if (isRight)
		{
			mines[clickedY][clickedX].currentState = none;
		}
	}
	else if (cms == open)//已经被打开
	{
		if (message->time - mines[clickedY][clickedX].lastTime > DBCLICK)//双击事件
		{
			mines[clickedY][clickedX].lastTime = message->time;
			return;
		}

		int mineFlag=0;

		for (int i = clickedY - 1; (i < yMine) && (i <= clickedY + 1); i++)
		{
			if (i < 0)
			{
				continue;
			}

			for (int j = clickedX - 1; (j < xMine) && (j <= clickedX + 1); j++)
			{
				if (j < 0)
				{
					continue;
				}

				if (mines[i][j].currentState == mine)
				{
					mineFlag++;
				}
			}

		}

		mines[clickedY][clickedX].lastTime = message->time;

		if (mineFlag != mines[clickedY][clickedX].num)
		{
			return;
		}

		for (int i = clickedY - 1; (i < yMine) && (i <= clickedY + 1); i++)
		{
			if (i < 0)
			{
				continue;
			}

			for (int j = clickedX - 1; (j < xMine) && (j <= clickedX + 1); j++)
			{
				if (j < 0)
				{
					continue;
				}

				if (mines[i][j].currentState == none)
				{
					msg tempMsg=*message;
					tempMsg.msgX = j;
					tempMsg.msgY = i;
					settleGame(t, &tempMsg);
				}
			}

		}

	}

}

void resetMine(gameControl *t,int clickedX,int clickedY)
{
	srand((unsigned)time(NULL));
	myBool tempBool;
	int randomNum,x=t->x,y=t->y;
	int barNum = x*y;
	Mine **mines = t->allMines;

	for (int i = 0; i <y; i++)
	{

		for (int j = 0; j < x; j++)
		{

			mines[i][j].isOpen = FALSE;
			mines[i][j].lastTime = STARTTIME;
			mines[i][j].currentState = none;

			randomNum = rand() % barNum;
			tempBool = mines[i][j].isMine;
			mines[i][j].isMine = mines[randomNum / y][randomNum%x].isMine;
			mines[randomNum / y][randomNum%x].isMine=tempBool;

		}

	}

	if (mines[clickedY][clickedX].isMine)
	{

		for (int i = 0; i < barNum; i++)
		{
			if (mines[i/y][i%x].isMine == FALSE)
			{
				mines[i / y][i%x].isMine = TRUE;
				mines[clickedY][clickedX].isMine = FALSE;
				break;
			}
		}
		
	}

	t->currentState = gaming;
	t->restMine = (t->x)*(t->y);
}