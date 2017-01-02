#include <graphics.h>
#include <stdio.h>
#include "functions.h"
#include "structs.h"
#include "core.h"

#define FONTFILE "./data/font.txt"
#define WORDS "请按任意键开始游戏"

#define CFONT "font"
#define CFONTSIZE "fontSize"
#define CFONTCOLOR "fontColor"
#define CFILLCOLOR "fillColor"
#define CWORDS "words"

#define WINDOW "扫雷"

#define FORMAT "点击任意方块开始游戏\n剩余雷数：%d\n右键可标记地雷，ESC退出游戏\n"

#ifdef UNICODE

#define PLAYSTR L"play file repeat"

#else

#define PLAYSTR "play file repeat"

#endif

#define OPENSTR1 "open "
#define OPENSTR2 " alias file"

static void showWelcome(gameControl *);

void iniGame(gameControl *t)
{
	initgraph(t->coverX,t->coverY);
	setrendermode(RENDER_MANUAL);
	setbkmode(TRANSPARENT);
	setcaption(WINDOW);

	if ((t->coverImage == NULL)||t->coverImage[0]==0)
	{
		showWelcome(t);
		return;
	}
	
	PIMAGE bgImg = newimage();
	getimage(bgImg, t->coverImage);
	putimage(0, 0, bgImg);
	showWelcome(t);
	delimage(bgImg);
	initgraph(t->x*BARLEN, t->y*BARLEN + MSGLEN);
}

void showGameFace(gameControl *t)
{
	cleardevice();
	setfillcolor(t->fillColor);
	for (int i = 0; i < t->y; i++)
	{

		for (int j = 0; j < t->x; j++)
		{
			bar(j*BARLEN, i*BARLEN, j*BARLEN + BARLEN - MARGIN, i*BARLEN+BARLEN - MARGIN);
		}

	}

	char buffer[BUFFERL];
	sprintf(buffer, FORMAT, t->numOfMine);
	outtextrect(0, BARLEN*t->y, t->x*BARLEN, t->y*BARLEN + MSGLEN, buffer);
}

void showWelcome(gameControl *t)
{
	FILE *welcome;
	int fontSize=FONTSIZE,fontColor=FONTCOLOR,fillColor=FILLCOLOR;
	char *font=NULL, *word=NULL, *buffer=NULL,*command=NULL;

	welcome = fopen(FONTFILE, OPENMODE);

	if (welcome == NULL)
	{
		t->fontColor = fontColor;
		t->fillColor = fillColor;
		t->fontSize = fontSize;

		setfont(FONTSIZE,0,DEFAULTFONT);
		setcolor(GREEN);
		int w = FONTSIZE*strlen(WORDS) / 2;
		int rx = (t->coverX - w) / 2;
		int ry = t->coverY * 5 / 6;
		outtextxy(rx, ry, WORDS);
		getch();
		return;
	}

	font = (char *)malloc(BUFFERL);
	word = (char *)malloc(BUFFERL);
	buffer = (char *)malloc(BUFFERL);
	command = (char *)malloc(CMDL);
	
	errorHandle(font,MODEMEM);
	errorHandle(word, MODEMEM);
	errorHandle(buffer, MODEMEM);
	errorHandle(command, MODEMEM);

	while (TRUE)
	{
		fgets(buffer, BUFFERL, welcome);

		int size;
		for (size = 0;; size++)
		{
			if (*(buffer + size) == SPLITCHAR)
			{
				break;
			}
		}

		memcpy(command, buffer, size);
		command[size] = 0;

		char *value = buffer + size + 1;

		if (strcmp(command, CFONTSIZE) == 0)
		{
			fontSize = atoi(value);
		}
		else if (strcmp(command, CFONTCOLOR) == 0)
		{
			fontColor= atoi(value);
		}
		else if (strcmp(command, CFILLCOLOR) == 0)
		{
			fillColor = atoi(value);
		}
		else if (strcmp(command, CFONT) == 0)
		{
			int len = strlen(value);
			memcpy(font, value, len - 1);
			font[len - 1] = 0;
		}
		else if (strcmp(command, CWORDS) == 0)
		{
			int len = strlen(value);
			memcpy(word, value, len);
			word[len] = 0;
		}

		if (feof(welcome))
		{
			break;
		}
	}

	fclose(welcome);

	setfont(fontSize, 0, font);
	setcolor(fontColor);
	setfillcolor(fillColor);
	int w = fontSize*strlen(word)/2;
	int rx = (t->coverX - w)/2;
	int ry = t->coverY*5 / 6;
	outtextxy(rx, ry, word);
	
	sprintf(buffer, "%s%s%s", OPENSTR1, t->musicRoute, OPENSTR2);

#ifdef UNICODE
	wchar_t *cmd = (wchar_t *)malloc(BUFFERL);
	MultiByteToWideChar(CP_ACP, 0, buffer, -1, cmd, strlen(buffer) * sizeof(wchar_t));
	mciSendString(cmd, NULL, 0, NULL);
	free(cmd);
#else
	mciSendString(buffer, NULL, 0, NULL);
#endif

	mciSendString(PLAYSTR, NULL, 0, NULL);
	
	t->fontColor = fontColor;
	t->fillColor = fillColor;
	t->fontSize = fontSize;

	getch();
	free(font);
	free(word);
	free(buffer);
	free(command);
}