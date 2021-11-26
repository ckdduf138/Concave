#pragma once

#include "Concave.h"

using namespace std;

#define BackgroundRGB RGB(192, 128, 59)		// ��� ��
#define Background_Start_X 180				// �ٵ��� ���� ��ġ X
#define Background_Start_Y 30				// �ٵ��� ���� ��ġ Y
#define OneSpace 40							// �ٵ��� ��ĭ ũ��

void PaintBoard(HDC hdc);                                  // ������ �׸��� �Լ�
void SetBackgroundRect(vector<vector<RECT>> &Bg_Rect);          // ���� �����ϴ� �Լ�
