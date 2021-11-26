// Concave.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Concave.h"

#define MAX_LOADSTRING 100

// 사용자 지정 함수-----------------------------------------------------------------------------------------------------------------

DWORD WINAPI AI(LPVOID lpParam);                                    // AI 쓰레드

void DeleteObjects();                                               // Object들 삭제하는 함수
void GetXY_BtnClick(HWND hWnd, LPARAM lParam, int xSrc, int ySrc);  // XY좌표를 얻어 버튼 클릭되었는지 체크하는 함수
void ImageRoad();                                                   // 이미지 로드하는 함수
void TimeChange(HWND hWnd);                                         // 시간 바꾸는 함수

void GameSetting();                                                 // 게임 세팅하는 함수(재시작)
void PaintMainScreen(HDC hdc);                                      // 메인화면 그리는 함수
void Paint_PVPButton(HDC hdc);                                      // 메인화면 [PVP] 버튼 그리는 함수     
void Paint_AIButton(HDC hdc);                                       // 메인화면 [AI] 버튼 그리는 함수 
void Paint_ExitButton(HDC hdc,int x, int y);                                 // 메인화면 [나가기] 버튼 그리는 함수 
void PaintStone(HDC hdc);                                           // 지금까지 둔 돌을 그리는 함수
void PaintCharacter(HDC hdc);                                       // 캐릭터 그리는 함수
void PaintTimer(HDC hdc);                                           // 타이머 그리는 함수
void PaintTurn(HDC hdc);                                            // 누구 턴인지 그리는 함수

void GetXY(HWND hWnd, LPARAM lParam);                               // X Y 좌표 얻는 함수
void TurnChange(HWND hWnd);                                         // 턴 바꾸는 함수
void DrawStone(HWND hWnd, int x, int y);                            // 놓은 돌 그리는 함수

//----------------------------------------------------------------------------------------------------------------------------------------

// 전역 변수:   
HINSTANCE hInst;                                        // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                         // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];                    // 기본 창 클래스 이름입니다.

struct StoneInfo {
    int x;
    int y;
    int check;
};

// 사용자 전역 변수-------------------------------------------------------------------------------------------------------------------------

RECT garbage;                                           // 쓰레기 RECT
RECT Background_Rect = { 180,30,820,670 };              // Background(오목판) 크기
vector<vector<RECT>> Bg_Rect(16, vector<RECT>(16));     // Background RECT 벡터
vector<vector<int>> Bg_Check(16, vector<int>(16));      // 바둑알이 있는지 check하는 벡터
vector<StoneInfo> Stone;                                // 바둑판에 놓인 돌 저장 벡터

// 남쪽부터 시작
int dx[8] = { 1,1,0,-1,-1,-1,0,1 };
int dy[8] = { 0,1,1,1,0,-1,-1,-1 };

int is_stone = 0;                                       // 현재 바둑알이 어떤 것인지 반환
int Time_remaining = PlayTime;                          // 현재 남은 시간
int ScreenStatus = StartScreen;                         // 현재 화면 상태
bool PVP_flag = false;                                  // [PVP] 버튼 클릭 상태
bool AI_flag = false;                                   // [AI 대전] 버튼 클릭 상태 
bool Exit_flag = false;                                 // [나가기] 버튼 클릭 상태
bool is_SetTimer = false;
bool is_AI_Thread = false;                              // AI 쓰레드가 존재 여부

// 비트맵 핸들
HBITMAP BlackStone, WhiteStone;                         // 바툭알 비트맵 핸들
HBITMAP BlackCh, WhiteCh;                               // 바둑 캐릭터 비트맵 핸들
HBITMAP TimerCheck;                                     // 타이머 비트맵 핸들
HBITMAP StartMainScreen;                                // 메인 시작화면 비트맵 핸들
HBITMAP Btn_PVP;                                        // [PVP] 버튼 비트맵 핸들
HBITMAP Btn_PVP_OnClick;                                // [PVP] 버튼 눌림 비트맵 핸들
HBITMAP Btn_AI;                                         // [AI대전] 버튼 비트맵 핸들
HBITMAP Btn_AI_OnClick;                                 // [AI대전] 버튼 눌림 비트맵 핸들
HBITMAP Btn_Exit;                                       // [나기기] 버튼 비트맵 핸들
HBITMAP Btn_Exit_OnClick;                               // [나가기] 버튼 눌림 비트맵 핸들

// 쓰레드 핸들
HANDLE AI_Thread;                                       // AI 쓰레드 핸들

//-------------------------------------------------------------------------------------------------------------------------------------

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CONCAVE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CONCAVE));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(Windows_Background_Color);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CONCAVE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, L"오목", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_GETMINMAXINFO: // 윈도우 크기 고정
    {
        ((MINMAXINFO*)lParam)->ptMaxTrackSize.x = Windows_Width;
        ((MINMAXINFO*)lParam)->ptMaxTrackSize.y = Windows_Heigth;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.x = Windows_Width;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.y = Windows_Heigth;
    }
    break;

    case WM_CREATE:
    {
        Center_Screen(hWnd, WS_OVERLAPPEDWINDOW, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
        
        SetBackgroundRect(Bg_Rect);
        
        ImageRoad();
    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_TIMER:
    {
        switch (wParam)
        {
        case Timer_ID_Second:

            TimeChange(hWnd);

        break;

        case Timer_ID_Start:

            KillTimer(hWnd, Timer_ID_Start);
            TimeChange(hWnd);

        break;

        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        switch (ScreenStatus)
        {
        case StartScreen:
        {
            // 메인 오목판
            PaintMainScreen(hdc);
            // [PVP] 버튼
            Paint_PVPButton(hdc);
            // [AI 대전] 버튼
            Paint_AIButton(hdc);
            //[나가기] 버튼
            Paint_ExitButton(hdc, 650, 550);
        }
        break;

        case GameScreen:
        {
            if (is_SetTimer == false)
            {
                SetTimer(hWnd, Timer_ID_Second, 1000, NULL);
                SetTimer(hWnd, Timer_ID_Start, 10, NULL);
                is_SetTimer = true;
            }

            PaintBoard(hdc);

            PaintStone(hdc);

            PaintTurn(hdc);

            PaintCharacter(hdc);

            PaintTimer(hdc);

            //[나가기] 버튼
            Paint_ExitButton(hdc,850,550);
        }
        break;

        case AIScreen:
        {
            if (is_SetTimer == false)
            {
                SetTimer(hWnd, Timer_ID_Second, 1000, NULL);
                SetTimer(hWnd, Timer_ID_Start, 10, NULL);
                is_SetTimer = true;
            }

            PaintBoard(hdc);

            PaintStone(hdc);

            PaintTurn(hdc);

            PaintCharacter(hdc);

            PaintTimer(hdc);

            //[나가기] 버튼
            Paint_ExitButton(hdc,850,550);

            // 백돌일 경우 AI 수를 놓음
            if (is_stone % 2 == 1)
            {
                AI_Thread = CreateThread(NULL, 0, AI, hWnd, 0, NULL);
                is_AI_Thread = true;
            }

        }
        break;
        default:
            break;
        }
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_MOUSEMOVE:
    {
        if (ScreenStatus == StartScreen)
        {
            GetXY_BtnClick(hWnd, lParam, 650, 550);
        }
        else
        {
            GetXY_BtnClick(hWnd, lParam, 850, 550);
        }
    }
    break;

    case WM_LBUTTONDOWN:
    {
        switch (ScreenStatus)
        {
        case StartScreen:
        {
            if (PVP_flag == true)
            {
                ScreenStatus = GameScreen;
                InvalidateRect(hWnd, NULL, false);
            }
            else if (AI_flag == true)
            {
                ScreenStatus = AIScreen;
                InvalidateRect(hWnd, NULL, false);
            }
            else if (Exit_flag == true)
            {
                exit(0);
            }
            
        }
        break;

        case GameScreen:
        {
            // [나가기] 버튼 클릭
            if (Exit_flag == true)
            {
                // 쓰레드 일시정지
                SuspendThread(AI_Thread);
                EndGame(hWnd, -1, &ScreenStatus);

                // 게임 세팅
                GameSetting();

                InvalidateRect(hWnd, NULL, false);
            }

            // X Y 좌표를 얻어 수를 놓는 함수
            GetXY(hWnd, lParam);
        }
        break;

        case AIScreen:
        {
            // [나가기] 버튼 클릭
            if (Exit_flag == true)
            {
                // 쓰레드 일시정지
                SuspendThread(AI_Thread);
                EndGame(hWnd, -1, &ScreenStatus);

                // 게임 세팅
                GameSetting();

                InvalidateRect(hWnd, NULL, false);
            }

            // 흑돌일 경우 사용자가 돌을 놓음
            if (is_stone % 2 == 0)
            {
                SuspendThread(AI_Thread);
                GetXY(hWnd, lParam);
            }
        }
        break;
        default:
            break;
        }

    }
    break;

    case WM_DESTROY:

        DeleteObjects();

        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


// 사용자 지정 함수 ----------------------------------------------------------------------------------------------------------

// AI 쓰레드
DWORD WINAPI AI(LPVOID lpParam)
{
    srand((unsigned int)time(NULL));

    HWND hWnd = (HWND)lpParam;
    HDC hdc = GetDC(hWnd);

    // 최종적 가중치
    vector<vector<int>> Final_board(16, vector<int>(16));

    // 판의 돌을 보고 돌의 가중치 저장
    vector<vector<int>> AI_board(16, vector<int>(16));

    // 가중치 값중 가장 큰 것들
    vector<pair<int, int>> min_value;

    int Who_Turn = 1; // 백돌 선공
    int maximum = -INF;
    int minimum = INF;

    // AI 시작 ------

    // AI_board 를 Undefined로 초기화
    Reset_Board(AI_board);

    // [가중치 증가]

    // 한칸 기준으로 가중치 저장
    OneAdd(AI_board, Bg_Check, Who_Turn);

    // 2 - 1 일때 가중치 증가 -> 돌 하나를 놓았을때 사목이 되면 가중치 증가
    Two_OneAdd(AI_board, Bg_Check);

    // 3개 이상 일때 가중치 증가
    ThreeAdd(AI_board, Bg_Check, 3, Who_Turn);

    // 4개 이상 일때 가중치 증가
    ThreeAdd(AI_board, Bg_Check, 4, Who_Turn);



    Sleep(500);
    // [READY]
    // AI_STACK에 가중치값 저장
    // [RUNNING]
    
    //Ready_AI(AI_board,Bg_Check, Who_Turn);
    
    // 가장 작은 값 찾기
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            minimum = min(minimum, AI_board[i][j]);
        }
    }

    // 작은 값이 여러개 라면 vector에 저장
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (AI_board[i][j] == minimum)
            {
                min_value.push_back({ i,j });
            }
        }
    }

    // 값이 같은 것중 랜덤으로 착수
    int random = rand() % min_value.size();

    // AI가 최종적으로 돌을 놓을 X Y 좌표
    int embroider_x = min_value[random].first;
    int embroider_y = min_value[random].second;


    // 돌 그리기
    DrawStone(hWnd, Bg_Rect[embroider_x][embroider_y].left, Bg_Rect[embroider_x][embroider_y].top);
    Stone.push_back({ Bg_Rect[embroider_x][embroider_y].left,Bg_Rect[embroider_x][embroider_y].top,is_stone });

    Bg_Check[embroider_x][embroider_y] = (is_stone % 2) + 1; // 1: 흑돌 2: 백돌
    

    if (is_Cheking_FiveStone(embroider_x, embroider_y, Bg_Check[embroider_x][embroider_y])) // 오목이 되었는가?
    {
        HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
        //타이머 RECT
        SelectObject(hdc, GetStockObject(NULL_PEN));
        Rectangle(hdc, 70, 220, 151, 261);
        Rectangle(hdc, 890, 220, 971, 261);
        DeleteObject(myBrush);

        EndGame(hWnd, is_stone, &ScreenStatus);

        // 게임 세팅
        GameSetting();

        // 쓰레드 종료
        ExitThread(0);
    }
    else
    {
        // 턴을 체인지함
        TurnChange(hWnd);
    }

    min_value.clear();

    return 0;
}

// 이미지 로드
void ImageRoad()
{
    // 바둑알 
    BlackStone = LoadBitmap(hInst, MAKEINTRESOURCE(Black_Stone));
    WhiteStone = LoadBitmap(hInst, MAKEINTRESOURCE(White_Stone));

    // 바둑 캐릭터
    BlackCh = LoadBitmap(hInst, MAKEINTRESOURCE(Black_Stone_Ch));
    WhiteCh = LoadBitmap(hInst, MAKEINTRESOURCE(White_Stone_Ch));

    // 타이머
    TimerCheck = LoadBitmap(hInst, MAKEINTRESOURCE(Timer));

    // 시작 화면
    StartMainScreen = LoadBitmap(hInst, MAKEINTRESOURCE(StartGame_Scrn));

    // [PVP] 버튼
    Btn_PVP = LoadBitmap(hInst, MAKEINTRESOURCE(Button_PVP));
    Btn_PVP_OnClick = LoadBitmap(hInst, MAKEINTRESOURCE(Button_PVP_OnClick));

    // [AI대전] 버튼
    Btn_AI = LoadBitmap(hInst, MAKEINTRESOURCE(Button_AI));
    Btn_AI_OnClick = LoadBitmap(hInst, MAKEINTRESOURCE(Button_AI_OnClick));

    // [AI버튼]
    Btn_Exit = LoadBitmap(hInst, MAKEINTRESOURCE(Button_Exit));
    Btn_Exit_OnClick = LoadBitmap(hInst, MAKEINTRESOURCE(Button_Exit_OnClick));
}

void GameSetting()
{
    is_stone = 0;                                       // 현재 바둑알이 어떤 것인지 확인
    Time_remaining = PlayTime;                          // 현재 남은 시간
    is_SetTimer = false;                                // 타이머를 세팅했는지 확인

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            Bg_Check[i][j] = 0;
        }
    }
    Stone.clear();
}

void PaintMainScreen(HDC hdc)
{
    HDC memDC;
    HBITMAP Goprint;
    HBRUSH myBrush;
    HBRUSH oldBrush;

    // 배경 그리기
    myBrush = (HBRUSH)CreateSolidBrush(Windows_Background_Color);
    oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
    Rectangle(hdc, 0, 0, Windows_Width, Windows_Heigth);

    // 시작화면 출력
    memDC = CreateCompatibleDC(hdc);
    Goprint = (HBITMAP)SelectObject(memDC, StartMainScreen);
    BitBlt(hdc, 180, 30, 640, 640, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, Goprint);
    DeleteDC(memDC);

    // 밖 테두리 선 그려주기
    myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
    Rectangle(hdc, Background_Rect.left, Background_Rect.top, Background_Rect.right, Background_Rect.bottom);

    DeleteObject(myBrush);
}

// [PVP] 버튼 그리는 함수
void Paint_PVPButton(HDC hdc)
{
    HDC memDC;
    HBITMAP Goprint;

    memDC = CreateCompatibleDC(hdc);

    if (PVP_flag == true)
        Goprint = (HBITMAP)SelectObject(memDC, Btn_PVP_OnClick);
    else
        Goprint = (HBITMAP)SelectObject(memDC, Btn_PVP);

    //BitBlt(hdc, 180, 30, 640, 640, memDC, 0, 0, SRCCOPY);
    GdiTransparentBlt(hdc, 650, 450, 120, 40, memDC, 0, 0, 120, 40, RGB(255, 255, 255));
    SelectObject(memDC, Goprint);

    DeleteDC(memDC);
}

// [AI 대전] 버튼 그리는 함수
void Paint_AIButton(HDC hdc)
{
    HDC memDC;
    HBITMAP Goprint;

    memDC = CreateCompatibleDC(hdc);

    if(AI_flag == true)
        Goprint = (HBITMAP)SelectObject(memDC, Btn_AI_OnClick);
    else
        Goprint = (HBITMAP)SelectObject(memDC, Btn_AI);

    //BitBlt(hdc, 180, 30, 640, 640, memDC, 0, 0, SRCCOPY);
    GdiTransparentBlt(hdc, 650, 500, 120, 40, memDC, 0, 0, 120, 40, RGB(255, 255, 255));
    SelectObject(memDC, Goprint);

    DeleteDC(memDC);
}

// [Exit 대전] 버튼 그리는 함수
void Paint_ExitButton(HDC hdc,int x, int y)
{
    HDC memDC;
    HBITMAP Goprint;

    memDC = CreateCompatibleDC(hdc);

    if (Exit_flag == true)
        Goprint = (HBITMAP)SelectObject(memDC, Btn_Exit_OnClick);
    else
        Goprint = (HBITMAP)SelectObject(memDC, Btn_Exit);

    //BitBlt(hdc, 180, 30, 640, 640, memDC, 0, 0, SRCCOPY);
    GdiTransparentBlt(hdc, x, y, 120, 40, memDC, 0, 0, 120, 40, RGB(255, 255, 255));
    SelectObject(memDC, Goprint);

    DeleteDC(memDC);
}


// 버튼 클릭 상태 체크하는 함수
void GetXY_BtnClick(HWND hWnd,LPARAM lParam,int xSrc, int ySrc)
{
    // 마우스 좌표값 받아오기
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
    RECT mouse = { x,y,x + 1,y + 1 };

    if (ScreenStatus == StartScreen)
    {

        RECT PVP_Btn = { 650,450,650 + 120,450 + 40 };
        RECT AI_Btn = { 650,500,650 + 120,500 + 40 };

        // [PVP] 버튼 체크
        if (IntersectRect(&garbage, &mouse, &PVP_Btn) == true)
        {
            PVP_flag = true;
            InvalidateRect(hWnd, &PVP_Btn, false);
        }
        else if (PVP_flag == true)
        {
            PVP_flag = false;
            InvalidateRect(hWnd, &PVP_Btn, false);
        }

        // [AI] 버튼 체크
        if (IntersectRect(&garbage, &mouse, &AI_Btn) == true)
        {
            AI_flag = true;
            InvalidateRect(hWnd, &AI_Btn, false);
        }
        else if (AI_flag == true)
        {
            AI_flag = false;
            InvalidateRect(hWnd, &AI_Btn, false);
        }
    }

    RECT Exit_Btn = { xSrc,ySrc,xSrc + 120,ySrc + 40 };
    
    // [나가기] 버튼 체크
    if (IntersectRect(&garbage, &mouse, &Exit_Btn) == true)
    {
        Exit_flag = true;
        InvalidateRect(hWnd, &Exit_Btn, false);
    }
    else if(Exit_flag == true)
    {
        Exit_flag = false;
        InvalidateRect(hWnd, &Exit_Btn, false);
    }
}

// 돌 그리는 함수
void PaintStone(HDC hdc)
{
    HDC memDC;
    HBITMAP Goprint;
    HBRUSH myBrush;
    HBRUSH oldBrush;

    int x, y;

    memDC = CreateCompatibleDC(hdc);

    // 지금까지 놓은 수를 그림
    for (int idx = 0; idx < Stone.size(); idx++)
    {
        if (Stone[idx].check % 2 == 0)
        {
            Goprint = (HBITMAP)SelectObject(memDC, BlackStone);
        }
        else
        {
            Goprint = (HBITMAP)SelectObject(memDC, WhiteStone);
        }

        if (idx == (Stone.size() - 1))
        {
            x = Stone[idx].x;
            y = Stone[idx].y;
        }

        GdiTransparentBlt(hdc, Stone[idx].x, Stone[idx].y, 40, 40, memDC, 0, 0, 40, 40, RGB(192, 128, 59));
        //BitBlt(hdc, Stone[idx].x, Stone[idx].y, 40, 40, memDC, 0, 0, SRCCOPY);
        SelectObject(memDC, Goprint);
    }

    //현재 놓은 수 표시 
    if (Stone.size() > 0)
    {
        myBrush = (HBRUSH)CreateSolidBrush(Current_Color);
        oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

        Rectangle(hdc, x + 15, y + 15, x + 25, y + 25);

        SelectObject(hdc, oldBrush);
        DeleteObject(myBrush);
    }

    // 밖 테두리 선 그려주기
    myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

    Rectangle(hdc, Background_Rect.left, Background_Rect.top, Background_Rect.right, Background_Rect.bottom);

    DeleteDC(memDC);
}

// 캐릭터 그리는 함수
void PaintCharacter(HDC hdc)
{
    HDC memDC;
    HBITMAP Goprint;

    memDC = CreateCompatibleDC(hdc);

    Goprint = (HBITMAP)SelectObject(memDC, BlackCh);
    BitBlt(hdc, 30, 80, 120, 140, memDC, 0, 0, SRCCOPY);

    Goprint = (HBITMAP)SelectObject(memDC, WhiteCh);
    BitBlt(hdc, 850, 80, 120, 140, memDC, 0, 0, SRCCOPY);

    SelectObject(memDC, Goprint);

    DeleteDC(memDC);

}

// 타이머 그리는 함수
void PaintTimer(HDC hdc)
{
    HDC memDC;
    HBITMAP Goprint;

    // 타이머 그리기
    memDC = CreateCompatibleDC(hdc);
    Goprint = (HBITMAP)SelectObject(memDC, TimerCheck);
    BitBlt(hdc, 30, 220, 40, 40, memDC, 0, 0, SRCCOPY);

    Goprint = (HBITMAP)SelectObject(memDC, TimerCheck);
    BitBlt(hdc, 850, 220, 40, 40, memDC, 0, 0, SRCCOPY);

    SelectObject(memDC, Goprint);
    DeleteDC(memDC);
}

// 턴을 표시해주는 RECT 그리는 함수
void PaintTurn(HDC hdc)
{
    HBRUSH myBrush = (HBRUSH)CreateSolidBrush(Ch_Rect_Color);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

    if (is_stone % 2 == 0) // 흑돌 턴
    {
        Rectangle(hdc, 24, 74, 156, 266);
    }
    else                   // 백돌 턴
    {
        Rectangle(hdc, 844, 74, 976, 266);
    }
    
    SelectObject(hdc, oldBrush);
    DeleteObject(myBrush);
}
 
// 수 를 놓는 함수
void GetXY(HWND hWnd,LPARAM lParam)
{
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);

    RECT is_checking_rect = { x,y,x + 1,y + 1 };

    // 오목판이 아니면
    if (IntersectRect(&garbage, &is_checking_rect, &Background_Rect) == false) return;

    HDC hdc = GetDC(hWnd);

    // X Y 좌표를 얻어 돌을 놓는다
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {

            if (IntersectRect(&garbage, &Bg_Rect[i][j], &is_checking_rect) && Bg_Check[i][j] == 0)
            {
                DrawStone(hWnd,Bg_Rect[i][j].left,Bg_Rect[i][j].top);
                Stone.push_back({ Bg_Rect[i][j].left,Bg_Rect[i][j].top,is_stone});

                Bg_Check[i][j] = (is_stone % 2) + 1; // 1: 흑돌 2: 백돌

                if (is_Cheking_FiveStone(i, j, Bg_Check[i][j])) // 오목이 되었는가?
                {
                    EndGame(hWnd, is_stone, &ScreenStatus);
                    
                    // 게임 세팅
                    GameSetting();
                }
                else
                {
                    // 턴을 체인지함
                    TurnChange(hWnd);
                }

            }
        }
    }
    


    ReleaseDC(hWnd, hdc);
}
 
// 바둑알 그리는 함수
void DrawStone(HWND hWnd,int x,int y)
{
    HDC hdc, memDC;
    HBITMAP Goprint;

    hdc = GetDC(hWnd);
    memDC = CreateCompatibleDC(hdc);

    if (is_stone % 2 == 0) // 흑돌
    {
        Goprint = (HBITMAP)SelectObject(memDC, BlackStone);
    }
    else // 백돌
    {
        Goprint = (HBITMAP)SelectObject(memDC, WhiteStone);
    }

    BitBlt(hdc, x, y, 40, 40, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, Goprint);

    DeleteDC(memDC);
    ReleaseDC(hWnd, hdc);
}

// 오목인지 체크하는 함수
bool is_Cheking_FiveStone(int curr_x, int curr_y, int num)
{
    for (int dir = 0; dir < 4; dir++)
    {
        int nx, ny;
        int Stone_num = 0;

        for (int direct = 1; direct <= 6; direct++)
        {
            nx = curr_x + dx[dir] * direct;
            ny = curr_y + dy[dir] * direct;

            if (nx >= 0 && nx < 16 && ny >= 0 && ny < 16)
            {
                if (Bg_Check[nx][ny] == num) Stone_num++;
                else break;
            }

        }
        for (int direct = 1; direct <= 6; direct++)
        {
            nx = curr_x + dx[(dir + 4) % 8] * direct;
            ny = curr_y + dy[(dir + 4) % 8] * direct;

            if (nx >= 0 && nx < 16 && ny >= 0 && ny < 16)
            {
                if (Bg_Check[nx][ny] == num) Stone_num++;
                else break;
            }
        }

        // 오목 완성
        if (Stone_num == 4) return true;
        else Stone_num = 0;
    }
    return false;
}

void TimeChange(HWND hWnd)
{
    HDC hdc = GetDC(hWnd);

    HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

    TCHAR Time[10];

    if (Time_remaining < 0)
    {
        TurnChange(hWnd);
        ReleaseDC(hWnd,hdc);
        return ;
    }

    // 타이머 RECT
    SelectObject(hdc, GetStockObject(NULL_PEN));

    Rectangle(hdc, 70, 220, 151, 261);
    Rectangle(hdc, 890, 220, 971, 261);

    SelectObject(hdc, oldBrush);
    DeleteObject(myBrush);
    DeleteObject(oldBrush);

    wsprintf(Time, TEXT(" %d 초 "), Time_remaining);

    if (is_stone % 2 == 0) // 흑돌
    {
        TextOut(hdc, 80, 231, Time, lstrlen(Time));
    }
    else // 백돌
    {
        TextOut(hdc, 900, 231, Time, lstrlen(Time));
    }

    Time_remaining--;
    ReleaseDC(hWnd, hdc);
}

// 턴을 바꾸는 함수
void TurnChange(HWND hWnd)
{
    SetTimer(hWnd, Timer_ID_Start,0, NULL);
    is_stone++;
    Time_remaining = PlayTime;

    InvalidateRect(hWnd, NULL, true);
}

// Object 삭제
void DeleteObjects()
{
    // 돌
    DeleteObject(BlackStone);
    DeleteObject(WhiteStone);

    // 돌 캐릭터
    DeleteObject(BlackCh);
    DeleteObject(WhiteCh);

    // 타이머
    DeleteObject(TimerCheck);
}