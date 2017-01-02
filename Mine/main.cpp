#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"

int main()
{
	gameControl *t = (gameControl *)malloc(sizeof(gameControl));

	readFile(t);
	iniGame(t);
	Mining(t);

	return 0;
}