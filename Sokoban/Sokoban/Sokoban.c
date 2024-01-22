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



//title Screen =====================================================================================
//void LoadingStage()
//{
//	int i;
//	for (i = 0; i < 45; i++)
//	{
//		GotoXY(10 + i, 5);
//		printf('-');
//		sleep(10);
//	}
//	for (i = 0; i < 45; i++)
//	{
//		GotoXY(70-i, 10);
//		printf('-');
//		sleep(10);
//	}
//
//	sleep(800);
//	GotoXY(35, 7);
//	printf("��");
//	sleep(600);
//	GotoXY(38, 7);
//	printf("��");
//	sleep(600);
//	GotoXY(41, 7);
//	printf("��");
//	sleep(600);
//	GotoXY(48, 8);
//	printf('M');
//	sleep(40);
//	GotoXY(49, 8);
//	printf('a');
//	sleep(40);
//	GotoXY(50, 8);
//	printf('d');
//	sleep(40);
//	GotoXY(51, 8);
//	printf('e');
//	sleep(40);
//	GotoXY(53, 8);
//	printf('b');
//	GotoXY(54, 8);
//	printf('y');
//	sleep(40);
//	GotoXY(56, 8);
//	printf("������");
//
//	sleep(2500);
//}
//====================================================================





















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

	strcpy(map[0],  "11111111111111111111");
	strcpy(map[1],  "11111111111111111111");
	strcpy(map[2],  "11111111111111111111");
	strcpy(map[3],  "11111111111111111111");
	strcpy(map[4],  "11111111111111111111");
	strcpy(map[5],  "11111111111111111111");
	strcpy(map[6],  "11111111111111111111");
	strcpy(map[7],  "11111111102111111111");
	strcpy(map[8],  "11111111000011111111");
	strcpy(map[9],  "11111100003000111111");
	strcpy(map[10], "11112000340300021111");
	strcpy(map[11], "11111100003000111111");
	strcpy(map[12], "11111111000011111111");
	strcpy(map[13], "11111111120111111111");
	strcpy(map[14], "11111111111111111111");
	strcpy(map[15], "11111111111111111111");
	strcpy(map[15], "11111111111111111111");
	strcpy(map[16], "11111111111111111111");
	strcpy(map[17], "11111111111111111111");
	strcpy(map[18], "11111111111111111111");
	strcpy(map[19], "11111111111111111111");
	strcpy(map[20], "11111111111111111111");




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
			//'4'�� �÷��̾�
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









int main() 
{
	
	//LoadingStage();



	Player player = {18,10,"��"};

	// 1. �� �����͸� �����մϴ�.
	createmaze();

	while (1)
	{
	// 2. �� �����Ϳ� �ִ� ������ ���� ����մϴ�.
	render();

	keyboard(map, &player);	//map[][]�� �ϳ��� �����Ͷ�� �ش�ȴ�. maze�� keyboard �Լ��� char 

	GotoXY(player.x, player.y);
	printf("%s", player.shape);

	sleep(100);
	system("cls");
	}
	return 0;
}