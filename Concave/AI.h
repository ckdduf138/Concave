#pragma once
#include "Concave.h"
#include <queue>

using namespace std;

#define Search_number 30

// 돌 가중치 설정

// 한칸 기준
#define weight_one 2

// 두칸 기준
#define weight_two 1

// 2 - 1 하나 놓았을때 4개가 되는 기준
#define weight_three 50

// 4개인 경우 -> 하나 놓으면 오목
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

// 오름차순 정렬
struct sortcompareAsc {
	bool operator()(const WeightInfo& A, const WeightInfo& B) {
		return A.value > B.value;
	}
};

// 내림차순 정렬
struct sortcompareDesc {
	bool operator()(const WeightInfo& A, const WeightInfo& B) {
		return A.value < B.value;
	}
};

// 오목 돌 세팅
void SetBoard(vector<vector<int>> Bg_Check);

// 가중치 증가
void WeightAdd(vector<vector<int>>& weightBoard);

// 한칸 기준으로 가중치 저장
void OneAdd(vector<vector<int>>& Temp_board);

// 두칸 기준으로 가중치 저장
void TwoAdd(vector<vector<int>>& weightBoard);

// 3개일때 가중치 증가
void ThreeAdd(vector<vector<int>>& weightBoard);

// 4개일때 가중치 증가
void FourAdd(vector<vector<int>>& weightBoard);

// 2 - 1 일때 가중치 증가 -> 돌 하나를 놓았을때 사목이 되면 가중치 증가
void Two_OneAdd(vector<vector<int>>& weightBoard);

// N목이 되었는지 체크하는 함수
bool is_Cheking_Stone(int curr_x, int curr_y, int num, int what_stone);

// AI 시작
pair<int, int> Running_AI(vector<vector<int>> weightBoard, vector<vector<int>>& stoneBoard, int whoTurn);