#include "AI.h"

using namespace std;

// AI_board 를 0으로 초기화
void Reset_Board(vector<vector<int>>& board)
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            board[i][j] = 0;
        }
    }
}

// 한칸 기준으로 가중치 저장
void OneAdd(vector<vector<int>> &Temp_board, vector<vector<int>>& Bg_Check, int Who_Turn)
{
    // 방향
    int dx[8] = { 1,1,0,-1,-1,-1,0,1 };
    int dy[8] = { 0,1,1,1,0,-1,-1,-1 };

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            for (int dir = 0; dir < 8; dir++)
            {
                // 놓인 수가 없다면 continue
                if (Bg_Check[x][y] == 0) continue;

                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (nx < 0 || nx >= 16 || ny < 0 || ny >= 16) continue;
                if (Bg_Check[nx][ny] > 0) continue;
                
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
void ThreeAdd(vector<vector<int>>& Temp_board, vector<vector<int>>& Bg_Check, int stone_num, int Who_Turn)
{
    // 방향
    int dx[8] = { 1,1,0,-1,-1,-1,0,1 };
    int dy[8] = { 0,1,1,1,0,-1,-1,-1 };

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            // 돌이 없다면 continue
            if (Bg_Check[x][y] == 0) continue;
            
            // 돌이 어떤 돌인지
            int What_Stone;
            if (Bg_Check[x][y] == 1) What_Stone = 1;
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
                    int left_x = x + dx[dir] * left;
                    int left_y = y + dy[dir] * left;

                    // 조건에 충족한다면
                    if (left_x >= 0 && left_x < 16 && left_y >= 0 && left_y < 16)
                    {
                        if (Bg_Check[left_x][left_y] == What_Stone) is_ok_left++;
                        else break;
                    }
                }

                for (int right = 1; right < stone_num; right++)
                {
                    // 현재 돌을 기준으로 오른쪽에 돌이 몇개 있는가
                    int right_x = x + dx[(dir + 4) % 8] * right;
                    int right_y = y + dy[(dir + 4) % 8] * right;

                    // 조건에 충족한다면
                    if (right_x >= 0 && right_x < 16 && right_y >= 0 && right_y < 16)
                    {
                        if (Bg_Check[right_x][right_y] == What_Stone) is_ok_right++;
                        else break;
                    }
                }

                // 돌이 3개 혹은 4개가 연속으로 있을 경우
                if (is_ok_left + is_ok_right == stone_num - 1)
                {
                    int add_left_x = x + dx[dir] * (is_ok_left + 1);
                    int add_left_y = y + dy[dir] * (is_ok_left + 1);
                    int add_right_x = x + dx[(dir + 4) % 8] * (is_ok_right + 1);
                    int add_right_y = y + dy[(dir + 4) % 8] * (is_ok_right + 1);

                    if (add_left_x < 0 || add_left_x >= 16 || add_left_y < 0 || add_left_y >= 16)       continue;
                    if (add_right_x < 0 || add_right_x >= 16 || add_right_y < 0 || add_right_y >= 16)   continue;

                    // 3개일 경우
                    if (stone_num == 3)
                    {
                        // 양쪽이 다 돌이 없는 경우
                        if (Bg_Check[add_left_x][add_left_y] == 0 && Bg_Check[add_right_x][add_right_y] == 0)
                        {
                            if (add_left_x + dx[dir] >= 0 && add_left_x + dx[dir] < 16 && add_left_y + dx[dir] >= 0 && add_left_y + dy[dir] < 16)
                            {
                                if (Bg_Check[add_left_x + dx[dir]][add_left_y + dy[dir]] == 0)
                                {
                                    (Who_Turn % 2 == 0) ? Temp_board[add_left_x][add_left_y] += 50 : Temp_board[add_left_x][add_left_y] -= 50;
                                }
                            }
                            
                            if (add_right_x + dx[(dir + 4) % 8] >= 0 && add_right_x + dx[(dir + 4) % 8] < 16 &&
                                add_right_y + dy[(dir + 4) % 8] >= 0 && add_right_y + dy[(dir + 4) % 8] < 16)
                            if (Bg_Check[add_right_x + dx[(dir + 4) % 8]][add_right_y + dy[(dir + 4) % 8]] == 0)
                            {
                                (Who_Turn % 2 == 0) ? Temp_board[add_right_x][add_right_y] += 50 : Temp_board[add_right_x][add_right_y] -= 50;
                            }
                        }
                        else
                        {
                            if (add_left_x + dx[dir] >= 0 && add_left_x + dx[dir] < 16 && add_left_y + dy[dir] >= 0 && add_left_y + dy[dir] < 16)
                            {
                                if (Bg_Check[add_left_x + dx[dir]][add_left_y + dy[dir]] == 0 && Bg_Check[add_left_x][add_left_y] == 0)
                                {
                                    (Who_Turn % 2 == 0) ? Temp_board[add_left_x][add_left_y] += 1 : Temp_board[add_left_x][add_left_y] -= 1;
                                }
                            }

                            if (add_right_x + dx[(dir + 4) % 8] >= 0 && add_right_x + dx[(dir + 4) % 8] < 16 &&
                                add_right_y + dy[(dir + 4) % 8] >= 0 && add_right_y + dy[(dir + 4) % 8] < 16)
                            {
                                if (Bg_Check[add_right_x + dx[(dir + 4) % 8]][add_right_y + dy[(dir + 4) % 8]] == 0 && Bg_Check[add_right_x][add_right_y] == 0)
                                {
                                    (Who_Turn % 2 == 0) ? Temp_board[add_right_x][add_right_y] += 1 : Temp_board[add_right_x][add_right_y] = -1;
                                }
                            }
                        }
                    }
                    else    // 4개일 경우
                    {

                        if (Bg_Check[add_left_x][add_left_y] == 0)
                        {
                            (Who_Turn % 2 == 0) ? Temp_board[add_left_x][add_left_y] += 100 : Temp_board[add_left_x][add_left_y] -= 100;

                        }

                        if (Bg_Check[add_right_x][add_right_y] == 0)
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
void Two_OneAdd(vector<vector<int>>& Temp_board, vector<vector<int>>& Bg_Check)
{
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            
            if (Bg_Check[x][y] != 0) continue;
            
            for (int what_stone = 1; what_stone <= 2; what_stone++)
            {
                if (is_Cheking_Stone(Bg_Check, x, y, 4, what_stone) == true)
                {
                    (what_stone == 1) ? Temp_board[x][y] = -100 : Temp_board[x][y] = -100;
                }
            }

            for (int what_stone = 1; what_stone <= 2; what_stone++)
            {
                if (is_Cheking_Stone(Bg_Check, x, y, 5, what_stone) == true)
                {
                    (what_stone == 1) ? Temp_board[x][y] = -INF : Temp_board[x][y] = -INF;
                }
            }

        }
    }
}

bool is_Cheking_Stone(vector<vector<int>>& Bg_Check,int curr_x, int curr_y, int num, int what_stone)
{
    // 방향
    int dx[8] = { 1,1,0,-1,-1,-1,0,1 };
    int dy[8] = { 0,1,1,1,0,-1,-1,-1 };

    for (int dir = 0; dir < 4; dir++)
    {
        int nx = INF, ny = INF;
        int Stone_num = 0;
        int left_distance = 0, right_distance = 0;

        for (int direct = 1; direct <= num; direct++)
        {
            nx = curr_x + dx[dir] * direct;
            ny = curr_y + dy[dir] * direct;

            if (nx >= 0 && nx < 16 && ny >= 0 && ny < 16)
            {
                if (Bg_Check[nx][ny] == what_stone)
                {
                    Stone_num++;
                    left_distance++;
                }
                else break;
            }

        }

        for (int direct = 1; direct <= num; direct++)
        {
            nx = curr_x + dx[(dir + 4) % 8] * direct;
            ny = curr_y + dy[(dir + 4) % 8] * direct;

            if (nx >= 0 && nx < 16 && ny >= 0 && ny < 16)
            {
                if (Bg_Check[nx][ny] == what_stone)
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

void Ready_AI(vector<vector<int>>& AI_board, vector<vector<int>>& Bg_Check,int who_Turn)
{

    priority_queue<int> progress;

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            // 가중치가 0이면 제외
            if (AI_board[x][y] == 0) continue;

            (who_Turn % 2 == 0) ? progress.push(-AI_board[x][y]) : progress.push(AI_board[x][y]);
        }
    }

    while (!progress.empty())
    {

    }
}

void Running_AI(vector<vector<int>> Temp_board, vector<vector<int>> Bg_Check, vector<vector<int>>& Final_board, int who_Turn)
{
    if (who_Turn > Search_number) return;

    
}
