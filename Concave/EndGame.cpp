#include "EndGame.h"

void EndGame(HWND hWnd,int is_stone,int *ScreenStatus)
{
	// Ÿ�̸� ����
	KillTimer(hWnd, Timer_ID_Start);
	KillTimer(hWnd, Timer_ID_Second);

	// �¸� ó��
	if (is_stone == -1);
	else if (is_stone % 2 == 0)
	{
		MessageBox(hWnd, L"�浹 �¸�", L"�¸�", MB_OK);
	}
	else
	{
		MessageBox(hWnd, L"�鵹 �¸�", L"�¸�", MB_OK);
	}

	// ��ũ�� ���¸� Start ���·� ����
	*ScreenStatus = StartScreen;
	InvalidateRect(hWnd, NULL, false);
}
