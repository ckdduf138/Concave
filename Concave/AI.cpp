#include "AI.h"

// ���ʺ��� ����
int dirX[8] = { 1,1,0,-1,-1,-1,0,1 };
int dirY[8] = { 0,1,1,1,0,-1,-1,-1 };

vector<vector<int>> stronCheck(16, vector<int>(16));      // �ٵϾ��� �ִ��� check�ϴ� ����

pair<int, int> Running_AI(vector<vector<int>> weightBoard, vector<vector<int>>& stoneBoard, int whoTurn)
{
    WeightAdd(weightBoard);

    // ����ġ �� ��������
    priority_queue<WeightInfo, vector<WeightInfo>, sortcompareAsc> minValue;

    // ����ġ �� ��������
    priority_queue<WeightInfo, vector<WeightInfo>, sortcompareDesc> maxValue;

    // ����ġ ����
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
    // [����ġ ����]
    // �浹�� ��� ����ġ�� ���� ���� ���� ������ ��ġ
    // �鵹�� ��� ����ġ�� ���� ���� ���� ������ ��ġ

    // ��ĭ �������� ����ġ ����
    OneAdd(weightBoard);

    // ��ĭ �������� ����ġ ����
    TwoAdd(weightBoard);

    // 2 - 1 �϶� ����ġ ���� -> �� �ϳ��� �������� ����� �Ǹ� ����ġ ����
    Two_OneAdd(weightBoard);

    // 3�� �϶� ����ġ ���� -> �� �ϳ��� �������� ����� �Ǹ� ����ġ ����
    ThreeAdd(weightBoard);

    // 4�� �϶� ����ġ ���� -> �� �ϳ��� �������� ������ �Ǹ� ����ġ ����
    FourAdd(weightBoard);
}

// ��ĭ �������� ����ġ ����
void OneAdd(vector<vector<int>> &weightBoard)
{
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            // ���� ���� ���ٸ� continue
            if (stronCheck[x][y] == 0) continue;

            for (int dir = 0; dir < 8; dir++)
            {
                int nx = x + dirX[dir];
                int ny = y + dirY[dir];
                
                if (nx < 0 || nx >= 16 || ny < 0 || ny >= 16)   continue; // ���� ���̸� continue            
                if (stronCheck[nx][ny] > 0)                     continue; // ���� �̹� ���� �ִٸ�
                
                // �浹(1)�� ��� + �鵹(2)�� ��� -
                weightBoard[nx][ny] += (stronCheck[x][y] == 1) ? weight_one * -1 : weight_one;
            }
        }
    }
}

// ��ĭ �������� ����ġ ����
void TwoAdd(vector<vector<int>>& weightBoard)
{
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            // ���� ���� ���ٸ� continue
            if (stronCheck[x][y] == 0) continue;

            for (int dir = 0; dir < 8; dir++)
            {
                int nx = x + dirX[dir] * 2;
                int ny = y + dirY[dir] * 2;

                if (nx < 0 || nx >= 16 || ny < 0 || ny >= 16)   continue; // ���� ���̸� continue            
                if (stronCheck[nx][ny] > 0)                     continue; // ���� �̹� ���� �ִٸ�

                // �浹(1)�� ��� + �鵹(2)�� ��� -
                weightBoard[nx][ny] += (stronCheck[x][y] == 1) ? weight_two * -1 : weight_two;
            }
        }
    }
}

// 2 - 1 �϶� ����ġ ���� -> �� �ϳ��� �������� ����� �Ǹ� ����ġ ����
void Two_OneAdd(vector<vector<int>>& weightBoard)
{
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            // ���� �̹� �ִٸ� continue..
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

// 3���϶� ����ġ ����
void ThreeAdd(vector<vector<int>>& weightBoard)
{
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            // ���� ���ٸ� continue..
            if (stronCheck[x][y] == 0) continue;

            for (int dir = 0; dir < 4; dir++)
            {
                // x, y �� �������� ��ĭ ��ġ�� ��
                StonePos left_one = { x + dirX[dir], y + dirY[dir] };
                StonePos right_one = { x + dirX[(dir + 4) % 8], y + dirY[(dir + 4) % 8] };

                // x, y �� �������� ��ĭ ��ġ�� ��
                StonePos left_two = { x + dirX[dir] * 2, y + dirY[dir] * 2 };
                StonePos right_two = { x + dirX[(dir + 4) % 8] * 2, y + dirY[(dir + 4) % 8] * 2 };

                // ���� ������ 3�� ������������
                if (stronCheck[x][y] == stronCheck[left_one.x][left_one.y] && stronCheck[x][y] == stronCheck[right_one.x][right_one.y])
                {
                    // 3���� ��������� ���� ���� �ٸ����̸� continue..
                    if (stronCheck[x][y] == stronCheck[left_one.x][left_one.y] + 1 % 2 && stronCheck[x][y] == stronCheck[right_one.x][right_one.y] + 1 % 2)
                    {
                        continue;
                    }

                    // ���� 3��
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

// 4���϶� ����ġ ����
void FourAdd(vector<vector<int>>& weightBoard)
{
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            // ���� �̹� �ִٸ� continue..
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