#include "Concave.h"

// 윈도우 관련 
#define Windows_Width	1020
#define Windows_Heigth	760
#define Windows_Background_Color RGB(100,100,150)

// 타이머 관련
#define Timer_ID_Second		5000
#define Timer_ID_Start		5001

// 게임 플레이 시간
#define PlayTime			30

// 캐릭터 턴 RECT
#define Ch_Rect_Color RGB(255,0,0)

// 현재 놓은 수 색
#define Current_Color RGB(0,255,0)

void Center_Screen(HWND window, DWORD style, DWORD exStyle);    // Window 화면 가운데 위치로 옮기는 함수