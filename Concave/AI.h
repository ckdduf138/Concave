#pragma once
#include "Concave.h"

using namespace std;

#define Search_number 5

// �� ����ġ ����

// ��ĭ ����
#define weight_one 2

// ��ĭ ����
#define weight_two 1

// 2 - 1 �ϳ� �������� 4���� �Ǵ� ����
#define weight_three 50


struct StonePos {
	int x;
	int y;
};

// ���� �� ����
void SetBoard(vector<vector<int>> Bg_Check);

// ����ġ ����
void WeightAdd(vector<vector<int>>& weightBoard, int whoTurn);

// ��ĭ �������� ����ġ ����
void OneAdd(vector<vector<int>>& Temp_board);

// ��ĭ �������� ����ġ ����
void TwoAdd(vector<vector<int>>& weightBoard);

// 3�� �̻� �϶� ����ġ ����
void ThreeAdd(vector<vector<int>>& weightBoard);

// 2 - 1 �϶� ����ġ ���� -> �� �ϳ��� �������� ����� �Ǹ� ����ġ ����
void Two_OneAdd(vector<vector<int>>& weightBoard);

// N���� �Ǿ����� üũ�ϴ� �Լ�
bool is_Cheking_Stone(int curr_x, int curr_y, int num, int what_stone);

// 
void Running_AI(vector<vector<int>> &weightBoard, vector<vector<int>>& stoneBoard, int whoTurn);