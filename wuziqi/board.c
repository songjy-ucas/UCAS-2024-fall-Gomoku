#include "play.h"

/*提示最新一步为三角*/void changepass(){
	int i,j;
	for(i=0;i<=SIZE;i++){
		for(j=0;j<=SIZE;j++){
			if(Board[i][j]==BLACKtem){
				Board[i][j]=BLACK;
			}
			else if(Board[i][j]==WHITEtem){
				Board[i][j]=WHITE;
			}
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
				
			case BLACKtem:      
				printf(" ▲");
				break;
				
			case WHITEtem:      
				printf(" △");
				break;
				
			case BLACK:      
				printf(" ●");
				break;
				
			case WHITE:
				printf(" ○");  
				break;
			}
			if(i == SIZE-1 )
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

/*判断胜负（判断五连）,黑五连则返回1，白五连则返回2*/int iswin(int x,int y,int z){
	/*黑*/if(z == 4){
	 for (int i = 0; i < 4; i++) {
        int count = 1; // 连子数，包括当前位置

        // 向一个方向查找
        int dx = direction[i][0];
        int dy = direction[i][1];
        while (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE && (Board[x + dx][y + dy] == BLACK||Board[x + dx][y + dy] == BLACKtem)) {
            count++;
            dx += direction[i][0];
            dy += direction[i][1];
        }

        // 向相反方向查找
        dx = -direction[i][0];
        dy = -direction[i][1];
        while (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE && (Board[x + dx][y + dy] == BLACK||Board[x + dx][y + dy] == BLACKtem)) {
            count++;
            dx -= direction[i][0];
            dy -= direction[i][1];
        }
		if(count==5){
			return 1;
			break;
		}
	  }
	 }
	 else {
        int count = 1; // 连子数，包括当前位置

        // 向一个方向查找
        int dx = direction[z][0];
        int dy = direction[z][1];
        while (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE && (Board[x + dx][y + dy] == BLACK||Board[x + dx][y + dy] == BLACKtem)) {
            count++;
            dx += direction[z][0];
            dy += direction[z][1];
        }

        // 向相反方向查找
        dx = -direction[z][0];
        dy = -direction[z][1];
        while (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE && (Board[x + dx][y + dy] == BLACK||Board[x + dx][y + dy] == BLACKtem)) {
            count++;
            dx -= direction[z][0];
            dy -= direction[z][1];
        }
		if(count==5){
			return 1;
		}		
	 }//读取某一个方向

	 /*白*/for (int i = 0; i < 4; i++) {
        int count = 1; // 连子数，包括当前位置

        // 向一个方向查找
        int dx = direction[i][0];
        int dy = direction[i][1];
        while (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE && (Board[x + dx][y + dy] == WHITE||Board[x + dx][y + dy] == WHITEtem)) {
            count++;
            dx += direction[i][0];
            dy += direction[i][1];
        }

        // 向相反方向查找
        dx = -direction[i][0];
        dy = -direction[i][1];
        while (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE && (Board[x + dx][y + dy] == WHITE||Board[x + dx][y + dy] == WHITEtem)) {
            count++;
            dx -= direction[i][0];
            dy -= direction[i][1];
        }
		if(count==5){
			return 2;
			break;
		}
	 }
}


