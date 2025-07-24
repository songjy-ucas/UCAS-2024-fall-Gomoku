#include"play.h"

int forbid(int x,int y){
    if(getlong(x,y)>=1 || getthree_good(x,y,4)>=2 || (getfour_good(x,y,4)+getfour_bad(x,y,4))>=1){
        printf("Here is forbidden!");
        return 1;
    }
    else {
        return 0;
    }
}