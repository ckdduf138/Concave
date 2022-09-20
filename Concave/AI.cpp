#include "AI.h"

// 남쪽부터 시작
int dirX[8] = { 1,1,0,-1,-1,-1,0,1 };
int dirY[8] = { 0,1,1,1,0,-1,-1,-1 };

vector<vector<int>> stronCheck(16, vector<int>(16));      // 바둑알이 있는지 check하는 벡터

pair<int, int> Running_AI(vector<vector<int>> weightBoard, vector<vector<int>>& stoneBoard, int whoTurn)
{
    WeightAdd(weightBoard);

    // 가중치 값 오름차순
    priority_queue<WeightInfo, vector<WeightInfo>, sortcompareAsc> minValue;

    // 가중치 값 내림차순
    priority_queue<WeightInfo, vector<WeightInfo>, sortcompareDesc> maxValue;

    // 가중치 저장
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            minValue.push({ x,y,weightBoard[x][y] });
            maxValue.push({ x,y,weightBoard[x][y] });
        }
    }
    
    WeightInfo minV;
    WeightInfo maxV;

    while (!minValue.empty())
    {
        minV = minValue.top();

        if (stronCheck[minV.x][minV.y] == 0) break;

        minValue.pop();
    }

    while (!maxValue.empty())
    {
        maxV = maxValue.top();

        if (stronCheck[maxV.x][maxV.y] == 0) break;

        maxValue.pop();
    }

    return abs(minV.value) > abs(maxV.value) ? pair<int, int>{minV.x, minV.y} : pair<int, int>{ maxV.x, maxV.y };
}


void SetBoard(vector<vector<int>> _stronCheck)
{
    stronCheck = _stronCheck;
}

void WeightAdd(vector<vector<int>>& weightBoard)
{
    // [가중치 증가]
    // 흑돌일 경우 가중치가 가장 낮은 곳이 최적의 위치
    // 백돌일 경우 가중치가 가장 높은 곳이 최적의 위치

    // 한칸 기준으로 가중치 저장
    OneAdd(weightBoard);

    // 두칸 기준으로 가중치 저장
    TwoAdd(weightBoard);

    // 2 - 1 일때 가중치 증가 -> 돌 하나를 놓았을때 사목이 되면 가중치 증가
    Two_OneAdd(weightBoard);

    // 3개 일때 가중치 증가 -> 돌 하나를 놓았을때 사목이 되면 가중치 증가
    ThreeAdd(weightBoard);

    // 4개 일때 가중치 증가 -> 돌 하나를 놓았을때 오목이 되면 가중치 증가
    FourAdd(weightBoard);
}

// 한칸 기준으로 가중치 저장
void OneAdd(vector<vector<int>> &weightBoard)
{
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            // 놓인 수가 없다면 continue
            if (stronCheck[x][y] == 0) continue;

            for (int dir = 0; dir < 8; dir++)
            {
                int nx = x + dirX[dir];
                int ny = y + dirY[dir];
                
                if (nx < 0 || nx >= 16 || ny < 0 || ny >= 16)   continue; // 범위 밖이면 continue            
                if (stronCheck[nx][ny] > 0)                     continue; // 돌이 이미 놓여 있다면
                
                // 흑돌(1)일 경우 + 백돌(2)일 경우 -
                weightBoard[nx][ny] += (stronCheck[x][y] == 1) ? weight_one * -1 : weight_one;
            }
        }
    }
}

// 두칸 기준으로 가중치 저장
void TwoAdd(vector<vector<int>>& weightBoard)
{
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            // 놓인 수가 없다면 continue
            if (stronCheck[x][y] == 0) continue;

            for (int dir = 0; dir < 8; dir++)
            {
                int nx = x + dirX[dir] * 2;
                int ny = y + dirY[dir] * 2;

                if (nx < 0 || nx >= 16 || ny < 0 || ny >= 16)   continue; // 범위 밖이면 continue            
                if (stronCheck[nx][ny] > 0)                     continue; // 돌이 이미 놓여 있다면

                // 흑돌(1)일 경우 + 백돌(2)일 경우 -
                weightBoard[nx][ny] += (stronCheck[x][y] == 1) ? weight_two * -1 : weight_two;
            }
        }
    }
}

// 2 - 1 일때 가중치 증가 -> 돌 하나를 놓았을때 사목이 되면 가중치 증가
void Two_OneAdd(vector<vector<int>>& weightBoard)
{
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            // 돌이 이미 있다면 continue..
            if (stronCheck[x][y] != 0) continue;

            for (int what_stone = 1; what_stone <= 2; what_stone++)
            {
                if (is_Cheking_Stone(x, y, 4, what_stone))
                {
                    weightBoard[x][y] += (what_stone == 1) ? weight_three * -1: weight_three;
                }
            }
        }
    }
}

// 3개일때 가중치 증가
void ThreeAdd(vector<vector<int>>& weightBoard)
{
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            // 돌이 없다면 continue..
            if (stronCheck[x][y] == 0) continue;

            for (int dir = 0; dir < 4; dir++)
            {
                // x, y 를 기준으로 한칸 위치한 돌
                StonePos left_one = { x + dirX[dir], y + dirY[dir] };
                StonePos right_one = { x + dirX[(dir + 4) % 8], y + dirY[(dir + 4) % 8] };

                // x, y 를 기준으로 두칸 위치한 돌
                StonePos left_two = { x + dirX[dir] * 2, y + dirY[dir] * 2 };
                StonePos right_two = { x + dirX[(dir + 4) % 8] * 2, y + dirY[(dir + 4) % 8] * 2 };

                // 같은 색으로 3개 만들어졌을경우
                if (stronCheck[x][y] == stronCheck[left_one.x][left_one.y] && stronCheck[x][y] == stronCheck[right_one.x][right_one.y])
                {
                    // 3개를 만들었으나 양쪽 돌이 다른색이면 continue..
                    if (stronCheck[x][y] == stronCheck[left_one.x][left_one.y] + 1 % 2 && stronCheck[x][y] == stronCheck[right_one.x][right_one.y] + 1 % 2)
                    {
                        continue;
                    }

                    // 오직 3개
                    if (stronCheck[left_two.x][left_two.y] == 0 && stronCheck[right_two.x][right_two.y] == 0)
                    {
                        weightBoard[left_two.x][left_two.y] += (stronCheck[x][y] == 1) ? weight_three * -1 : weight_three;
                        weightBoard[right_two.x][right_two.y] += (stronCheck[x][y] == 1) ? weight_three * -1 : weight_three;
                    }
                    else
                    {
                        weightBoard[left_two.x][left_two.y] += (stronCheck[x][y] == 1) ? weight_one * -1 : weight_one;
                        weightBoard[right_two.x][right_two.y] += (stronCheck[x][y] == 1) ? weight_one * -1 : weight_one;
                    }
                }
            }
        }
    }
}

// 4개일때 가중치 증가
void FourAdd(vector<vector<int>>& weightBoard)
{
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            // 돌이 이미 있다면 continue..
            if (stronCheck[x][y] != 0) continue;

            for (int what_stone = 1; what_stone <= 2; what_stone++)
            {
                if (is_Cheking_Stone(x, y, 5, what_stone))
                {
                    weightBoard[x][y] += (what_stone == 1) ? weight_four * -1 : weight_four;
                }
            }
        }
    }
}

bool is_Cheking_Stone(int curr_x, int curr_y, int num, int what_stone)
{
    for (int dir = 0; dir < 4; dir++)
    {
        int nx = INF, ny = INF;
        int Stone_num = 0;
        int left_distance = 0, right_distance = 0;

        for (int direct = 1; direct <= num; direct++)
        {
            nx = curr_x + dirX[dir] * direct;
            ny = curr_y + dirY[dir] * direct;

            if (nx >= 0 && nx < 16 && ny >= 0 && ny < 16)
            {
                if (stronCheck[nx][ny] == what_stone)
                {
                    Stone_num++;
                    left_distance++;
                }
                else break;
            }

        }

        for (int direct = 1; direct <= num; direct++)
        {
            nx = curr_x + dirX[(dir + 4) % 8] * direct;
            ny = curr_y + dirY[(dir + 4) % 8] * direct;

            if (nx >= 0 && nx < 16 && ny >= 0 && ny < 16)
            {
                if (stronCheck[nx][ny] == what_stone)
                {
                    Stone_num++;
                    right_distance++;
                }
                else break;
            }
        }

        // 완성
        if (Stone_num == num - 1)
        {
            return true;
        }
        else
        {
            Stone_num = 0;
        }
    }
    return false;
}