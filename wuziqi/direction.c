#include"play.h"
int direction[4][2];
void dir(){
direction[0][0]=1;
direction[0][1]=0;
direction[1][0]=0;
direction[1][1]=1;
direction[2][0]=1;
direction[2][1]=1;
direction[3][0]=-1;
direction[3][1]=1;
}