#include "WindowSet.h"

// Window ȭ�� ��� ��ġ�� �ű�� �Լ�
void Center_Screen(HWND window, DWORD style, DWORD exStyle)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    RECT clientRect; GetClientRect(window, &clientRect);
    int clientWidth = clientRect.right - clientRect.left;
    int clientHeight = clientRect.bottom - clientRect.top;
    SetWindowPos(window, NULL, screenWidth / 2 - clientWidth / 2, screenHeight / 2 - clientHeight / 2 - 40, clientWidth, clientHeight, 0);
}