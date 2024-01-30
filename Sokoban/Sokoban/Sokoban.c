#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>	
#include <windows.h> 


// 매크로로 상하좌우와 스테이지수 설정
#define ESC 27
#define SPACE 32
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define MAXSTAGE 3

// 전역변수 생성
char map[18][21]; // 스테이지
int stage;        // 몇번째 스테이지 인지
int nx, ny;       // Player의 현재 위치
int MoveCount;    // 움직인 횟수



//맵 생성 함수
char CreateMap[MAXSTAGE][18][21] = {
     {
      // # : 벽
      // O : 바위
      // & : 플레이어

     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "#####   O     *#####",
     "#####&  O     *#####",
     "#####   O     *#####",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################"

     },
     {

     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "#########*##########",
     "######### ##########",
     "#########O O  *#####",
     "######*  O&##########",
     "##########O#########",
     "########## #########",
     "##########*#########",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################"
     },
     {
     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "#########  #########",
     "########&O #########",
     "#########O #########",
     "######### O ########",
     "########*O  ########",
     "########** *########",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################"
     },
};

// 콘솔창에 커서 숨겨주고 나타내는 함수
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}   //커서 숨기기 
void ViewCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 20; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = TRUE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}   //커서 보여주기

//좌표지정 함수
void gotoxy(int x, int y)
{
    // x, y 좌표 설정
    COORD position = { x, y };

    // 커서 이동 함수
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}   

// 콘솔에 출력되는 값들
void DrawScreen()

{

    int x, y;

    for (y = 0; y < 18; y++)
    {
        for (x = 0; x < 20; x++)
        {
            gotoxy(x, y);
            printf("%c", map[y][x]);
        }

    } // 맵 출력


    gotoxy(nx, ny); //플레이어 맵상에 출력
    printf("&");


    // 인게임 내에서 뜨는 정보
    gotoxy(32, 2); puts("SOKOBAN");
    gotoxy(32, 4); puts("ESC : 종료, SPACE : 리셋");
    gotoxy(32, 6); puts("A : 이전 스테이지");
    gotoxy(32, 8); puts("D : 다음 스테이지");
    gotoxy(32, 10); printf("스테이지 : %d", stage + 1);
    gotoxy(32, 12); printf("이동 횟수 : %d", MoveCount);
}

// Player & 바위 이동시켜주는 함수
void Move(int key)  

{

    int dx = 0, dy = 0;

    switch (key) {
    case LEFT:
        dx -= 1;
        break;
    case RIGHT:
        dx += 1;
        break;
    case UP:
        dy -= 1;
        break;
    case DOWN:
        dy += 1;
        break;
    }   // player 이동


    if (map[ny + dy][nx + dx] != '#')   // Player & 벽 충돌 방지
    {
        if (map[ny + dy][nx + dx] == 'O')  // Player & 바위 충돌 방지
        {
            if (map[ny + dy * 2][nx + dx * 2] == ' ' || map[ny + dy * 2][nx + dx * 2] == '*') // 바위 & 벽 충돌 방지
            {

                if (CreateMap[stage][ny + dy][nx + dx] == '*')
                {
                    map[ny + dy][nx + dx] = '*';
                }
                else {
                    map[ny + dy][nx + dx] = ' ';
                }

                map[ny + dy * 2][nx + dx * 2] = 'O';    // 바위 이동
            }
            else {
                return;
            }
        }
        nx += dx;
        ny += dy;
        MoveCount++;
    }
}

// 각 스테이지 클리어한 후의 값을 받는 논리함수(바위가 목표점에 도달 = 'True' / 도달하지 X = 'False')
BOOL TestEnd()
{

    int x, y;

    for (y = 0; y < 18; y++) 
    {
        for (x = 0; x < 20; x++) 
        {
            if (CreateMap[stage][y][x] == '*' && map[y][x] != 'O') // 바위가 목표점에 도달하지 못했을 경우 계속진행
            {
                return FALSE;
            }
        }
    }

    return TRUE; // 바위가 목표점에 도달했을 때 종료

}

// Main 함수
void main()
{
    int key;
    int x, y;
    HideCursor();
    stage = 0;


    while (1) {

        memcpy(map, CreateMap[stage], sizeof(map)); // map 배열에 CreateMap 배열을 복사

        for (y = 0; y < 18; y++) {
            for (x = 0; x < 20; x++) {
                if (map[y][x] == '&') {
                
                    nx = x;                     
                    
                    ny = y;
                    
                    map[y][x] = ' ';
                
                }

            }

        }
        system("cls");
        MoveCount = 0;


        while (1) {

            DrawScreen();

            key = _getch();

            if (key == 0xE0 ) {

                key = _getch();

                switch (key) {
                case LEFT:
                case RIGHT:
                case UP:
                case DOWN:
                   Move(key);
                   break;
                }
            }
            else {
                key = tolower(key); // 입력값을 소문자로 변형

                if (key == SPACE) {
                    break;
                }

                if (key == 'd') {
                    if (stage < MAXSTAGE - 1) { stage++; }
                    break;
                }

                if (key == 'a') {
                    if (stage > 0) { stage--;}
                    break;
                }

                if (key == ESC) {
                    system("cls");
                    gotoxy(29, 10);
                    printf("Game End~!");
                    printf("\n\n\n\n\n\n\n\n");
                    ViewCursor();
                    exit(0);

                }

            }


            // 각 스테이지 클리어한 후에 실행
            if (TestEnd()) {
                if (stage < MAXSTAGE - 1) {
                    system("cls");
                    gotoxy(10, 10);
                    printf("%d번째 스테이지를 풀었습니다. 다음 스테이지로 이동합니다", stage + 1);
                    Sleep(2000);
                    stage++;
                }
                else
                {
                    system("cls");
                    gotoxy(29, 10);
                    printf("All Clear~!");
                    printf("\n\n\n\n\n\n\n\n");
                    ViewCursor();
                    exit(0);
                }
                break;
            }
        }

    }

}



