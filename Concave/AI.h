#pragma once
#include "Concave.h"

using namespace std;

#define Search_number 20
#define weight_one 1

// ���� �� ����
void SetBoard(vector<vector<int>> Bg_Check);

// ����ġ ����
void WeightAdd(vector<vector<int>>& weightBoard, int whoTurn);

// ��ĭ �������� ����ġ ����
void OneAdd(vector<vector<int>>& Temp_board);

// 3�� �̻� �϶� ����ġ ����
void ThreeAdd(vector<vector<int>>& Temp_board, int stone_num, int whoTurn);

// 2 - 1 �϶� ����ġ ���� -> �� �ϳ��� �������� ����� �Ǹ� ����ġ ����
void Two_OneAdd(vector<vector<int>>& Temp_board);

// N���� �Ǿ����� üũ�ϴ� �Լ�
bool is_Cheking_Stone(int curr_x, int curr_y, int num, int what_stone);

// 
void Running_AI(vector<vector<int>> &weightBoard, vector<vector<int>>& stoneBoard, int whoTurn);