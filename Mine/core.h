#pragma once

#define MODEFILE 0
#define MODEMEM 1
#define BUFFERL 255
#define CMDL 20

#define FPSLIMIT 60

#define SPLITCHAR '='

#define DEFAULTFONT "����"
#define FONTSIZE 20
#define FILLCOLOR 4286945
#define FONTCOLOR 16753920

#define OPENMODE "r"

#define BARLEN 40
#define MARGIN 2
#define MSGLEN 60

/*��unicode�����ͷ�unicode�������ò�ͬ�Ĵ���ʽ*/
#ifdef UNICODE 

#define WTITLE L"��������"
#define WFILE L"��Ϸ������ȱʡֵ��ʼ��"
#define WMEM L"�ڴ����ʧ��"

#else

#define WTITLE "��������"
#define WFILE "��Ϸ������ȱʡֵ��ʼ��"
#define WMEM "�ڴ����ʧ��"

#endif