#define _CRT_SECURE_NO_WARNINGS

#include"game.h"

void menu2()
{
	printf("*********************\n");
	printf("****** 1. 标记 ******\n");
	printf("****** 2. 排查 ******\n");
	printf("*********************\n");
}

void Init_Board(char board[Rows][Lines], int rows, int lines, char set)
{
	int i = 0, j = 0;
	for (i = 0; i < Rows; i++)
	{
		for (j = 0; j < Lines; j++)
		{
			board[i][j] = set;
		}
	}
}
void Draw_board(char board[Rows][Lines], int row, int line)
{
	int i = 0, j = 0;
	//打印列号
	for (i = 0; i <= line; i++)
	{
		printf("%d ", i);
	}
	putchar('\n');
	for (i = 1; i <= row; i++)
	{
		//打印行号
		printf("%d ", i);
		for (j = 1; j <= line; j++)
		{
			printf("%c ", board[i][j]);
		}
		putchar('\n');
	}
}
void Set_mine(char board[Rows][Lines], int row, int line)
{
	int count = EASY_COUNT;
	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % line + 1;
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}
int Get_mine_count(char mine[Rows][Lines], int x, int y)
{
	return  mine[x - 1][y - 1] +
		mine[x - 1][y] +
		mine[x - 1][y + 1] +
		mine[x][y - 1] +
		mine[x][y + 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] -  8 * 48;
}
void Expand_space(char show[Rows][Lines],char mine[Rows][Lines] ,int x, int y, int **win)
{
	int count = 0;
	count = Get_mine_count(mine, x, y);
	if (count)
	{
		(** win)++;
		show[x][y] = count + '0';
	}
	if (!count)
	{
		show[x][y] = ' ';
		if (show[x -1 ][y -1 ] == '*' && x-1 > 0 && y-1 > 0)
		Expand_space(show, mine, x - 1, y - 1, win);
		if (show[x - 1][y] == '*' && x - 1 > 0 )
		Expand_space(show, mine, x - 1, y, win);
		if (show[x - 1][y + 1] == '*' && x - 1 > 0 && y + 1 < Lines)
		Expand_space(show, mine, x - 1, y + 1, win);
		if (show[x][y - 1] == '*' && y - 1 > 0)
		Expand_space(show, mine, x, y - 1, win);
		if (show[x][y + 1] == '*' && y + 1 < Lines)
		Expand_space(show, mine, x, y + 1, win);
		if (show[x + 1][y - 1] == '*' && x + 1 < Rows && y - 1 > 0)
		Expand_space(show, mine, x + 1, y - 1, win);
		if (show[x + 1][y] == '*' && x + 1 <Rows)
		Expand_space(show, mine, x + 1, y, win);
		if (show[x - 1][y - 1] == '*' && x + 1 < Rows && y + 1 < Lines)
		Expand_space(show, mine, x + 1, y + 1, win);
	}
	
}
void troubleshoot_mine(char show[Rows][Lines], char mine[Rows][Lines] ,int row ,int line, int *ok, int *win)
{
	int x = 0, y = 0;
	int flag = 1;
	while (flag)
	{
		printf("请输入要排查的位置坐标\n");
		//合法输入
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= line)
		{
			//坐标合法,继续
			//如果输入的坐标是雷
			flag = 0;
			if (mine[x][y] == '1')
			{
				printf("很遗憾,游戏结束\n");
				Draw_board(mine, row, line);
				*ok = 0;
			}
			else
			{
				//展开空白
				(*win)++;
				Expand_space(show, mine, x, y, &win);
				Draw_board(show, row, line);
			}
		}
		else
		{
			//坐标非法,再次输入
			printf("你输入的坐标非法,请重新输入\n");
		}
	}
}
void Sign_mine(char show[Rows][Lines], char mine[Rows][Lines], int row, int line,int *sign)
{
	int x = 0, y = 0;
	int flag = 1;
	while (flag)
	{
		printf("请输入想要标记的坐标：（选择已标记的坐标则会取消标记）\n");
		scanf("%d %d", &x, &y);
		//判断输入合法
		if (x >= 1 && x <= row && y >= 1 && y <= line)
		{
			flag = 0;
			if (show[x][y] == '?')
			{
				printf("改坐标已被标记\n将取消标记\n");
				(* sign)--;
				show[x][y] = '*';
				Draw_board(show, row, line);
			}
			else
			{
				if ((* sign) < EASY_COUNT)
				{
					printf("改坐标已被标记\n");
					show[x][y] = '?';
					Draw_board(show, row, line);
					(*sign)++;
				}
				else
				{
					printf("标记达到上限\n取消之前的标记可以继续标记\n");
				}
			}
		}
		else
		{
			printf("输入坐标不合法,请重新输入\n");
		}
	}
}
void Find_mine(char mine[Rows][Lines], char show[Rows][Lines], int row, int line)
{
	int ok = 1;
	int win = 0;
	int sign = 0;
	int input = 0;
	while (ok && win < row * line - EASY_COUNT)
	{
			menu2();
			while (scanf("%d", &input) != 1)
			{
				getchar();
				printf("输入不合法,重新输入\n");
			}
			switch (input)
			{
			case 1:
				Sign_mine(show, mine, row, line, &sign);
					break;
			case 2:
				troubleshoot_mine(show ,mine ,row ,line, &ok ,&win);
				break;
			default:
				printf("输入错误重新输入");
				break;
			}
			if (win == row * line - EASY_COUNT)
			{
				printf("恭喜你！排雷成功！你可真是个排雷小天才！\n");
				Draw_board(show, row, line);
			}
	}
}
