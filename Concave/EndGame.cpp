#include "EndGame.h"

void EndGame(HWND hWnd,int is_stone,int *ScreenStatus)
{
	KillTimer(hWnd, Timer_ID_Start);
	KillTimer(hWnd, Timer_ID_Second);

	if (is_stone == -1);
	else if (is_stone % 2 == 0)
	{
		MessageBox(0, L"�浹 �¸�", L"�¸�", MB_OK);
	}
	else
	{
		MessageBox(0, L"�鵹 �¸�", L"�¸�", MB_OK);
	}

	*ScreenStatus = StartScreen;

	InvalidateRect(hWnd, NULL, false);
}
