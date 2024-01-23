#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>	
#include <windows.h>



#define ESC 27
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define SPACE 32
#define MAXSTAGE 2

void GotoXY(int x, int y)
{
	// x, y ��ǥ ����
	COORD position = { x, y };

	// Ŀ�� �̵� �Լ�
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void TextColor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}
enum ColorType {
	BLACK = 0,  	//0
	darkBLUE=1,		//1
	DarkGreen=2,	//2
	darkSkyBlue=3,  //3
	DarkRed=4,  	//4
	DarkPurple=5,	//5
	DarkYellow=6,	//6
	GRAY=7,			//7
	DarkGray=8,		//8
	BLUE=9,			//9
	GREEN=10,		//10
	SkyBlue=11,		//11
	RED=12,			//12
	PURPLE=13,		//13
	YELLOW=14,		//14
	WHITE=15		//15
} COLOR;



/*title Screen =====================================================================================*/
void LoadingStage()
{
	int i;

	for (i = 0; i < 45; i++)
	{
		GotoXY(10 + i, 5);
		TextColor(1);
		printf("-");
		Sleep(10);
	}

	for (i = 0; i < 45; i++)
	{
		GotoXY(70 - i, 10);
		printf("-");
		Sleep(10);
	}

	Sleep(800);
	GotoXY(35, 7);
	printf("��");

	Sleep(600);
	GotoXY(38, 7);
	printf("��");

	Sleep(600);
	GotoXY(41, 7);
	printf("��");

	Sleep(600);
	GotoXY(48, 8);
	printf("M");

	Sleep(40);
	GotoXY(49, 8);
	printf("a");

	Sleep(40);
	GotoXY(50, 8);
	printf("d");

	Sleep(40);
	GotoXY(51, 8);
	printf("e");

	Sleep(40);
	GotoXY(53, 8);
	printf("b");

	Sleep(40);
	GotoXY(54, 8);
	printf("y");

	Sleep(40);
	GotoXY(56, 8);
	printf("������");

	Sleep(2500);
}

/*====================================================================*/

#define WIDTH 21
#define HEIGHT 21

char map[WIDTH][HEIGHT];


typedef struct Player
{
	int x;
	int y;
	const char* shape;

}Player; //�÷��̾� ��ǥ

void CreateMaze()
{
	// 0 : �� ���� (" ") -> but Ư�� ���ڰ� 2byte�̹Ƿ� 2�� �������Ѵ�.
	// 1 : �� (��)
	// 2 : ���� (��)
	// 3 : �÷��̾� ()
	// 4 : ���ڸ� �Űܾ� �ϴ� ��ǥ��(��)

	strcpy(map[0],  "00000000000000000000");
	strcpy(map[1],  "00000000000000000000");
	strcpy(map[2],  "00000000000000000000");
	strcpy(map[3],  "00000000000000000000");
	strcpy(map[4],  "00000000111100000000");
	strcpy(map[5],  "00000011111111000000");
	strcpy(map[6],  "00001111102111110000");
	strcpy(map[7],  "00011111000011111000");
	strcpy(map[8],  "01111100030000111110");
	strcpy(map[9],  "11112000300300021111");
	strcpy(map[10], "01111100003000111110");
	strcpy(map[11], "00011111000011111000");
	strcpy(map[12], "00001111102111110000");
	strcpy(map[13], "00000011111111000000");
	strcpy(map[14], "00000000111100000000");
	strcpy(map[15], "00000000000000000000");
	strcpy(map[15], "00000000000000000000");
	strcpy(map[16], "00000000000000000000");
	strcpy(map[17], "00000000000000000000");
	strcpy(map[18], "00000000000000000000");
	strcpy(map[19], "00000000000000000000");
	strcpy(map[20], "00000000000000000000");




}

void Render()
{	
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++) {
			//'0'�� ����
			//'1'�� ��
			//'2'�� ��ǥ��
			//'3'�� ����
			switch (map[i][j])
			{
			case '0':
				printf("  ");
				break;
			case '1':
				printf("��");
				break;
			case '2':
				printf("��");
				break;
			case '3':
				printf("��");
				break;
			default:
				break;
			}
		}
		printf("\n");
	}

}

void Keyboard(char map[WIDTH][HEIGHT], Player* player)
{
	char key = 0;

	if (_kbhit()) //Ű���� �Է�Ȯ�� (true/false)
	{

		key = _getch();	// key �Է��� �޾��ִ� �Լ�

		system("cls");

		if (key == -32)
		{
			key = _getch();
		}

		switch (key)
		{
		case UP: if (map[player->y - 1][player->x / 2] != '1') { player->y--; }
			   break;
		case LEFT: if (map[player->y][player->x / 2 - 1] != '1') { player->x -= 2; }
				 break;
		case RIGHT: if (map[player->y][player->x / 2 + 1] != '1') { player->x += 2; }
				  break;
		case DOWN: if (map[player->y + 1][player->x / 2] != '1') { player->y++; }
				 break;
		}
	}
}
void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}


int main() 
{
	
	CursorView();
	
	LoadingStage();

	Player player = { 18,10,"��" };
	CreateMaze();// �� �����͸� �����մϴ�.
	Render();
	while (1)
	{
		Render(); // �� �����Ϳ� �ִ� ������ ���� ����մϴ�.

		Keyboard(map, &player);	// map[][]�� �ϳ��� �����Ͷ�� �ش�ȴ�. maze�� keyboard �Լ��� char 

		GotoXY(player.x, player.y);
		printf("%s", player.shape);

		Sleep(100);
		system("cls");
	}
	

	
	return 0;
}