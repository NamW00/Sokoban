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
	// x, y 좌표 설정
	COORD position = { x, y };

	// 커서 이동 함수
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
//	printf("소");
//	sleep(600);
//	GotoXY(38, 7);
//	printf("코");
//	sleep(600);
//	GotoXY(41, 7);
//	printf("반");
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
//	printf("남형우");
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

}Player; //플레이어 좌표

void CreateMaze()
{
	// 0 : 빈 공간 (" ") -> but 특수 문자가 2byte이므로 2번 띄어줘야한다.
	// 1 : 벽 (▩)
	// 2 : 상자 (▤)
	// 3 : 플레이어 ()
	// 4 : 상자를 옮겨야 하는 목표점(★)

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
			//'0'은 공백
			//'1'은 벽
			//'2'는 목표점
			//'3'은 상자
			//'4'는 플레이어
			switch (map[i][j])
			{
			case '0':
				printf("  ");
				break;
			case '1':
				printf("▩");
				break;
			case '2':
				printf("★");
				break;
			case '3':
				printf("■");
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

	if (_kbhit()) //키보드 입력확인 (true/false)
	{

		key = _getch();	// key 입력을 받아주는 함수

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



	Player player = {18,10,"♠"};

	// 1. 맵 데이터를 생성합니다.
	createmaze();

	while (1)
	{
	// 2. 맵 데이터에 있는 정보를 토대로 출력합니다.
	render();

	keyboard(map, &player);	//map[][]가 하나의 포인터라고 해당된다. maze가 keyboard 함수의 char 

	GotoXY(player.x, player.y);
	printf("%s", player.shape);

	sleep(100);
	system("cls");
	}
	return 0;
}