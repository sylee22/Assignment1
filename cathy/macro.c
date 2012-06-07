#include <stdio.h>
#define ABS(a) a>0?a:-a

int main(void){
  int y=-10;
  int x=15;

  int z=ABS(x);
  printf("abs(%d)=%d\n",x,z);
  z=ABS(y);
  printf("abs(%d)=%d\n",y,z);

  z=ABS(2-3);
  printf("abs(2-3)=%d\n",z);
}
