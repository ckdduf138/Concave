#pragma once
//#pragma comment(lib, "msimg32.lib")

#include <Windows.h>
#include <vector>
#include <time.h>
#include <stack>

#include "resource.h"

#include "WindowSet.h"
#include "Background.h"
#include "EndGame.h"
#include "AI.h"

using namespace std;

#define StartScreen		1000
#define GameScreen		2000
#define AIScreen		3000

#define INF 987654321
#define Undefined 999999999

bool is_Cheking_FiveStone(int curr_x, int curr_y, int num);     // 오목이 되었는지 체크하는 함수