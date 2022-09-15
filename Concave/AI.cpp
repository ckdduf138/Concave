#include "AI.h"

// 남쪽부터 시작
int dirX[8] = { 1,1,0,-1,-1,-1,0,1 };
int dirY[8] = { 0,1,1,1,0,-1,-1,-1 };

vector<vector<int>> stronCheck(16, vector<int>(16));      // 바둑알이 있는지 check하는 벡터

void Running_AI(vector<vector<int>> &weightBoard, vector<vector<int>>& stoneBoard, int whoTurn)
{
    WeightAdd(weightBoard, whoTurn);
}

void SetBoard(vector<vector<int>> _stronCheck)
{
    stronCheck = _stronCheck;
}

void WeightAdd(vector<vector<int>>& weightBoard, int whoTurn)
{
    // [가중치 증가]

    // 한칸 기준으로 가중치 저장
    OneAdd(weightBoard, whoTurn);

    // 2 - 1 일때 가중치 증가 -> 돌 하나를 놓았을때 사목이 되면 가중치 증가
    Two_OneAdd(weightBoard);

    // 3개 이상 일때 가중치 증가
    ThreeAdd(weightBoard, 3, whoTurn);

    // 4개 이상 일때 가중치 증가
    ThreeAdd(weightBoard, 4, whoTurn);
}

// 한칸 기준으로 가중치 저장
void OneAdd(vector<vector<int>> &Temp_board, int Who_Turn)
{

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            for (int dir = 0; dir < 8; dir++)
            {
                // 놓인 수가 없다면 continue
                if (stronCheck[x][y] == 0) continue;

                int nx = x + dirX[dir];
                int ny = y + dirY[dir];

                if (nx < 0 || nx >= 16 || ny < 0 || ny >= 16) continue;
                if (stronCheck[nx][ny] > 0) continue;
                
                // 흑돌일 경우 + 백돌일 경우 -
                if (Temp_board[nx][ny] == 0)
                {
                    (Who_Turn % 2 == 0) ? Temp_board[nx][ny] = 1 : Temp_board[nx][ny] = -1;
                }
                else
                {
                    (Who_Turn % 2 == 0) ? Temp_board[nx][ny]++ : Temp_board[nx][ny]--;
                }
            }
        }
    }
}

// 3개 이상 일때 가중치 증가
void ThreeAdd(vector<vector<int>>& Temp_board, int stone_num, int Who_Turn)
{
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            // 돌이 없다면 continue
            if (stronCheck[x][y] == 0) continue;
            
            // 돌이 어떤 돌인지
            int What_Stone;
            if (stronCheck[x][y] == 1) What_Stone = 1;
            else                     What_Stone = 2;

            // 방향 
            for (int dir = 0; dir < 4; dir++)
            {
                // 돌이 3개 혹은 4개가 만들어 졌는가
                int is_ok_left = 0;
                int is_ok_right = 0;

                for (int left = 1; left < stone_num; left++)
                {
                    // 현재 돌을 기준으로 왼쪽에 돌이 몇개 있는가
                    int left_x = x + dirX[dir] * left;
                    int left_y = y + dirY[dir] * left;

                    // 조건에 충족한다면
                    if (left_x >= 0 && left_x < 16 && left_y >= 0 && left_y < 16)
                    {
                        if (stronCheck[left_x][left_y] == What_Stone) is_ok_left++;
                        else break;
                    }
                }

                for (int right = 1; right < stone_num; right++)
                {
                    // 현재 돌을 기준으로 오른쪽에 돌이 몇개 있는가
                    int right_x = x + dirX[(dir + 4) % 8] * right;
                    int right_y = y + dirY[(dir + 4) % 8] * right;

                    // 조건에 충족한다면
                    if (right_x >= 0 && right_x < 16 && right_y >= 0 && right_y < 16)
                    {
                        if (stronCheck[right_x][right_y] == What_Stone) is_ok_right++;
                        else break;
                    }
                }

                // 돌이 3개 혹은 4개가 연속으로 있을 경우
                if (is_ok_left + is_ok_right == stone_num - 1)
                {
                    int add_left_x = x + dirX[dir] * (is_ok_left + 1);
                    int add_left_y = y + dirY[dir] * (is_ok_left + 1);
                    int add_right_x = x + dirX[(dir + 4) % 8] * (is_ok_right + 1);
                    int add_right_y = y + dirY[(dir + 4) % 8] * (is_ok_right + 1);

                    if (add_left_x < 0 || add_left_x >= 16 || add_left_y < 0 || add_left_y >= 16)       continue;
                    if (add_right_x < 0 || add_right_x >= 16 || add_right_y < 0 || add_right_y >= 16)   continue;

                    // 3개일 경우
                    if (stone_num == 3)
                    {
                        // 양쪽이 다 돌이 없는 경우
                        if (stronCheck[add_left_x][add_left_y] == 0 && stronCheck[add_right_x][add_right_y] == 0)
                        {
                            if (add_left_x + dirX[dir] >= 0 && add_left_x + dirX[dir] < 16 && add_left_y + dirX[dir] >= 0 && add_left_y + dirY[dir] < 16)
                            {
                                if (stronCheck[add_left_x + dirX[dir]][add_left_y + dirY[dir]] == 0)
                                {
                                    (Who_Turn % 2 == 0) ? Temp_board[add_left_x][add_left_y] += 50 : Temp_board[add_left_x][add_left_y] -= 50;
                                }
                            }
                            
                            if (add_right_x + dirX[(dir + 4) % 8] >= 0 && add_right_x + dirX[(dir + 4) % 8] < 16 &&
                                add_right_y + dirY[(dir + 4) % 8] >= 0 && add_right_y + dirY[(dir + 4) % 8] < 16)
                            if (stronCheck[add_right_x + dirX[(dir + 4) % 8]][add_right_y + dirY[(dir + 4) % 8]] == 0)
                            {
                                (Who_Turn % 2 == 0) ? Temp_board[add_right_x][add_right_y] += 50 : Temp_board[add_right_x][add_right_y] -= 50;
                            }
                        }
                        else
                        {
                            if (add_left_x + dirX[dir] >= 0 && add_left_x + dirX[dir] < 16 && add_left_y + dirY[dir] >= 0 && add_left_y + dirY[dir] < 16)
                            {
                                if (stronCheck[add_left_x + dirX[dir]][add_left_y + dirY[dir]] == 0 && stronCheck[add_left_x][add_left_y] == 0)
                                {
                                    (Who_Turn % 2 == 0) ? Temp_board[add_left_x][add_left_y] += 1 : Temp_board[add_left_x][add_left_y] -= 1;
                                }
                            }

                            if (add_right_x + dirX[(dir + 4) % 8] >= 0 && add_right_x + dirX[(dir + 4) % 8] < 16 &&
                                add_right_y + dirY[(dir + 4) % 8] >= 0 && add_right_y + dirY[(dir + 4) % 8] < 16)
                            {
                                if (stronCheck[add_right_x + dirX[(dir + 4) % 8]][add_right_y + dirY[(dir + 4) % 8]] == 0 && stronCheck[add_right_x][add_right_y] == 0)
                                {
                                    (Who_Turn % 2 == 0) ? Temp_board[add_right_x][add_right_y] += 1 : Temp_board[add_right_x][add_right_y] = -1;
                                }
                            }
                        }
                    }
                    else    // 4개일 경우
                    {

                        if (stronCheck[add_left_x][add_left_y] == 0)
                        {
                            (Who_Turn % 2 == 0) ? Temp_board[add_left_x][add_left_y] += 100 : Temp_board[add_left_x][add_left_y] -= 100;

                        }

                        if (stronCheck[add_right_x][add_right_y] == 0)
                        {
                            (Who_Turn % 2 == 0) ? Temp_board[add_right_x][add_right_y] += 100 : Temp_board[add_right_x][add_right_y] -= 100;
                        }
                    }

                }

            }
        }
    }
}

// 2 - 1 일때 가중치 증가 -> 돌 하나를 놓았을때 사목이 되면 가중치 증가
void Two_OneAdd(vector<vector<int>>& Temp_board)
{
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            
            if (stronCheck[x][y] != 0) continue;
            
            for (int what_stone = 1; what_stone <= 2; what_stone++)
            {
                if (is_Cheking_Stone(x, y, 4, what_stone) == true)
                {
                    (what_stone == 1) ? Temp_board[x][y] = -100 : Temp_board[x][y] = -100;
                }
            }

            for (int what_stone = 1; what_stone <= 2; what_stone++)
            {
                if (is_Cheking_Stone(x, y, 5, what_stone) == true)
                {
                    (what_stone == 1) ? Temp_board[x][y] = -INF : Temp_board[x][y] = -INF;
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