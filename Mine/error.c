#include <windows.h>
#include "core.h"

void errorHandle(void *ptr,int mode)
{

	if (ptr == NULL)
	{
		if (mode == MODEFILE)
		{
			MessageBox(NULL, WFILE, WTITLE, MB_OK);
		}
		else if (mode == MODEMEM)
		{
			MessageBox(NULL, WMEM, WTITLE, MB_OK);
			exit(1);
		}
	}

}