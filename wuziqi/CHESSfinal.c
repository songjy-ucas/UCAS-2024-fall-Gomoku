#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>//需要的表头

#define SIZE 15
#define BLACKtem 14
#define WHITEtem 24
#define BLACK 11
#define WHITE 21
#define BAN   28
#define infinite 1000000//评分函数的具体分数
#define MAXSIZE 400//maxmax,max203的容量
#define getit  30//我方最优棋的数目
#define getother 15//对方最优棋数目



struct point{
        int x;
        int y;
        int score;
    };//分数结构
struct delt{
     struct point first;//第一步下的棋
     struct point second;//第二步下的棋
     int score;//分差结构
};

int Board[SIZE][SIZE];
struct point huiqi[225];//悔棋



void bubbleSort();//排序
void bubblesort1();//为了更为快速的bubble sort做的更适合于这个程序的排序
void InitBoardArray();  //初始化棋盘
void DisplayBoard();//展示棋盘
int iswin();//判断胜利的函数
void playGame1();//人人
void playGame2();//人机
int isValidMove();//判断是否是超范围的
int isbanlong();	//��ʾ����
int isbanother();
void bannewLONG();
void bannewsisi();
void bannewsansan();
int judgechange();
int playerchange();
void evaluate();//赋分
int  startchoose();
struct point  maxchoose();//找棋盘上最大分数棋子的信息

int choosetree();//决策树
struct point finalchoose();//最终选择


void main()
{
	int p;
	printf("欢迎来到五子棋人人对战平台\n");
	printf("请选择人机对战还是人人对战,人机对战请输入2,人人对战请输入1\n");
	
	while (1)
	{
		scanf("%d",&p);
		if(p==1){
			InitBoardArray();
			playGame1();
			break;
		}else if(p==2 ){
			InitBoardArray();
			playGame2();
			break;
		}else{
			printf("错误输入,请重新输入1或2\n");
			while (getchar() != '\n');

		}
	}
	

	
	}
void InitBoardArray()
{
	int j, i; 
	
	Board[0][0] = 1;
	Board[0][SIZE - 1] = 2;
	Board[SIZE - 1][SIZE - 1] = 3;
	Board[SIZE - 1][0] = 4;
	
	for (j = 1; j <= SIZE - 2; j++)
	{
		Board[j][0] = 5;
	}
	
	for (i = 1; i <= SIZE - 2; i++)
	{
		Board[0][i] = 6;
	}
	
	for (j = 1; j <= SIZE - 2; j++)
	{
		Board[j][SIZE - 1] = 7;
	}
	
	for (i = 1; i <= SIZE - 2; i++)
	{
		Board[SIZE - 1][i] = 8;
	}
	
	for (j = 1; j <= SIZE - 2; j++)
	{
		for (i = 1; i <= SIZE - 2; i++)
		{
			Board[j][i] = 9;
		}
	}
}

void DisplayBoard() 
{	
	int i, j;
	char line;
	char ary;
	


	for(j = 0,line = 15; j <= SIZE - 1; j++)
	{
		printf("%2d",line);
		line -= 1;
		for(i = 0; i <= SIZE - 1; i++)
		{
			switch(Board[j][i])
			{
			case 1:
				printf(" ┌");
				break;
				
			case 2:
				printf(" ┐");
				break;
				
			case 3:
				printf(" ┘");
				break;
				
			case 4:
				printf(" └");
				break;
				
			case 5:
				printf(" ├");
				break;
				
			case 6:
				printf(" ┬");
				break;
				
			case 7:
				printf( " ┤");
				break;
				
			case 8:
				printf(" ┴");
				break;
				
			case 9:
				printf(" ┼");
				break;
				
			case BLACKtem:      // ������һ��
				printf(" ▲");
				break;
				
			case WHITEtem:      //������һ��
				printf(" △");
				break;
				
			case BLACK:      //����ͨ��
				printf(" ●");
				break;
				
			case WHITE:
				printf(" ○");  //����ͨ��
				break;

		    case BAN:
			    printf(" *");
				break;
			}
			if(i == SIZE - 1)
			{
				printf("\n");
			}
			
		}
	}
	
	printf("   ");
	for (ary = 'A'; ary < 'A' + SIZE ; ary++)
		printf("%c ",ary);
	
	printf("\n");
}


int iswin(int Board[SIZE][SIZE],int player,int x, int y) {
	int directions[4][2] = {{1,0}, {0,1}, {1,1}, {1, -1}};
	for(int i = 0; i< 4;i++) {
		int count = 1;
		for (int j =1;j <5 ; j++){
			int nx = x + j *directions[i][0];
			int ny = y + j * directions[i][1];
			if(nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && Board[nx][ny]/5 == player/5){
				count++;
			} else {
				break;
			}
		
		}
		for(int j =1 ; j <5; j++) {
			int nx = x - j* directions[i][0];
			int ny = y - j*directions[i][1];
			if(nx >=0&& nx < SIZE && ny >=0&&ny < SIZE && Board[nx][ny]/5 == player/5){
				count++;
			}else{
				break;
			}
		}
		if(count > 4) {
			return 1;
		}
	}
	return 0;
}
int isValidMove(int Board[SIZE][SIZE], int x,int y) {
	if(x>= 0 && x <SIZE && y >= 0 &&y< SIZE && ((Board[x][y] >=1&&Board[x][y]<=9)||Board[x][y] ==BAN)){
		return 0;
	} else {
		return 1;
	}
}

void playGame1() {
	int currentPlayer = BLACK;
	int round = 0;
	while(round < 226) {
		round++;
		bannewLONG(Board);
		bannewsisi(Board);
		bannewsansan(Board);
		DisplayBoard();
		if(currentPlayer == BLACK) {
		printf("BLACK's turn\n");
		} else {
			printf("WHITE's turn\n");
		}

		int x,u,z,l;
		char y;
		scanf(" %c %d", &y, &u);
		z = y - 'A';
		x = 15 - u;
        l = Board[x][z];
		if(isValidMove(Board,x,z)){
			printf("下棋重复 请在别处下棋\n");
			round --;
			continue;
		}
		
		if (currentPlayer == BLACK) 
		{  if(Board[x][z]==BAN){
				printf("此处为禁手 请在别处下棋\n");
				round--;
				continue;
			}
		    
			
		}
		if(currentPlayer == BLACK){
		 for(int i=0;i<=SIZE;i++){
		    for(int j=0;j<=SIZE;j++){
			    if(Board[i][j]==BLACKtem){
				    Board[i][j]=BLACK;
			    }else if(Board[i][j] ==BAN){
					if(j == 0 && i>0 && i<SIZE-1){
						Board[i][j] = 5;
					}else if(i == 0 && j<SIZE -1&&j>0){
						Board[i][j] = 6;
					}else if(j== SIZE -1 && i >0&&i<SIZE -1){
                        Board[i][j] = 7;
					}else if(i==SIZE -1 && j>0 &&j<SIZE -1){
						Board[i][j]= 8;
					}else if(i>0 && i<SIZE -1 &&j>0 &&j<SIZE-1){
						Board[i][j] = 9;
					}
					
				}
		    }
		 }
         Board[x][z] = BLACKtem;
		}else if (currentPlayer == WHITE) {
			for(int i=0;i<=SIZE;i++){
		       for(int j=0;j<=SIZE;j++){
			       if(Board[i][j]==WHITEtem){
				      Board[i][j]=WHITE;
			        }else if(Board[i][j] ==BAN){
					if(j == 0 && i>0 && i<SIZE-1){
						Board[i][j] = 5;
					}else if(i == 0 && j<SIZE -1&&j>0){
						Board[i][j] = 6;
					}else if(j== SIZE -1 && i >0&&i<SIZE -1){
                        Board[i][j] = 7;
					}else if(i==SIZE -1 && j>0 &&j<SIZE -1){
						Board[i][j]= 8;
					}else if(i>0 && i<SIZE -1 &&j>0 &&j<SIZE-1){
						Board[i][j] = 9;
					}
					
				}
		        }
			}
			Board[x][z]=WHITEtem;
		}
		if(iswin(Board,currentPlayer,x,z)) {
			DisplayBoard();
			if(currentPlayer == BLACK){
			printf("BLACK wins!\n");
			break;
			}else{
				printf("WHITE wins!\n");
				break;
			}
		}
		
		if(currentPlayer == BLACK) {
			currentPlayer = WHITE;
		}else {
			currentPlayer = BLACK;
		}
	   
	}
	
}
void playGame2(){
	int p,AIplayer,realplayer;//执黑执白判定符
	printf("请选择对方执黑或执白,执黑请输入1,执白请输入2\n");
	 while (1) { // 使用循环直到获取有效输入
        scanf(" %d", &p);
        if (p == 1) {
            AIplayer = WHITE;
            realplayer = BLACK;
            break; // 有效输入，跳出循环
        } else if (p == 2) {
            AIplayer = BLACK;
            realplayer = WHITE;
            break; // 有效输入，跳出循环
        } else {
            printf("错误输入,请输入1或2\n");
            // 清空输入缓冲区，防止错误输入被重复读取
            while (getchar() != '\n');
        }
		
    }
	int currentplayer = BLACK ;//当前为谁下
	int round = 0;
	while(round<226){
		int x,u,z,l;
		char y;
		round++;
		bannewLONG(Board);
		bannewsisi(Board);
		bannewsansan(Board);//判断禁手位置；
		DisplayBoard();
		printf("是否需要悔棋,要悔输入1,不要悔输入0\n");
        while (round>1) { // 使用循环直到获取有效输入
            scanf(" %d", &p);
            if (p == 1) {
              struct point need = huiqi[round -2];
			  Board[need.x][need.y] = need.score;
              round--;
			  currentplayer=  playerchange(currentplayer);
			  
			  bannewLONG(Board);
		      bannewsisi(Board);
		      bannewsansan(Board);//判断禁手位置；
		      DisplayBoard();
			  printf("是否要再悔,悔输入1,不悔输入0\n");
            } else if (p == 0) {
              
              break; // 有效输入，跳出循环
            } else {
              printf("错误输入,请输入1或0\n");
               // 清空输入缓冲区，防止错误输入被重复读取
              while (getchar() != '\n');
             }
		
        }
		if(currentplayer == BLACK) {
		printf("BLACK's turn\n");
		} else {
			printf("WHITE's turn\n");
		}
		if(AIplayer == currentplayer){
			int u;
			struct point need;
            struct delt maxmax[MAXSIZE];
            struct delt max201[getit];
            struct delt max202[getother];
            struct delt max203[MAXSIZE];
			for (int i = 0; i < MAXSIZE; i++) {
                 maxmax[i].first.x = 0;
                 maxmax[i].first.y = 0;
                 maxmax[i].first.score = 0;
                 maxmax[i].second.x = 0;
                 maxmax[i].second.y = 0;
                 maxmax[i].second.score = 0;
                 maxmax[i].score = 0; // 分差
                 max203[i].first.x = 0;
                 max203[i].first.y = 0;
                 max203[i].first.score = 0;
				 max203[i].second.x = 0;
                 max203[i].second.y = 0;
                 max203[i].second.score = 0;
               
        
                }//初始化
				for(int i =0;i< getit;i++){
                 max201[i].first.x = 0;
                 max201[i].first.y = 0;
                 max201[i].first.score = 0;
				 max201[i].second.x = 0;
                 max201[i].second.y = 0;
                 max201[i].second.score = 0;
				}//初始化
                for(int i = 0;i< getother;i++){
                 max202[i].first.x = 0;
                 max202[i].first.y = 0;
                 max202[i].first.score = 0;
				 max202[i].second.x = 0;
                 max202[i].second.y = 0;
                 max202[i].second.score = 0;
                }//初始化
          
                int score1[SIZE][SIZE]={0};//黑评分;
                int score2[SIZE][SIZE]={0};//白评分;初始化
				if(round==1 ){
					x = 7;
					z = 7; 
					huiqi[round-1].x = need.x;
				    huiqi[round-1].y = need.y;
				    huiqi[round-1].score = Board[need.x][need.y];
				}else{
				u = choosetree( maxmax, Board, AIplayer, score1, score2,max201,max202,max203,round);
				need = finalchoose( max203, u);
				huiqi[round-1].x = need.x;
				huiqi[round-1].y = need.y;
				huiqi[round-1].score = Board[need.x][need.y];
				x =need.x;
				z = need.y;
				}
				printf("%c %d\n", z+'A',15-x);
				

              //给X，Z赋值；
			  //并输出坐标
		}else if(realplayer == currentplayer){
		    scanf(" %c %d", &y, &u);
		    z = y - 'A';
		    x = 15 - u;
            l = Board[x][z];
			
		    if(isValidMove(Board,x,z)){
			   printf("下棋重复 请在别处下棋\n");
			    round --;
			    continue;
		    }
			
		    if (currentplayer == BLACK) {  
				   if(Board[x][z]==BAN){
				   printf("此处为禁手 请在别处下棋\n");
				   round--;
				   continue;
			    }
			}
			huiqi[round-1].x = x;
			huiqi[round-1].y = z;
			huiqi[round-1].score = Board[x][z];
		}
		if(currentplayer == BLACK){
		 for(int i=0;i<=SIZE;i++){
		    for(int j=0;j<=SIZE;j++){
			    if(Board[i][j]==BLACKtem){
				    Board[i][j]=BLACK;
			    }else if(Board[i][j] ==BAN){
					if(j == 0 && i>0 && i<SIZE-1){
						Board[i][j] = 5;
					}else if(i == 0 && j<SIZE -1&&j>0){
						Board[i][j] = 6;
					}else if(j== SIZE -1 && i >0&&i<SIZE -1){
                        Board[i][j] = 7;
					}else if(i==SIZE -1 && j>0 &&j<SIZE -1){
						Board[i][j]= 8;
					}else if(i>0 && i<SIZE -1 &&j>0 &&j<SIZE-1){
						Board[i][j] = 9;
					}
					
				}
		    }
		 }
         Board[x][z] = BLACKtem;
		}else if (currentplayer == WHITE) {
			for(int i=0;i<=SIZE;i++){
		       for(int j=0;j<=SIZE;j++){
			       if(Board[i][j]==WHITEtem){
				      Board[i][j]=WHITE;
			        }else if(Board[i][j] ==BAN){
					if(j == 0 && i>0 && i<SIZE-1){
						Board[i][j] = 5;
					}else if(i == 0 && j<SIZE -1&&j>0){
						Board[i][j] = 6;
					}else if(j== SIZE -1 && i >0&&i<SIZE -1){
                        Board[i][j] = 7;
					}else if(i==SIZE -1 && j>0 &&j<SIZE -1){
						Board[i][j]= 8;
					}else if(i>0 && i<SIZE -1 &&j>0 &&j<SIZE-1){
						Board[i][j] = 9;
					}
					
				}
		        }
			}
			Board[x][z]=WHITEtem;
		}
		if(iswin(Board,currentplayer,x,z)) {
			DisplayBoard();
			if(currentplayer == BLACK){
			printf("BLACK wins!\n");
			break;
			}else{
				printf("WHITE wins!\n");
				break;
			}
		}
		if(currentplayer == BLACK) {
			currentplayer = WHITE;
		}else {
			currentplayer = BLACK;
		}
	   

	}
	
}







void bannewLONG(int Board[SIZE][SIZE]){
	int directions[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};
	int i,j,k,l;
	for (int i=0; i <15;i++){
		for(int j=0; j<15;j++ ){
			if(Board[i][j]/10==0){
				for (int k=0; k<4;k++){
				int count =1;
		        for (int l =1;l <5 ; l++){
			        int nx = i + l *directions[k][0];
			        int ny = j + l * directions[k][1];
			        if(nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && (Board[nx][ny]/10) == 1){
				       count++;
			           } else {
				          break;
			            }

	            }
	            for(int l =1 ; l <5; l++) {
			        int nx = i - l* directions[k][0];
			        int ny = j - l*directions[k][1];
			        if(nx >=0&& nx < SIZE && ny >=0&&ny < SIZE && (Board[nx][ny]/10) == 1){
				       count++;
			           }else{
				         break;
			            }
		        }
		        if(count >= 6) {
			        Board[i][j]=BAN;
		        }
 
			}
			}else{
				continue;
			}
			
		}
	}
	
}
void bannewsisi( int Board[SIZE][SIZE]){
   int directions[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};
   int judge1[6]={0,1,1,1,1,0};
   int judge2[6]={2,1,1,1,1,0};
   int judge3[6]={0,1,1,1,1,2};//数组元素有六个的四四判断数组

   int judge4[7]={2,1,0,1,1,1,2};
   int judge5[7]={2,1,0,1,1,1,0};
   int judge6[7]={0,1,0,1,1,1,2};
   int judge7[7]={0,1,0,1,1,1,0};
   int judge8[7]={2,1,1,0,1,1,2};
   int judge9[7]={2,1,1,0,1,1,0};
   int judge10[7]={0,1,1,0,1,1,2};
   int judge11[7]={0,1,1,0,1,1,0};//数组元素有七个的四四判断数组
	int i,j,k,l,q;
	for (int i=0; i <15;i++){
		for(int j=0; j<15;j++ ){
			int countlive4 = 0;
			int p;
			p = Board[i][j];
			if(Board[i][j]/10==0){
			 
			  Board[i][j] = BLACK;//虚拟下一个子
			}else{
				continue;
			}
			for (int k=0; k<4;k++){
				
		        for (int l =0;l <6 ; l++){	
					 int count1 =0;
		             int count2 =0;
		             int count3 =0;							 
			         int nx = i + l *directions[k][0];
			         int ny = j + l * directions[k][1];
					 for (int q=0;q <6; q++){
				        int ux = nx - q*directions[k][0];
				        int uy = ny - q*directions[k][1];
				        if(ux >= 0 && ux < SIZE && uy >= 0 && uy < SIZE ){
					        if ((Board[ux][uy]/10) == judge1[q]){
						        count1++;
					           } 
					        if((Board[ux][uy]/10) == judge2[q]){
						        count2++;
					           }
					        if((Board[ux][uy]/10) == judge3[q]){
						        count3++;
					           }
				          }
					    }
					 if(count1 == 6 || count2 == 6 || count3 == 6){
				            countlive4++;
			           }
	            }
	            for (int l =0;l <7 ; l++){
		             int count4 =0;
		             int count5 =0;
		             int count6 =0;
		             int count7 =0;
		             int count8 =0;
		             int count9 =0;
		             int count10 =0;
		             int count11 =0;
			   
			         int nx = i + l *directions[k][0];
			         int ny = j + l * directions[k][1];
			        for (int q=0;q <7; q++){
				        int ux = nx - q*directions[k][0];
				        int uy = ny - q*directions[k][1];
				        if(ux >= 0 && ux < SIZE && uy >= 0 && uy < SIZE ){
					      if ((Board[ux][uy]/10) == judge4[q]){
						     count4++;
					       } 
					      if((Board[ux][uy]/10) == judge5[q]){
						     count5++;
					       }
					      if((Board[ux][uy]/10) == judge6[q]){
						    count6++;
					       }
					      if ((Board[ux][uy]/10) == judge7[q]){
						    count7++;
					       }
					      if ((Board[ux][uy]/10) == judge8[q]){
						    count8++;
					       }
					     if ((Board[ux][uy]/10) == judge9[q]){
						    count9++;
					       }
					     if ((Board[ux][uy]/10) == judge10[q]){
						    count10++;
					       }
					     if ((Board[ux][uy]/10) == judge11[q]){
						    count11++;
					       }
				        }
			        }
			    if(count4 == 7 || count5 == 7 || count6 == 7 ||count7 == 7||count8 == 7||count9 == 7||count10 == 7||count11 == 7){
				    countlive4++;
			    }			
	            }
			}
            if(countlive4 >1){
		      
		       Board[i][j]=BAN;
			    
	        }else {
              Board[i][j]=p;
		      
	        }
	
	    }
	}
}

void bannewsansan(int Board[SIZE][SIZE]){
	int directions[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};
	int judge12[6]={0,1,1,0,1,0};
    int judge13[6]={0,1,0,1,1,0};
    int judge14[7]={0,0,1,1,1,0,0};
    int judge15[7]={2,0,1,1,1,0,0};
    int judge16[7]={0,0,1,1,1,0,2};
	int i,j,k,l,q;
	for (int i=0; i <15;i++){
		for(int j=0; j<15;j++ ){
			int countlive3=0;
			int p;
			p=Board[i][j];
			if(Board[i][j]/10==0){
			  
			  Board[i][j] = BLACK;//虚拟下一子
			}else{
				continue;
			}
            for (int k=0; k<4;k++){
				
		        for (int l =0;l <6 ; l++){	
					 int count12 =0;
		             int count13 =0;							 
			         int nx = i + l *directions[k][0];
			         int ny = j + l * directions[k][1];
					 for (int q=0;q <6; q++){
				        int ux = nx - q*directions[k][0];
				        int uy = ny - q*directions[k][1];
				        if(ux >= 0 && ux < SIZE && uy >= 0 && uy < SIZE ){
					        if ((Board[ux][uy]/10) == judge12[q]){
						        count12++;
					           } 
					        if((Board[ux][uy]/10) == judge13[q]){
						        count13++;
					           }
				          }
					    }
					    if(count12 == 6 || count13 == 6 ){
				               countlive3++;
			              }
	            }
	            for (int l =0;l <7 ; l++){
		             int count14 =0;
		             int count15 =0;
		             int count16 =0;
		             
			         int nx = i + l *directions[k][0];
			         int ny = j + l * directions[k][1];
			        for (int q=0;q <7; q++){
				        int ux = nx - q*directions[k][0];
				        int uy = ny - q*directions[k][1];
				        if(ux >= 0 && ux < SIZE && uy >= 0 && uy < SIZE ){
					      if ((Board[ux][uy]/10) == judge14[q]){
						     count14++;
					       } 
					      if((Board[ux][uy]/10) == judge15[q]){
						     count15++;
					       }
					      if((Board[ux][uy]/10) == judge16[q]){
						     count16++;
					       }
					      
				        }
			        }
			    if(count14 == 7 || count15 == 7 || count16 == 7 ){
				    countlive3++;
			    }			
	            }
			}
            if(countlive3 >1){
		      
		       Board[i][j]=BAN;
			   
	        }else {
              Board[i][j]=p;
		     
	        }
	
		}
	}
}
	
int  judgechange(int flag){
    if(flag =1){
        return 8;
    }else if(flag =0 ){
        return 5;
    }
}//判断这行有无相同棋的赋值函数
int playerchange(int player){
    if(player == BLACK){
        return WHITE;
    }else if(player == WHITE){
        return BLACK;
    }
}//转换玩家函数

void evaluate(int Board[SIZE][SIZE],int player,int score1[SIZE][SIZE],int score2[SIZE][SIZE] ){//连子的分数用次方
    int directions[4][2] = {{1,0}, {0,1}, {1,1}, {1, -1}};
   
    int t[SIZE][SIZE]={0};//替代函数，最后用来赋值给黑白评分
    for(int i =0;i<15;i++){
        for(int j=0;j<15;j++){
			 int m =Board[i][j];
            if(Board[i][j]/10 == 0  ||(Board[i][j]== BAN && player == WHITE)){
               
                Board[i][j] = player;
            }else {
                t[i][j] = -infinite;
				if(player == WHITE){
					score2[i][j] = t[i][j];
				}else if(player == BLACK){
					score1[i][j] = t[i][j];
				}
                continue;
            }
            if(iswin(Board, player, i, j)==1){
                t[i][j]= infinite;
				if(player == WHITE){
					score2[i][j] = t[i][j];
				}else if(player == BLACK){
					score1[i][j] = t[i][j];
				}
				Board[i][j] = m;
                continue;
            }else {//单子相加
                int sumt =0;//总分
				int lian3 = 0;//连棋为三个的
				int huolian3 = 0 ;//？
				int huolian4 = 0 ;//？
				
                for(int k=0;k<4;k++){
                    int  positive= 0;//每一行的分数计量
                    int countlian=1;
					int escape1 = 0;//是否有对方棋子阻挡
					int escape2 = 0;//第二个方向
					int countok = 1;//判断这一行是否有五个以上的空格
                    int specialescape1 = 0;//是否是被紧贴着阻挡
                    int specialescape2 = 0;//同理，第二行。
                    int countscore = 100;//分数
                    int flag = 1;//判断棋子是否连起来的符号
                    int count = 0;//有空格分开后连棋的数目
					int count3 = 0;//跳着的三？？
					int block1 = 0;//判断是否有临接空格
					int block2 = 0;//判断是否有临接空格
                    for(int l=1;l<6;l++){                      
                        int nx = i+l*directions[k][0];
                        int ny = j+l*directions[k][1];
                        //连着的更具优势要在函数上体现它 
                        
						
                        if(nx >0 && nx <SIZE &&ny >0 && ny <SIZE){
                            if(Board[nx][ny]/5 == player/5){//除以五的操作是为了保证white与whitetem是统一的以及black
                                if(flag == 1){
                                    countlian++;
									countok++;
									
                                    //countlian不可能到l=5，因为如果到五一定会被iswin检测到
                                }else {
                                    count++;
									countok++;
                                    if(l == 5){
                                        positive += pow(5,count)*countscore;
                                    }
                                }
                               
                            } else if(Board[nx][ny] == BAN &&player/5 == BLACK/5){
								escape1 = 1;
                                break;//由于阻挡效应，阻挡后的棋对下在这个位置基本无用
                            } else if (Board[nx][ny]/5 == playerchange(player)/5){
								if(flag == 1&&countlian == 1){
                                   specialescape1 = 1;
                                }//主要是为了单个棋子断开对方的连棋
								escape1 = 1;
                                break;
                            } else{
								countok++;
								if(flag == 1){
                                    flag = 0;
                                    countscore = countscore/10;
                                    positive += countscore/10;
									block1 = 0;
                                }else {
									if(countscore == 10&&count >1){
										count3++;
									}
                                    positive += pow(5,count)*countscore;
                                    countscore = countscore/10;
                                    positive += countscore/10;
                                    count = 0;
                                }
                            }
                        }else{
                            break;
                        }    
                    }
                 count = 0;
                 flag =1;
                 countscore =100; //重新初始化  
                for(int l=1;l<6;l++){
                    int nx = i-l*directions[k][0];
                    int ny = j-l*directions[k][1];

                    
                    if(nx >0 && nx <SIZE &&ny >0 && ny <SIZE){
                        if(Board[nx][ny]/5 == player/5){//除以五的操作是为了保证white与whitetem是统一的以及black
                            if(flag == 1){
                              countlian++;
							  countok++;
                           }else {
                               count++;
							   countok++;
                               if(l == 5){
                                positive +=pow(5,count)*countscore;
                               }
                           }
                        } else if(Board[nx][ny] == BAN &&player/5 == BLACK/5){
								escape2 =1;
                            break;//由于阻挡效应，阻挡后的棋对下在这个位置基本无用
                        } else if (Board[nx][ny]/5 == playerchange(player)/5){
							    if(flag == 1&&countlian == 1){
                                  specialescape2 = 1;
                           }
								escape2 =1;
                            break;
                        } else{
							countok++;
							if(flag == 1){
                                flag =0;
                                positive += pow(5,countlian)*countscore;
                                countscore=countscore/10;
                                positive += countscore/10;
								block2 = 1;
                            }else {
								if(countscore == 10&&count >1){
										count3=1;
									}
                                positive += pow(5,count)*countscore;
                                countscore = countscore/10;
                                positive += countscore/10;
                                count = 0;
                            }
                           
                        }
                    }else{
                        break;
                    }   
                }
				int position = 1.5;
				if(countlian < 3){
                if(i<10&&i>5&&j>5&&j<10){
					position = 1.5;
				}else if(i>5&&i<10&&(j<5||j>10)){
					position =0.8;
				}else if(j<5&&j>10&&(i<5||i>10)){
					position =0.8;
				}else{
					position=0.8*0.8;
				}
				}
				if(countlian >1){
					specialescape1 = 0; //考虑到由于后续countlian会加起来
				}
				if(countok >4){
					if((escape1 ==1)&&(escape2 == 1)){
						positive /=9;
					}else if((escape1 ==1)&&(escape2 == 0)){
						positive /=3;
					}else if((escape1 ==0)&&(escape2 == 1)){
						positive /=3;
					}
				}else {
                    
                    if((specialescape1 == 1)&&(specialescape2 == 0)){
                        int count1 = 0;
						int countok = 0;
                       for(int l = 1;l<6;l++){
                        int nx = i+l*directions[k][0];
                        int ny = j+l*directions[k][1];
                        
                        if(nx >0 && nx <SIZE &&ny >0 && ny <SIZE){
                           
									
                                    //countlian不可能到l=5，因为如果到五一定会被iswin检测到
                         if (Board[nx][ny]/5 == playerchange(player)/5){
								count1++;
                                countok++;
                            } else if((Board[nx][ny]/10 == 0)&&(player == WHITE && Board[nx][ny] == BAN)){
								countok++;
								break;
                            }else{
								break;
							}
                        }else{
                            break;
                        }    
                       
                       
                    }
                    if(count1 == 3&&countok >3){
                          positive = 12500;
                       }else if(count1 >3&&countok>3){
                          positive = 62500;
                       }else{
                        positive = 0;
                       }
                    }else if((specialescape1 == 0)&&(specialescape2 == 1)){
                        int count1 = 0;
						int countok = 0;
                        for(int l = 1;l<6;l++){
                        int nx = i-l*directions[k][0];
                        int ny = j-l*directions[k][1];
                     
                        if(nx >0 && nx <SIZE &&ny >0 && ny <SIZE){
                           
									
                                    //countlian不可能到l=5，因为如果到五一定会被iswin检测到
                         if (Board[nx][ny]/5 == playerchange(player)/5){
								count1++;
                                countok++;
                            } else if((Board[nx][ny]/10 == 0)&&(player == WHITE && Board[nx][ny] == BAN)){
								countok++;
								break;
                            }else{
								break;
							}
                        }else{
                            break;
                        }    
                       
                      
                    }
                     if(count1 == 3&&countok >3){
                          positive = 12500;
                       }else if(count1 >3&&countok >3){
                          positive = 62500;
                       }else{
                        positive = 0;
                       }
                    }else if((specialescape1 == 1)&&(specialescape2 == 1)){
                         int count1 = 0;
						 int countok = 0;
                        for(int l = 1;l<6;l++){
                        int nx = i+l*directions[k][0];
                        int ny = j+l*directions[k][1];
                       
                        if(nx >0 && nx <SIZE &&ny >0 && ny <SIZE){         
                         if (Board[nx][ny]/5 == playerchange(player)/5){
								count1++;
                                countok++;
                            } else if((Board[nx][ny]/10 == 0)&&(player == WHITE && Board[nx][ny] == BAN)){
								countok++;
								break;
                            }else{
								break;
							}
                        }else{
                            break;
                        }    
                       
                       
                    }
                    for(int l = 1;l<6;l++){
                        int nx = i-l*directions[k][0];
                        int ny = j-l*directions[k][1];
                        if(nx >0 && nx <SIZE &&ny >0 && ny <SIZE){
                           
									
                                    
                         if (Board[nx][ny]/5 == playerchange(player)/5){
								count1++;
                                countok++;
                            } else if((Board[nx][ny]/10 == 0)&&(player == WHITE && Board[nx][ny] == BAN)){
								countok++;
								break;
                            }else{
								break;
							}
                        }else{
                            break;
                        }    
                       
                      
                    }
                     if(count1 == 3&&countok > 3){
                          positive = 12500;
                       }else if(count1 >3&&countok > 3){
                          positive = 62500;
                       }else{
                        positive = 0;
                       }
                    }else {
                        positive = 0;
                    }
					
				}
				
				
                sumt += positive*position;

                if(((countlian == 3 )&&(countok > 4)&&(block1==1&&block2 == 1))||((count3 ==1)&&(countok >4 )&&(block1==1&&block2 == 1))){
					huolian3++;
				}else if ((countlian > 3)&&(countok>4)){
					huolian4++;
				}
                }
				if(player==WHITE){
					if((huolian3+huolian4)>1){
                        sumt *=2;
					}
				}else if(player == BLACK){
					if(huolian3 == 1&&huolian4 == 1){
						sumt *=2;
					}
				}
                t[i][j] = sumt;
                Board[i][j] = m;
                if(player == WHITE){
					score2[i][j] = t[i][j];
				}else if(player == BLACK){
					score1[i][j] = t[i][j];
				}
                
            }
        }
    }
	
   
}

int  startchoose(int Board[SIZE][SIZE],int currentplayer,int score1[SIZE][SIZE],int score2[SIZE][SIZE],struct delt maxmax[MAXSIZE],int round){
    int l = 0;//用来存储Board
    int k = 0;//maxmax的序标
    int r =0 ;//判断黑白棋哪个类型
    //存储所有的分差
    
    evaluate(Board,currentplayer,score1,score2);
    for (int i=0;i<SIZE;i++){
        for(int j =0;j<SIZE;j++){
			if(round <3&&(i<6||i>8)&&(j<6||j>8)){
				continue;
			}else if((round>2&&round<7)&&(i<4||i>10)&&(j<4||j>10)){
				continue;
			}
            if(currentplayer == BLACK){
                if(score1[i][j]== -infinite){
                    continue;
                }else if(score1[i][j] == infinite){
					 struct delt different;
					 different.first.x = i;
					 different.first.y = j;
					 different.second.x = 0;
					 different.second.y = 0;
					 different.score = infinite;
					 maxmax[0] = different;
					 return -1;//必赢了就要直接跳出
					 
				}
				else {
                    
                    struct point maxwhite;
                    struct point maxblack;
                    struct delt  different;
                    l = Board[i][j];
                    Board[i][j] = BLACK;
                    r=playerchange(currentplayer);
                    evaluate(Board,r,score1,score2);
                    maxwhite = maxchoose(score2);
					if(maxwhite.score == infinite){
						Board[i][j] = l;
						continue;//对方赢了说明我们棋子策略不对，肯定不能纳入考虑范围内，
					}
                    maxblack.x = i;
                    maxblack.y = j;
                    maxblack.score = score1[i][j];
                    different.first = maxblack;
                    different.second = maxwhite;
                    different.score = maxwhite.score -maxblack.score;
                    maxmax[k]= different;
                    k++;
                    Board[i][j]=l;
                    
                                                            
                }
            }else if(currentplayer == WHITE){
                if(score2[i][j] == -infinite){
                    continue;
                }else if(score2[i][j] == infinite){
					 struct delt different;
					 different.first.x = i;
					 different.first.y = j;
					 different.second.x = 0;
					 different.second.y = 0;
					 different.score = infinite;
					 maxmax[0] = different;
					 return -1;//必赢了就要直接跳出
					 
				}
				else{
                    struct point max2;
                    struct point max1;
                    struct delt  different;
                    l = Board[i][j];
                    Board[i][j] = WHITE;
                    r=playerchange(currentplayer);
                    evaluate(Board,r,score1,score2);
                    max2 = maxchoose(score1);
					if(max2.score == infinite){
						Board[i][j]=l;
						continue;
					}
                    max1.x = i;
                    max1.y = j;
                    max1.score = score2[i][j];
                    different.first = max1;
                    different.second = max2;
                    different.score = max2.score -max1.score;
                    maxmax[k]= different;
                    k++;
                    Board[i][j]=l;
                    
                }
            }
        }
    }
    return k;

}//在maxchoose之前的一些起始操作
struct point  maxchoose(int score[SIZE][SIZE]){
    struct  point max;
	 max.score = score[0][0];
	 max.x = 0;
	 max.y = 0;
    for(int i =0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
			if(max.score == infinite){
				return max;
			}
            if(max.score > score[i][j]){
                continue;
            }else if(max.score < score[i][j]){
                max.score = score[i][j];
                max.x = i;
                max.y = j;
            }else{
				double distance1,distance2;
                distance1 = sqrt(pow(max.x - 7.5, 2) + pow(max.y - 7.5, 2));
                distance2 = sqrt(pow(i - 7.5, 2) + pow(j - 7.5, 2));
                if(distance1 < distance2){
                    continue;
                }else if(distance1 > distance2){
                    max.score = score[i][j];
                    max.x = i;
                    max.y = j;
                }else{
                    continue;
                }
               

            }
        }
    }
    return max;
}
void bubbleSort(struct delt maxmax[],int u){
    int i,j;
    struct delt temp;
    for(i=0;i<u-1;i++){
        for(j =0; j<u-i-1;j++){
            if(maxmax[j].score>maxmax[j+1].score){
                  temp = maxmax[j];
                  maxmax[j]=maxmax[j+1];
                  maxmax[j+1]= temp;
            }else if(maxmax[j].score == maxmax[j+1].score){
            struct point maxneedj = maxmax[j].first;
            struct point maxneedj1 = maxmax[j+1].first;
            float  distance1 = sqrt(pow(maxneedj.x - 7.5, 2) + pow(maxneedj.y - 7.5, 2));
            float  distance2 = sqrt(pow(maxneedj1.x - 7.5, 2) + pow( maxneedj1.y- 7.5, 2));
               if(distance1>distance2){
                  temp = maxmax[j];
                  maxmax[j]=maxmax[j+1];
                  maxmax[j+1]= temp;
               }
            }
        }
    }
}


int choosetree(struct delt maxmax[MAXSIZE],int Board[SIZE][SIZE],int currentplayer,int score1[SIZE][SIZE],int score2[SIZE][SIZE],
struct delt max201[getit], struct delt max202[getother], struct delt max203[MAXSIZE],int round){
    int k1 =0 ;//maxmax数组有效数总长度
    int u =0;
    k1=startchoose(Board,currentplayer,score1,score2,maxmax,round);//把maxmax填充了，且还输出了长度数k
	if(k1 == 0){
		return -1;//即对方能赢而我方不能赢
	}else if(k1 == -1){
		max203[0]=maxmax[0];
		return -2;//必胜棋就是要必胜下
	}
    //bubbleSort(maxmax,k1);//由于是第二步减第一步，所以取最小的就是取最大的
	bubblesort1(maxmax,k1,getit);
    for(int t =0;t<getit;t++){
        if(t!= k1){
            max201[t]=maxmax[t];
        }else{
			break;
		}
    }//将最大的20个传给了max201
    //下一轮计算
    for(int i = 0;i<getit;i++){
        if(i!=k1){
            int k2=0;//maxmax长度
            struct point need1;//第一步棋
            need1 = max201[i].first;
            int l1 =0;
            int p1 = 0;//玩家身份提示
            l1 =Board[need1.x][need1.y];
            Board[need1.x][need1.y] = currentplayer;
            p1 = playerchange(currentplayer);
            k2=startchoose(Board,p1,score1,score2,maxmax,round);
			if(k2 == 0){
				Board[need1.x][need1.y]=l1;
				max203[0] =max201[i];//即对方没办法反制我们获胜
				return -2;
			}else if(k2 == -1){
                Board[need1.x][need1.y]=l1;
				continue;
			}
            //bubbleSort(maxmax,k2);
			bubblesort1(maxmax,k2,getother);
            for(int t=0;t<getother;t++){
                if(t != k2){
					
                    max202[t]=maxmax[t];
				
                }else{
					break;
				}
            }
            //第三轮也是最后一轮
            for(int j = 0;j<getother;j++){
             if(j!=k2){
            int k3=0;
            int l2 =0;
            int p2 = 0;//玩家身份提示
			
            l2 =Board[max202[j].first.x][max202[j].first.y];
            Board[max202[j].first.x][max202[j].first.y] = p1;//虚拟下一步
            p2 = playerchange(p1);
            k3=startchoose(Board,p2,score1,score2,maxmax,round);
			if(k3 == 0){
				Board[max202[j].first.x][max202[j].first.y] = l2;
				break;
			}else if(k3 ==-1){
				Board[max202[j].first.x][max202[j].first.y] = l2;
				Board[need1.x][need1.y]=l1;
				max203[0] = max201[i];
				return -2;
			}
            //bubbleSort(maxmax,k3);
			bubblesort1(maxmax,u,1);
            if(u == 0){
               max203[u].score = maxmax[0].score;
               max203[u].first = max201[i].first;
               max203[u].second = max201[i].second;
               u++;
            }else if(u == 1){
               if(max203[0].score >maxmax[0].score){
                max203[0].score = maxmax[0].score;
                max203[0].first = max201[i].first;
                max203[0].second = max201[i].second;
               }else if(max203[0].score == maxmax[0].score){
                    float  distance1 = sqrt(pow(max203[0].first.x - 7.5, 2) + pow(max203[0].first.y - 7.5, 2));
                    float  distance2 = sqrt(pow(maxmax[0].first.x - 7.5, 2) + pow( maxmax[0].first.y- 7.5, 2));
                    if(distance1>distance2){
                        max203[0].score = maxmax[0].score;
                        max203[0].first = max201[i].first;
                        max203[0].second = max201[i].second;
                    }
               }
            }
         
            
            Board[max202[j].first.x][max202[j].first.y] = l2;//复原
            }
        }
        Board[need1.x][need1.y]=l1;
    }else{
		break;
	}
            
    }
    return u;
    }
struct point finalchoose(struct delt max203[MAXSIZE],int u){
	if(u == -2){
		return max203[0].first;
	}else if(u == -1 || u == 0){
		struct point k ={0,0,0};
		return k;
	}
    struct point need1;
    need1 =  max203[0].first;
    return need1;
}//输出最后需要的坐标

void bubblesort1(struct delt maxmax[MAXSIZE],int u,int get/*get是我们所取的棋子数目*/){
	if(u>get){
	bubbleSort(maxmax,get);
	for(int i = get;i< u;i++){
		if(maxmax[i].score >maxmax[get].score){
           continue;
		}else {
			for(int j = 0;j< get;j++){
              if(maxmax[j].score < maxmax[i].score){
				continue;
			  }else if(maxmax[j].score == maxmax[i].score){
				float  distance1 = sqrt(pow(maxmax[j].first.x - 7.5, 2) + pow(maxmax[j].first.y - 7.5, 2));
                float  distance2 = sqrt(pow(maxmax[i].first.x - 7.5, 2) + pow( maxmax[i].first.y- 7.5, 2));
				if(distance1 <distance2){
					continue;
				}else {
                    for(int l = j;l<get;l++){
						maxmax[l+1]=maxmax[l];
					}
					maxmax[j] =maxmax[i];
					break;
				}
			  }else if(maxmax[j].score>maxmax[i].score){
				   for(int l = j;l<get;l++){
						maxmax[l+1]=maxmax[l];
					}
					maxmax[j] =maxmax[i];
					break;
			  }  
			}
		}
	}
	}else {
		bubbleSort(maxmax,u);
	}
}