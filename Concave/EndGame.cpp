#include "EndGame.h"

void EndGame(HWND hWnd,int is_stone,int *ScreenStatus)
{
	// 타이머 죽임
	KillTimer(hWnd, Timer_ID_Start);
	KillTimer(hWnd, Timer_ID_Second);

	// 승리 처리
	if (is_stone == -1);
	else if (is_stone % 2 == 0)
	{
		MessageBox(hWnd, L"흑돌 승리", L"승리", MB_OK);
	}
	else
	{
		MessageBox(hWnd, L"백돌 승리", L"승리", MB_OK);
	}

	// 스크린 상태를 Start 상태로 변경
	*ScreenStatus = StartScreen;
	InvalidateRect(hWnd, NULL, false);
}
