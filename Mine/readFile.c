#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "structs.h"
#include "core.h"

#define CONFIGROUTE "./data/core.txt"

#define CNUMOFMINE "numOfMine"
#define CMINEX "x"
#define CMINEY "y"
#define MUSICROUTE "musicRoute"
#define IMAGEROUTE "coverImage"
#define COVERX "coverX"
#define COVERY "coverY"

#define MINENUM 10
#define MINEX 10
#define MINEY 10
#define SQURE 400

#pragma warning(disable:4996)

extern void errorHandle(void *, int);

void readFile(gameControl *t)
{
	FILE *config;
	config=fopen(CONFIGROUTE,OPENMODE);

	if (config == NULL)
	{
		errorHandle(config, MODEFILE);

		t->numOfMine = MINENUM;
		t->x = MINEX;
		t->y = MINEY;
		t->coverX = SQURE;
		t->coverY = SQURE;
		t->musicRoute = NULL;
		t->coverImage = NULL;

		t->allMines = malloc(MINEY*sizeof(Mine *));
		errorHandle(t->allMines, MODEMEM);

		for (int i = 0; i < MINEX; i++)
		{
			t->allMines[i] = malloc(MINEX*sizeof(Mine));
			errorHandle(t->allMines[i], MODEMEM);
		}

	}
	else
	{
		char *buffer=malloc(BUFFERL*sizeof(char));
		char *command = malloc(CMDL*sizeof(char));
		t->musicRoute = NULL;
		t->coverImage = NULL;

		errorHandle(buffer, MODEMEM);
		errorHandle(buffer, MODEMEM);

		while (TRUE)
		{
			fgets(buffer, BUFFERL, config);

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

			char *value = buffer + size +1;

			if (strcmp(command, CNUMOFMINE) == 0)
			{
				t->numOfMine = atoi(value);
			}
			else if (strcmp(command, CMINEX)==0)
			{
				t->x = atoi(value);
			}
			else if (strcmp(command, CMINEY)==0)
			{
				t->y = atoi(value);
			}
			else if (strcmp(command, COVERX) == 0)
			{
				t->coverX = atoi(value);
			}
			else if (strcmp(command, COVERY) == 0)
			{
				t->coverY = atoi(value);
			}
			else if (strcmp(command, IMAGEROUTE)==0)
			{
				int len = strlen(value);
				free(t->coverImage);
				t->coverImage = malloc(len);
				errorHandle(t->coverImage, MODEMEM);
				memcpy(t->coverImage, value, len-1);
				t->coverImage[len - 1] = 0;
			}
			else if (strcmp(command, MUSICROUTE) == 0)
			{
				int len = strlen(value);
				free(t->musicRoute);
				t->musicRoute = malloc(len);
				errorHandle(t->musicRoute, MODEMEM);
				memcpy(t->musicRoute, value, len-1);
				t->musicRoute[len - 1] = 0;
			}

			if (feof(config))
			{
				break;
			}
		}

		fclose(config);
		free(buffer);
		free(command);

		t->allMines = malloc(t->y*sizeof(Mine *));

		errorHandle(t->allMines, MODEMEM);

		for (int i = 0; i < t->x; i++)
		{
			t->allMines[i] = malloc(t->x*sizeof(Mine));
			errorHandle(t->allMines[i], MODEMEM);
		}

	}

	int currentMine = 0;
	for (int i = 0; i < t->y; i++)
	{

		for (int j = 0; j < t->x; j++)
		{
			if (currentMine < t->numOfMine)
			{
				t->allMines[i][j].isMine = TRUE;
				currentMine++;
			}
			else
			{
				t->allMines[i][j].isMine = FALSE;
			}

		}

	}

}