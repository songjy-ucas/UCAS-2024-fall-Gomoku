#include"play.h"

/*读取活三*/int getthree_good(int x,int y,int z){
 /*四个方向遍历*/if(z == 4){
  int num=0;
  for (int i = 0; i < 4; i++) {
    int dxpo = direction[i][0];
    int dypo = direction[i][1];
    int check = 0;//用于检查正向有没有活四，如果正向试落子可以活四就不用看反向
    while (x + dxpo >= 0 && x + dxpo < SIZE && y + dypo >= 0 && y + dypo < SIZE && (Board[x + dxpo][y + dypo] == BLACK||Board[x + dxpo][y + dypo] == BLACKtem)) {
            dxpo += direction[i][0];
            dypo += direction[i][1];
        }
    if(x + dxpo < 0 || x + dxpo == SIZE || y + dypo < 0 || y + dypo == SIZE || Board[x + dxpo][y + dypo] == WHITE){;}//读到白子或边界就不可能活三
    else {
        int store1 = Board[x + dxpo][y + dypo];
        Board[x + dxpo][y + dypo] = BLACK;

        DisplayBoard();

        if(getfour_good(x + dxpo,y + dypo,i) == 1){
           // printf("run1\n");
            /*确保这个试落子不是禁手*/if(getthree_good(x + dxpo,y + dypo,4) <= 1 && getfour_bad(x + dxpo,y + dypo,4)+getfour_good(x + dxpo,y + dypo,4) <=1 && getlong(x + dxpo,y + dypo) == 0){ 
                num++;
                check++;
               // printf("1%d\n",num);//检查程序用的
         }//一定要先是可能的四，再检验这个点是不是禁手，否则会无限进行下去
        }
        Board[x + dxpo][y + dypo] = store1;//还原空子

        //DisplayBoard();

    }//正向

    // printf("2%d\n",num);//检查程序用的  

    /*避免一行里面算两个活三*/if(check == 0){
    int dxne = -direction[i][0];
    int dyne = -direction[i][1];
    while (x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && (Board[x + dxne][y + dyne] == BLACK||Board[x + dxne][y + dyne] == BLACKtem)) {
            dxne -= direction[i][0];
            dyne -= direction[i][1];
        }
    if(x + dxne < 0 || x + dxne == SIZE || y + dyne < 0 || y + dyne == SIZE || Board[x + dxne][y + dyne] == WHITE){;}//读到白子就不可能活三
    else {
        int store1 = Board[x + dxne][y + dyne];
        Board[x + dxne][y + dyne] = BLACK;

        //DisplayBoard();

        if(getfour_good(x + dxne,y + dyne,i) == 1){
            //  printf("run2\n");
              /*确保这个试落子不是禁手*/if(getthree_good(x + dxne,y + dyne,4) <= 1 && getfour_bad(x + dxne,y + dyne,4)+getfour_good(x + dxne,y + dyne,4) <=1 && getlong(x + dxne,y + dyne) == 0){
             num++;
            // printf("3%d\n",num);//检查程序用的
         }
        }
        Board[x + dxne][y + dyne] = store1;//还原空子

        //DisplayBoard();   //检测用的，正式程序不需要

      }//反向

      

    }   
  }
      return num;
 }


}

/*读取冲三*/int getthree_bad(int x,int y,int z){
    int j;//j记录冲三
    
}

/*读取活四*/int getfour_good(int x,int y,int z){
  /*四个方向遍历*/
 if(z == 4){
  int num=0;
  for (int i = 0; i < 4; i++) {
        int count1 = 1;//连子数,包括当前位置
        int count2 = 0;//正向空子数
        int count3 = 0;//反向空子数

        // 向一个方向查找
        int dxpo = direction[i][0];
        int dypo = direction[i][1];
        while (x + dxpo >= 0 && x + dxpo < SIZE && y + dypo >= 0 && y + dypo < SIZE && (Board[x + dxpo][y + dypo] == BLACK||Board[x + dxpo][y + dypo] == BLACKtem)) {
            count1++;
            dxpo += direction[i][0];
            dypo += direction[i][1];
        }

        // 向相反方向查找
        int dxne = -direction[i][0];
        int dyne = -direction[i][1];
        while (x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && (Board[x + dxne][y + dyne] == BLACK||Board[x + dxne][y + dyne] == BLACKtem)) {
            count1++;
            dxne -= direction[i][0];
            dyne -= direction[i][1];
        }

        // 判断连子数
        if (count1==4) {
        /*判断空子数*/  while (x + dxpo >= 0 && x + dxpo < SIZE && y + dypo >= 0 && y + dypo < SIZE && Board[x + dxpo][y + dypo] <=9 && Board[x + dxpo][y + dypo] >= 1) {
             count2++;
             dxpo += direction[i][0];
             dypo += direction[i][1];
           }
           while (x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && Board[x + dxne][y + dyne] <=9 && Board[x + dxne][y + dyne] >= 1) {
             count3++;
             dxne -= direction[i][0];
             dyne -= direction[i][1];
           }
           if(count2 >= 2 && count3 >= 2){
             num++;
           }//00111100型活四
           else{
            if(count2 ==1 && count3 >= 2){
                if(x + dxpo >= 0 && x + dxpo < SIZE && y + dypo >= 0 && y + dypo < SIZE && (Board[x + dxpo][y + dypo] == BLACK||Board[x + dxpo][y + dypo] == BLACKtem)){
                    ;
                }
                else {
                    num++;
                }
            }
            else if(count3 ==1 && count2 >= 2){
                if(x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && (Board[x + dxne][y + dyne] == BLACK||Board[x + dxne][y + dyne] == BLACKtem)){
                    ;
                }
                else {
                    num++;
                }
            }
            else if(count2 ==1 &&count3 == 1){
                if ((x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && Board[x + dxne][y + dyne] == WHITE) && (x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && Board[x + dxne][y + dyne] == WHITE))
                {
                    num++;
                }
                else {
                    ;
                }
                
            }
            else{
                ;
            }//避免10111100;00111101棋形
           }
        }
    }
    return num;
  }
  /*单个方向*/else {
        int yorn;
        int count1 = 1;//连子数,包括当前位置
        int count2 = 0;//正向空子数
        int count3 = 0;//反向空子数

        // 向一个方向查找
        int dxpo = direction[z][0];
        int dypo = direction[z][1];
        while (x + dxpo >= 0 && x + dxpo < SIZE && y + dypo >= 0 && y + dypo < SIZE && (Board[x + dxpo][y + dypo] == BLACK||Board[x + dxpo][y + dypo] == BLACKtem)) {
            count1++;
            dxpo += direction[z][0];
            dypo += direction[z][1];
        }

        // 向相反方向查找
        int dxne = -direction[z][0];
        int dyne = -direction[z][1];
        while (x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && (Board[x + dxne][y + dyne] == BLACK||Board[x + dxne][y + dyne] == BLACKtem)) {
            count1++;
            dxne -= direction[z][0];
            dyne -= direction[z][1];
        }

        // 判断连子数
        if (count1==4) {
        /*判断空子数*/  while (x + dxpo >= 0 && x + dxpo < SIZE && y + dypo >= 0 && y + dypo < SIZE && Board[x + dxpo][y + dypo] <=9 && Board[x + dxpo][y + dypo] >= 1) {
             count2++;
             dxpo += direction[z][0];
             dypo += direction[z][1];
           }
           while (x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && Board[x + dxne][y + dyne] <=9 && Board[x + dxne][y + dyne] >= 1) {
             count3++;
             dxne -= direction[z][0];
             dyne -= direction[z][1];
           }
           if(count2 >= 2 && count3 >= 2){
             yorn++;
           }//00111100型活四
           else{
            if(count2 ==1 && count3 >= 2){
                if(x + dxpo >= 0 && x + dxpo < SIZE && y + dypo >= 0 && y + dypo < SIZE && (Board[x + dxpo][y + dypo] == BLACK||Board[x + dxpo][y + dypo] == BLACKtem)){
                    ;
                }
                else {
                    yorn++;
                }
            }
            else if(count3 ==1 && count2 >= 2){
                if(x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && (Board[x + dxne][y + dyne] == BLACK||Board[x + dxne][y + dyne] == BLACKtem)){
                    ;
                }
                else {
                    yorn++;
                }
            }
            else if(count2 ==1 &&count3 == 1){
                if ((x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && Board[x + dxne][y + dyne] == WHITE) && (x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && Board[x + dxne][y + dyne] == WHITE))
                {
                    yorn++;
                }
                else {
                    ;
                }
                
            }
            else{
                yorn++;
            }//避免10111100;00111101棋形
           }
        }
    return yorn;    
  }
}

/*读取冲四*/int getfour_bad(int x,int y,int z){  
 /*四个方向遍历*/
 if(z == 4){
  int num=0;  
  for (int i = 0; i < 4; i++) {
    int dxpo = direction[i][0];
    int dypo = direction[i][1];
    while (x + dxpo >= 0 && x + dxpo < SIZE && y + dypo >= 0 && y + dypo < SIZE && (Board[x + dxpo][y + dypo] == BLACK||Board[x + dxpo][y + dypo] == BLACKtem)) {
            dxpo += direction[i][0];
            dypo += direction[i][1];
        }
    if(Board[x + dxpo][y + dypo] == WHITE || x + dxpo < 0 || x + dxpo == SIZE || y + dypo < 0 || y + dypo == SIZE){
        int dxne = -direction[i][0];
        int dyne = -direction[i][1];
        while (x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && (Board[x + dxne][y + dyne] == BLACK||Board[x + dxne][y + dyne] == BLACKtem)) {
            dxne -= direction[i][0];
            dyne -= direction[i][1];
        }
        if(x + dxne < 0 || x + dxne == SIZE || y + dyne < 0 || y + dyne == SIZE || Board[x + dxne][y + dyne] == WHITE){;}//读到白子或边界就不可能
        else {
        int store1 = Board[x + dxne][y + dyne];
        Board[x + dxne][y + dyne] = BLACK;
        if(iswin(x + dxne,y + dyne,i) == 1){
             num++;
        }
        Board[x + dxne][y + dyne] = store1;//还原空子
        }
    }//碰到白子或边界就看反向
    else{
       int store1 = Board[x + dxpo][y + dypo];
       Board[x + dxpo][y + dypo] = BLACK;
       /*下了一步就五连，要让反向不五连才是冲四*/if(iswin(x + dxpo,y + dypo,i) == 1){
        int dxne = -direction[i][0];
        int dyne = -direction[i][1];
        while (x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && (Board[x + dxne][y + dyne] == BLACK||Board[x + dxne][y + dyne] == BLACKtem)) {
            dxne -= direction[i][0];
            dyne -= direction[i][1];
        }
        Board[x + dxpo][y + dypo] = store1;//还原空子
        if(x + dxne < 0 || x + dxne == SIZE || y + dyne < 0 || y + dyne == SIZE || Board[x + dxne][y + dyne] == WHITE){
            num++;
        }//读到白子或边界就不是五连
        else{
        int store2 = Board[x + dxne][y + dyne];
        Board[x + dxne][y + dyne] = BLACK;
        if(iswin(x + dxne,y + dyne,i) == 1){
             ;
        }
        else{
            num++;
        }
        Board[x + dxne][y + dyne] = store2;//假设落子还原
        }
       }
       /*下了一步没五连，要让反向五连才是冲四*/else if(iswin(x + dxpo,y + dypo,i) != 1){
        int dxne = -direction[i][0];
        int dyne = -direction[i][1];
        while (x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && (Board[x + dxne][y + dyne] == BLACK||Board[x + dxne][y + dyne] == BLACKtem)) {
            dxne -= direction[i][0];
            dyne -= direction[i][1];
        }
        Board[x + dxpo][y + dypo] = store1;//还原空子
        if(x + dxne < 0 || x + dxne == SIZE || y + dyne < 0 || y + dyne == SIZE || Board[x + dxne][y + dyne] == WHITE){;}//读到白子或边界就不可能
        else {
        int store2 = Board[x + dxne][y + dyne];
        Board[x + dxne][y + dyne] = BLACK;
        if(iswin(x + dxne,y + dyne,i) == 1){
             num++;
        }
        else{
            ;
        }
        Board[x + dxne][y + dyne] = store2;//假设落子还原
        }
       }
    }//碰到空子，就假设这里下一个黑子
  }
  return num;
}
 /*单独某个方向*/else{
    int yorn;
    int dxpo = direction[z][0];
    int dypo = direction[z][1];
    while (x + dxpo >= 0 && x + dxpo < SIZE && y + dypo >= 0 && y + dypo < SIZE && (Board[x + dxpo][y + dypo] == BLACK||Board[x + dxpo][y + dypo] == BLACKtem)) {
            dxpo += direction[z][0];
            dypo += direction[z][1];
        }
    if(x + dxpo < 0 || x + dxpo == SIZE || y + dypo < 0 || y + dypo == SIZE || Board[x + dxpo][y + dypo] == WHITE){
        int dxne = -direction[z][0];
        int dyne = -direction[z][1];
        while (x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && (Board[x + dxne][y + dyne] == BLACK||Board[x + dxne][y + dyne] == BLACKtem)) {
            dxne -= direction[z][0];
            dyne -= direction[z][1];
        }
        int store1 = Board[x + dxne][y + dyne];
        Board[x + dxne][y + dyne] = BLACK;
        if(iswin(x + dxne,y + dyne,z) == 1){
             yorn++;
        }
        Board[x + dxne][y + dyne] = store1;//还原空子
    }//碰到白子就看反向
    else{
       int store1 = Board[x + dxpo][y + dypo];
       Board[x + dxpo][y + dypo] = BLACK;
       /*下了一步就五连，要让反向不五连才是冲四*/if(iswin(x + dxpo,y + dypo,z) == 1){
        int dxne = -direction[z][0];
        int dyne = -direction[z][1];
        while (x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && (Board[x + dxne][y + dyne] == BLACK||Board[x + dxne][y + dyne] == BLACKtem)) {
            dxne -= direction[z][0];
            dyne -= direction[z][1];
        }
        Board[x + dxpo][y + dypo] = store1;//还原空子
        if(x + dxne < 0 || x + dxne == SIZE || y + dyne < 0 || y + dyne == SIZE || Board[x + dxne][y + dyne] == WHITE){
            yorn++;
        }//读到白子或边界就不是五连
        else{
        int store2 = Board[x + dxne][y + dyne];
        Board[x + dxne][y + dyne] = BLACK;
        if(iswin(x + dxne,y + dyne,z) == 1){
             ;
        }
        else{
            yorn++;
        }
        Board[x + dxne][y + dyne] = store2;//假设落子还原
         }
        }
       /*下了一步没五连，要让反向五连才是冲四*/else if(iswin(x + dxpo,y + dypo,z) != 1){
        int dxne = -direction[z][0];
        int dyne = -direction[z][1];
        while (x + dxne >= 0 && x + dxne < SIZE && y + dyne >= 0 && y + dyne < SIZE && (Board[x + dxne][y + dyne] == BLACK||Board[x + dxne][y + dyne] == BLACKtem)) {
            dxne -= direction[z][0];
            dyne -= direction[z][1];
        }
        Board[x + dxpo][y + dypo] = store1;//还原空子
        if(x + dxne < 0 || x + dxne == SIZE || y + dyne < 0 || y + dyne == SIZE || Board[x + dxne][y + dyne] == WHITE){
            yorn++;
        }//读到白子或边界就不是五连
        else{
        int store2 = Board[x + dxne][y + dyne];
        Board[x + dxne][y + dyne] = BLACK;
        if(iswin(x + dxne,y + dyne,z) == 1){
             yorn++;
        }
        else{
            ;
        }
        Board[x + dxne][y + dyne] = store2;//假设落子还原
         }
       }
       return yorn;
    }//碰到空子，就假设这里下一个黑子
 }
}
    
/*读取长连*/int getlong(int x,int y){
  int num=0;
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

        // 判断连子数
        if (count > 5) {
            num++;
        }
    }
    return num;
}
