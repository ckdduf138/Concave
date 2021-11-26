#pragma once
#include "Concave.h"

#include <queue>

using namespace std;

#define Search_number 2

// AI_board 를 0으로 초기화
void Reset_Board(vector<vector<int>> &board);

// 한칸 기준으로 가중치 저장
void OneAdd(vector<vector<int>>& Temp_board, vector<vector<int>>& Bg_Check, int Who_Turn);

// 3개 이상 일때 가중치 증가
void ThreeAdd(vector<vector<int>>& Temp_board, vector<vector<int>>& Bg_Check, int stone_num, int Who_Turn);

// 2 - 1 일때 가중치 증가 -> 돌 하나를 놓았을때 사목이 되면 가중치 증가
void Two_OneAdd(vector<vector<int>>& Temp_board, vector<vector<int>>& Bg_Check);

// N목이 되었는지 체크하는 함수
bool is_Cheking_Stone(vector<vector<int>>& Bg_Check, int curr_x, int curr_y, int num, int what_stone);

//
void Ready_AI(vector<vector<int>>& AI_board, vector<vector<int>>& Bg_Check,int who_Turn);

// 
void Running_AI(vector<vector<int>> Temp_board, vector<vector<int>> Bg_Check, vector<vector<int>>& Final_board, int who_Turn);


//// STACK에 가중치값 저장
//void AI_Ready(vector<vector<int>>& value_board, stack<pair<int, int>>& AI_STACK);
//
//bool Running_AI(vector<vector<int>> Temp_board, vector<vector<int>> Temp_Check, vector<vector<int>>& AI_board, int Who_Turn, int embroider_cnt);
//
//// 가장 큰 값 찾기
//void MaxValue(vector<vector<int>>& value_board);