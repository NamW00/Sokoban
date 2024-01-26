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
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define MAXSTAGE 3


char map[18][21];
int nStage;
int nx, ny;
int nMove;

char CreateMap[MAXSTAGE][18][21] = {
     {

     "####################",

     "####################",

     "####################",

     "#####   ############",

     "#####O  ############",

     "#####  O############",

     "###  O O ###########",

     "### # ## ###########",

     "#   # ## #####  ..##",

     "# O  O   @      ..##",

     "##### ### # ##  ..##",

     "#####     ##########",

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

     "####..  #     ######",

     "####..  # O  O  ####",

     "####..  #O####  ####",

     "####..    @ ##  ####",

     "####..  # #  O #####",

     "######### ##O O ####",

     "###### O  O O O ####",

     "######    #     ####",

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

     "##########     @####",

     "########## O#O #####",

     "########## O  O#####",

     "###########O O #####",

     "########## O # #####",

     "##....  ## O  O  ###",

     "###...    O  O   ###",

     "##....  ############",

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
            printf('%c', map[y][x]);
        }

    }

    gotoxy(nx, ny);
    printf('@');




    gotoxy(40, 2); puts("SOKOBAN");

    gotoxy(40, 4); puts("Q:����, R:�ٽ� ����");

    gotoxy(40, 6); puts("N:����, P:����");

    gotoxy(40, 8); printf("�������� : %d", nStage + 1);

    gotoxy(40, 10); printf("�̵� ȸ�� : %d", nMove);

}
BOOL TestEnd()

{

    int x, y;



    for (y = 0; y < 18; y++) {

        for (x = 0; x < 20; x++) {

            if (CreateMap[nStage][y][x] == '.' && map[y][x] != 'O') {

                return FALSE;

            }

        }

    }

    return TRUE;

}
void Move(int dir)

{

    int dx = 0, dy = 0;



    switch (dir) {

    case LEFT:

        dx = -1;

        break;

    case RIGHT:

        dx = 1;

        break;

    case UP:

        dy = -1;

        break;

    case DOWN:

        dy = 1;

        break;

    }



    if (map[ny + dy][nx + dx] != '#') {

        if (map[ny + dy][nx + dx] == 'O') {

            if (map[ny + dy * 2][nx + dx * 2] == ' ' || map[ny + dy * 2][nx + dx * 2] == '.') {

                if (CreateMap[nStage][ny + dy][nx + dx] == '.') {

                    map[ny + dy][nx + dx] = '.';

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

        nMove++;

    }

}


void main()

{

    int key;
    int x, y;

    HideCursor();

    nStage = 0;


    for (; 1;) {

        memcpy(map, CreateMap[nStage], sizeof(map));

        for (y = 0; y < 18; y++) {

            for (x = 0; x < 20; x++) {

                if (map[y][x] == '@') {

                    nx = x;

                    ny = y;

                    map[y][x] = ' ';

                }

            }

        }

        clrscr();

        nMove = 0;



        for (; 2;) {

            DrawScreen();

            key = getch();

            if (key == 0xE0 || key == 0) {

                key = getch();

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

                key = tolower(key);

                if (key == 'r') {

                    break;

                }

                if (key == 'n') {

                    if (nStage < MAXSTAGE - 1) {

                        nStage++;

                    }

                    break;

                }

                if (key == 'p') {

                    if (nStage > 0) {

                        nStage--;

                    }

                    break;

                }

                if (key == 'q') {

                    ViewCursor();

                    exit(0);

                }

            }



            if (TestEnd()) {

                clrscr();

                gotoxy(10, 10);

                printf("%d ���������� Ǯ�����ϴ�. ���� ���������� �̵��մϴ�",

                    nStage + 1);

                Sleep(2000);

                if (nStage < MAXSTAGE - 1) {

                    nStage++;

                }

                break;

            }

        }

    }

}



