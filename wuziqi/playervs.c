#include"play.h"

/*人人对战*/void playervs(){
    char y;
	int x;
    int BorW=0;//黑还是白落子


	InitBoardArray();
	DisplayBoard();

int rounds;//轮数
for(rounds=0;;rounds++){
	
	/*黑棋下*/if(BorW==0){
	scanf("%c%d",&y,&x);  
	getchar();  //缓冲区的换行符吸收掉
	changepass();
    
    if(Board[SIZE-x][y-'A']==BLACK||Board[SIZE-x][y-'A']==WHITE){
		printf("You can't place here\n");
	}
	else if((SIZE-x<0||SIZE-x>14)||(y-'A'<0||y-'A'>14)){
		printf("You can't place here\n");
	}
    else {
	  system("cls");
	  Board[SIZE-x][y-'A'] = BLACKtem;
	  BorW=1;	
	DisplayBoard();
	printf("黑冲四数：%d\n",getfour_bad(SIZE-x,y-'A',4));
	printf("黑活四数：%d\n",getfour_good(SIZE-x,y-'A',4));
	printf("黑长连数：%d\n",getlong(SIZE-x,y-'A'));
	printf("黑活三数：%d\n",getthree_good(SIZE-x,y-'A',4));
	if(iswin(SIZE-x,y-'A',4) ==1)
	   {
		printf("%s","The black is win.\n");
		break;
	   }
	//if(forbid(SIZE-x,y-'A')==1){break;}
     }
   } 
   /*白棋下*/if(BorW==1){
    scanf("%c%d",&y,&x);  
	getchar();  //缓冲区的换行符吸收掉
	changepass();
   
    if(Board[SIZE-x][y-'A']==BLACK||Board[SIZE-x][y-'A']==WHITE){
		printf("You can't place here\n");
	}
	else if((SIZE-x<0||SIZE-x>14)||(y-'A'<0||y-'A'>14)){
		printf("You can't place here\n");
	}
    else { 
	  system("cls");
	  Board[SIZE-x][y-'A'] = WHITEtem;
	  BorW=0;	
	DisplayBoard();
		
    if(iswin(SIZE-x,y-'A',0) ==2)
	   {
		printf("%s","The white is win.\n");
		break;
	   }
	  }
	}
 }
}
