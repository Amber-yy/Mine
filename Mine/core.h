#pragma once

#define MODEFILE 0
#define MODEMEM 1
#define BUFFERL 255
#define CMDL 20

#define FPSLIMIT 60

#define SPLITCHAR '='

#define DEFAULTFONT "楷体"
#define FONTSIZE 20
#define FILLCOLOR 4286945
#define FONTCOLOR 16753920

#define OPENMODE "r"

#define BARLEN 40
#define MARGIN 2
#define MSGLEN 60

/*对unicode环境和非unicode环境采用不同的处理方式*/
#ifdef UNICODE 

#define WTITLE L"发生错误"
#define WFILE L"游戏将采用缺省值初始化"
#define WMEM L"内存分配失败"

#else

#define WTITLE "发生错误"
#define WFILE "游戏将采用缺省值初始化"
#define WMEM "内存分配失败"

#endif