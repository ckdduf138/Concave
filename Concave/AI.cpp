#include "AI.h"

using namespace std;

// AI_board �� 0���� �ʱ�ȭ
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

// ��ĭ �������� ����ġ ����
void OneAdd(vector<vector<int>> &Temp_board, vector<vector<int>>& Bg_Check, int Who_Turn)
{
    // ����
    int dx[8] = { 1,1,0,-1,-1,-1,0,1 };
    int dy[8] = { 0,1,1,1,0,-1,-1,-1 };

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            for (int dir = 0; dir < 8; dir++)
            {
                // ���� ���� ���ٸ� continue
                if (Bg_Check[x][y] == 0) continue;

                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (nx < 0 || nx >= 16 || ny < 0 || ny >= 16) continue;
                if (Bg_Check[nx][ny] > 0) continue;
                
                // �浹�� ��� + �鵹�� ��� -
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

// 3�� �̻� �϶� ����ġ ����
void ThreeAdd(vector<vector<int>>& Temp_board, vector<vector<int>>& Bg_Check, int stone_num, int Who_Turn)
{
    // ����
    int dx[8] = { 1,1,0,-1,-1,-1,0,1 };
    int dy[8] = { 0,1,1,1,0,-1,-1,-1 };

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            // ���� ���ٸ� continue
            if (Bg_Check[x][y] == 0) continue;
            
            // ���� � ������
            int What_Stone;
            if (Bg_Check[x][y] == 1) What_Stone = 1;
            else                     What_Stone = 2;

            // ���� 
            for (int dir = 0; dir < 4; dir++)
            {
                // ���� 3�� Ȥ�� 4���� ����� ���°�
                int is_ok_left = 0;
                int is_ok_right = 0;

                for (int left = 1; left < stone_num; left++)
                {
                    // ���� ���� �������� ���ʿ� ���� � �ִ°�
                    int left_x = x + dx[dir] * left;
                    int left_y = y + dy[dir] * left;

                    // ���ǿ� �����Ѵٸ�
                    if (left_x >= 0 && left_x < 16 && left_y >= 0 && left_y < 16)
                    {
                        if (Bg_Check[left_x][left_y] == What_Stone) is_ok_left++;
                        else break;
                    }
                }

                for (int right = 1; right < stone_num; right++)
                {
                    // ���� ���� �������� �����ʿ� ���� � �ִ°�
                    int right_x = x + dx[(dir + 4) % 8] * right;
                    int right_y = y + dy[(dir + 4) % 8] * right;

                    // ���ǿ� �����Ѵٸ�
                    if (right_x >= 0 && right_x < 16 && right_y >= 0 && right_y < 16)
                    {
                        if (Bg_Check[right_x][right_y] == What_Stone) is_ok_right++;
                        else break;
                    }
                }

                // ���� 3�� Ȥ�� 4���� �������� ���� ���
                if (is_ok_left + is_ok_right == stone_num - 1)
                {
                    int add_left_x = x + dx[dir] * (is_ok_left + 1);
                    int add_left_y = y + dy[dir] * (is_ok_left + 1);
                    int add_right_x = x + dx[(dir + 4) % 8] * (is_ok_right + 1);
                    int add_right_y = y + dy[(dir + 4) % 8] * (is_ok_right + 1);

                    if (add_left_x < 0 || add_left_x >= 16 || add_left_y < 0 || add_left_y >= 16)       continue;
                    if (add_right_x < 0 || add_right_x >= 16 || add_right_y < 0 || add_right_y >= 16)   continue;

                    // 3���� ���
                    if (stone_num == 3)
                    {
                        // ������ �� ���� ���� ���
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
                    else    // 4���� ���
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

// 2 - 1 �϶� ����ġ ���� -> �� �ϳ��� �������� ����� �Ǹ� ����ġ ����
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
    // ����
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

        // �ϼ�
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
            // ����ġ�� 0�̸� ����
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
