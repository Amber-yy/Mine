#include <graphics.h>
#include <ctime>
#include "core.h"
#include "structs.h"
#include "functions.h"

#define ESC 27

void getmsg(msg *ms)
{

	mouse_msg mouse;

	for (; is_run(); delay_fps(FPSLIMIT))
	{

		mouse = { 0 };

		if (mousemsg())
		{
			mouse = getmouse();
		}

		if (kbhit())
		{
			if (getch() == ESC)
			{
				exit(0);
			}
		}

		if (mouse.is_down() && mouse.is_left())
		{
			ms->mt = left;
			ms->msgX = mouse.x / BARLEN;
			ms->msgY = mouse.y / BARLEN;
			ms->time = clock();
			return;
		}
		else if (mouse.is_down() && mouse.is_right())
		{
			ms->mt = right;
			ms->msgX = mouse.x / BARLEN;
			ms->msgY = mouse.y / BARLEN;
			ms->time = clock();
			return;
		}

	}

}

void waitNewGame()
{
	mouse_msg mouse;
	char key;



	for (; is_run(); delay_fps(FPSLIMIT))
	{

		mouse = { 0 };

		if (mousemsg())
		{
			mouse = getmouse();
			if (mouse.is_down())
			{
				return;
			}
		}

		if (kbhit())
		{
			key = getch();
			if (key == ESC)
			{
				exit(0);
			}
		}

	}

}