#define Row 9
#define Line 9

#define Rows Row + 2
#define Lines Line + 2

#define EASY_COUNT 10

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void Init_Board(char board[Rows][Lines], int rows, int lines, char set);
void Draw_board(char board[Rows][Lines], int row, int line);
void Set_mine(char board[Rows][Lines], int row, int line);
void Find_mine(char mine[Rows][Lines], char show[Rows][Lines], int row, int line);
