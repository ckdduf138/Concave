#pragma once
#include "Concave.h"

#include <queue>

using namespace std;

#define Search_number 2

// AI_board �� 0���� �ʱ�ȭ
void Reset_Board(vector<vector<int>> &board);

// ��ĭ �������� ����ġ ����
void OneAdd(vector<vector<int>>& Temp_board, vector<vector<int>>& Bg_Check, int Who_Turn);

// 3�� �̻� �϶� ����ġ ����
void ThreeAdd(vector<vector<int>>& Temp_board, vector<vector<int>>& Bg_Check, int stone_num, int Who_Turn);

// 2 - 1 �϶� ����ġ ���� -> �� �ϳ��� �������� ����� �Ǹ� ����ġ ����
void Two_OneAdd(vector<vector<int>>& Temp_board, vector<vector<int>>& Bg_Check);

// N���� �Ǿ����� üũ�ϴ� �Լ�
bool is_Cheking_Stone(vector<vector<int>>& Bg_Check, int curr_x, int curr_y, int num, int what_stone);

//
void Ready_AI(vector<vector<int>>& AI_board, vector<vector<int>>& Bg_Check,int who_Turn);

// 
void Running_AI(vector<vector<int>> Temp_board, vector<vector<int>> Bg_Check, vector<vector<int>>& Final_board, int who_Turn);


//// STACK�� ����ġ�� ����
//void AI_Ready(vector<vector<int>>& value_board, stack<pair<int, int>>& AI_STACK);
//
//bool Running_AI(vector<vector<int>> Temp_board, vector<vector<int>> Temp_Check, vector<vector<int>>& AI_board, int Who_Turn, int embroider_cnt);
//
//// ���� ū �� ã��
//void MaxValue(vector<vector<int>>& value_board);