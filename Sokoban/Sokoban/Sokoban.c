#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>	//getch()
#include <windows.h> 

void gotoxy(int x, int y)
{
    // x, y ��ǥ ����
    COORD position = { x, y };

    // Ŀ�� �̵� �Լ�
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// ��ũ�η� �����¿�� ���������� ����
#define ESC 27
#define SPACE 32
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define MAXSTAGE 3


char map[18][21];
int stage; // ���° �������� ����
int nx, ny; 
int MoveCount; // ������ Ƚ��

char CreateMap[MAXSTAGE][18][21] = {
     {

     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "##    O          *##",
     "## &  O          *##",
     "##    O          *##",
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
     "#########* #########",
     "#######      #######",
     "#####          #####",
     "###   ## O  ##   ###",
     "##*   O   &  O   *##",
     "###   ##  O ##   ###",
     "#####          #####",
     "#######      #######",
     "######### *#########",
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
     "####################",
     "####################",
     "##    O          *##",
     "## &  O          *##",
     "##    O          *##",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################",
     "####################"
     },
};

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
    cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}   //Ŀ�� ����� 
void ViewCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 20; //Ŀ�� ���� (1 ~ 100)
    cursorInfo.bVisible = TRUE; //Ŀ�� Visible TRUE(����) FALSE(����)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}   //Ŀ�� �����ֱ�


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

    } // �� ���


    gotoxy(nx, ny); //�÷��̾� �ʻ� ���
    printf("&");


    // �ΰ��� ������ �ߴ� ����
    gotoxy(32, 2); puts("SOKOBAN");
    gotoxy(32, 4); puts("ESC : ����, SPACE : ����");
    gotoxy(32, 6); puts("A : ���� ��������");
    gotoxy(32, 8); puts("D : ���� ��������");
    gotoxy(32, 10); printf("�������� : %d", stage + 1);
    gotoxy(32, 12); printf("�̵� Ƚ�� : %d", MoveCount);

}

BOOL TestEnd()
{

    int x, y;

    for (y = 0; y < 18; y++) 
    {
        for (x = 0; x < 20; x++) 
        {
            if (CreateMap[stage][y][x] == '*' && map[y][x] != 'O') 
            {
                return FALSE;
            }
        }
    }

    return TRUE;

}

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
    }   // player �̵�


    if (map[ny + dy][nx + dx] != '#') 
    {
        if (map[ny + dy][nx + dx] == 'O') 
        {
            if (map[ny + dy * 2][nx + dx * 2] == ' ' || map[ny + dy * 2][nx + dx * 2] == '*')
            {

                if (CreateMap[stage][ny + dy][nx + dx] == '*')
                {
                    map[ny + dy][nx + dx] = '*';
                }
                else {
                    map[ny + dy][nx + dx] = ' ';
                }
                map[ny + dy * 2][nx + dx * 2] = 'O';
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


void main()
{
    int key;
    int x, y;
    HideCursor();
    stage = 0;


    while (1) {

        memcpy(map, CreateMap[stage], sizeof(map));

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

            if (key == 0xE0 || key == 0) {

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
                key = tolower(key); // �Է°��� �ҹ��ڷ� ����

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



            if (TestEnd()) {

                system("cls");

                gotoxy(10, 10);

                printf("%d��° ���������� Ǯ�����ϴ�. ���� ���������� �̵��մϴ�",  stage + 1);

                Sleep(2000);

                if (stage < MAXSTAGE - 1) {

                    stage++;

                }

                break;

            }

        }

    }

}



