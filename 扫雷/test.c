#define _CRT_SECURE_NO_WARNINGS

#include"game.h"

void test();
void menu();
void game();

int main()
{
	test();
	return 0;
}
void test()
{
	int input = 0;
	int flag = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		if (!flag)
		{
			printf("请选择是否进行游戏:> ");
			flag++;
		}
		else
		{
			printf("请选择是否继续游戏:> ");
		}
		while (scanf("%d", &input) != 1)
		{
			getchar();
			printf("输入非法,重新输入");
		}
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("输入错误,请重新接输入\n");
			break;
		}
	} while (input);
}
void menu()
{
	printf("*********************\n");
	printf("****** 1. play ******\n");
	printf("****** 0. exit ******\n");
	printf("*********************\n");
}
void game()
{
	//布置储存雷
	//布置雷
	char deposit_mine[Rows][Lines] = { 0 };
	//排查雷
	char show_mine[Rows][Lines] = { 0 };
	//初始化
	Init_Board(deposit_mine, Rows, Lines, '0');
	Init_Board(show_mine, Rows, Lines, '*');
	//打印棋盘
	//Draw_board(deposit_mine, Row , Line);
	Draw_board(show_mine, Row, Line);
	//布置雷
	Set_mine(deposit_mine , Row , Line);
	//扫雷
	//Draw_board(deposit_mine, Row, Line);
	Find_mine(deposit_mine , show_mine , Row , Line);
}
