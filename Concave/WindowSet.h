#include "Concave.h"

// ������ ���� 
#define Windows_Width	1020
#define Windows_Heigth	760
#define Windows_Background_Color RGB(100,100,150)

// Ÿ�̸� ����
#define Timer_ID_Second		5000
#define Timer_ID_Start		5001

// ���� �÷��� �ð�
#define PlayTime			30

// ĳ���� �� RECT
#define Ch_Rect_Color RGB(255,0,0)

// ���� ���� �� ��
#define Current_Color RGB(0,255,0)

void Center_Screen(HWND window, DWORD style, DWORD exStyle);    // Window ȭ�� ��� ��ġ�� �ű�� �Լ�