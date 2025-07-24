#include<stdio.h>
#include<stdlib.h>
#define SIZE 15
#define BLACKtem 10
#define WHITEtem 54
#define BLACK 11
#define WHITE 55


extern int direction[4][2];//定义读取方向 四个方向
extern int Board[SIZE][SIZE]; //棋盘
void changepass();
void InitBoardArray(); 
void DisplayBoard();	
int iswin(int,int,int);
void playervs(void);
int getthree_good(int,int,int);//活三,前两个int是坐标，最后一个控制读取方向
int getthree_bad(int,int,int);//冲三
int getfour_good(int,int,int);//活四
int getfour_bad(int,int,int);//冲四
int gettwo_good(int,int,int);//活二
int gettwo_bad(int,int,int);//冲二
int getlong(int,int);//长连
int forbid(int,int);
void dir();//方向数组初始化赋值
