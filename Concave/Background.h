#pragma once

#include "Concave.h"

using namespace std;

#define BackgroundRGB RGB(192, 128, 59)		// 배경 색
#define Background_Start_X 180				// 바둑판 시작 위치 X
#define Background_Start_Y 30				// 바둑판 시작 위치 Y
#define OneSpace 40							// 바둑판 한칸 크기

void PaintBoard(HDC hdc);                                  // 오목판 그리는 함수
void SetBackgroundRect(vector<vector<RECT>> &Bg_Rect);          // 게임 세팅하는 함수
