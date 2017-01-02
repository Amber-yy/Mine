#include <graphics.h>
#include <stdio.h>
#include "core.h"
#include "functions.h"
#include "structs.h"

#define ISMINE "!"
#define UNSURE "?"
#define MINE "*"

#define GAMINGF   "游戏进行中\n地雷总数：%d\n右键可标记地雷,ESC退出游戏\n"
#define WINF "游戏胜利\n地雷总数：%d\n点击任意方块开始新游戏,ESC退出游戏\n"
#define LOSTF "游戏失败\n地雷总数：%d\n点击任意方块开始新游戏,ESC退出游戏\n"

void outputtext(const char* str, int fontSize, int x, int y);

void updateGame(gameControl *t)
{
	cleardevice();
	Mine **mines = t->allMines;
	int x = t->x;
	int y = t->y;
	for (int i = 0; i < y; i++)
	{

		for (int j = 0; j < x; j++)
		{
			if (mines[i][j].isOpen)
			{
				setfillcolor(WHITE);
				bar(j*BARLEN, i*BARLEN, j*BARLEN + BARLEN - MARGIN, i*BARLEN + BARLEN - MARGIN);
				if (mines[i][j].isMine)
				{
					outputtext(MINE, t->fontSize, j, i);
					continue;
				}
				if (mines[i][j].num != 0)
				{
					char buffer[BUFFERL];
					sprintf(buffer, "%d", mines[i][j].num);
					outputtext(buffer, t->fontSize, j, i);
				}
			}
			else
			{
				setfillcolor(t->fillColor);
				bar(j*BARLEN, i*BARLEN, j*BARLEN + BARLEN - MARGIN, i*BARLEN + BARLEN - MARGIN);
				if (mines[i][j].currentState == mine)
				{
					outputtext(ISMINE, t->fontSize, j, i);
				}
				else if (mines[i][j].currentState == unsure)
				{
					outputtext(UNSURE, t->fontSize, j, i);
				}

			}
	
		}

	}

	char buffer[BUFFERL];

	if (t->currentState == gaming)
	{
		sprintf(buffer, GAMINGF, t->numOfMine);
	}
	else if (t->currentState == win)
	{
		sprintf(buffer, WINF, t->numOfMine);
	}
	else if (t->currentState == lost)
	{
		sprintf(buffer, LOSTF, t->numOfMine);
	}
	outtextrect(0, BARLEN*t->y, t->x*BARLEN, t->y*BARLEN + MSGLEN, buffer);

}

void outputtext(const char* str,int fontSize,int x,int y)
{
	outtextrect(x*BARLEN + (BARLEN - MARGIN - fontSize / 2)*strlen(str) / 2,
		y*BARLEN + (BARLEN - MARGIN - fontSize) / 2, BARLEN - MARGIN, BARLEN - MARGIN, str);
}