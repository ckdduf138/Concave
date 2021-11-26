#include "Background.h"

// Background를 그리는 함수
void PaintBoard(HDC hdc)
{
    HBRUSH myBrush = (HBRUSH)CreateSolidBrush(BackgroundRGB);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

    Rectangle(hdc, 180, 30, 820, 670);

    myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            RECT r = { 200 + i * 40,50 + j * 40,r.left + 40,r.top + 40 };
            Rectangle(hdc, r.left, r.top, r.right, r.bottom);
        }
    }

    SelectObject(hdc, oldBrush);
    DeleteObject(myBrush);
    DeleteObject(oldBrush);
}

// 바둑 판 뒤 RECT 설정
void SetBackgroundRect(vector<vector<RECT>> &Bg_Rect)
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            int a = Background_Start_X + i * OneSpace;
            int b = Background_Start_Y + j * OneSpace;
            Bg_Rect[i][j] = { a,b,a + OneSpace,b + OneSpace };
        }
    }
}