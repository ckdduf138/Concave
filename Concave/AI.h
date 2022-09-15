#pragma once
#include "Concave.h"

using namespace std;

#define Search_number 20
#define weight_one 1

// 오목 돌 세팅
void SetBoard(vector<vector<int>> Bg_Check);

// 가중치 증가
void WeightAdd(vector<vector<int>>& weightBoard, int whoTurn);

// 한칸 기준으로 가중치 저장
void OneAdd(vector<vector<int>>& Temp_board);

// 3개 이상 일때 가중치 증가
void ThreeAdd(vector<vector<int>>& Temp_board, int stone_num, int whoTurn);

// 2 - 1 일때 가중치 증가 -> 돌 하나를 놓았을때 사목이 되면 가중치 증가
void Two_OneAdd(vector<vector<int>>& Temp_board);

// N목이 되었는지 체크하는 함수
bool is_Cheking_Stone(int curr_x, int curr_y, int num, int what_stone);

// 
void Running_AI(vector<vector<int>> &weightBoard, vector<vector<int>>& stoneBoard, int whoTurn);