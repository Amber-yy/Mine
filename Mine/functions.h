#pragma once
#include "structs.h"

void iniGame(gameControl *);

extern "C"
{
	void readFile(gameControl *);
	void errorHandle(void *, int);
	void Mining(gameControl *);
	void deleteData(gameControl *);
	void getmsg(msg *);
	void updateGame(gameControl *t);
	void waitNewGame();
	void showGameFace(gameControl *);
}