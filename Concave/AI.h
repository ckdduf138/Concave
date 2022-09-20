#pragma once
#include "Concave.h"
#include <queue>

using namespace std;

#define Search_number 30

// �� ����ġ ����

// ��ĭ ����
#define weight_one 2

// ��ĭ ����
#define weight_two 1

// 2 - 1 �ϳ� �������� 4���� �Ǵ� ����
#define weight_three 50

// 4���� ��� -> �ϳ� ������ ����
#define weight_four 5000

struct StonePos {
	int x;
	int y;
};

struct WeightInfo {
	int x;
	int y;
	int value;
};

// �������� ����
struct sortcompareAsc {
	bool operator()(const WeightInfo& A, const WeightInfo& B) {
		return A.value > B.value;
	}
};

// �������� ����
struct sortcompareDesc {
	bool operator()(const WeightInfo& A, const WeightInfo& B) {
		return A.value < B.value;
	}
};

// ���� �� ����
void SetBoard(vector<vector<int>> Bg_Check);

// ����ġ ����
void WeightAdd(vector<vector<int>>& weightBoard);

// ��ĭ �������� ����ġ ����
void OneAdd(vector<vector<int>>& Temp_board);

// ��ĭ �������� ����ġ ����
void TwoAdd(vector<vector<int>>& weightBoard);

// 3���϶� ����ġ ����
void ThreeAdd(vector<vector<int>>& weightBoard);

// 4���϶� ����ġ ����
void FourAdd(vector<vector<int>>& weightBoard);

// 2 - 1 �϶� ����ġ ���� -> �� �ϳ��� �������� ����� �Ǹ� ����ġ ����
void Two_OneAdd(vector<vector<int>>& weightBoard);

// N���� �Ǿ����� üũ�ϴ� �Լ�
bool is_Cheking_Stone(int curr_x, int curr_y, int num, int what_stone);

// AI ����
pair<int, int> Running_AI(vector<vector<int>> weightBoard, vector<vector<int>>& stoneBoard, int whoTurn);