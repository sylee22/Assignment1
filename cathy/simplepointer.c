#include <stdio.h>

int main(void){
  int a=5;
  int* p=&a;
  int** q=&p;

  printf("a=%d\n",a);
  printf("&a=%d\n",&a);
  printf("p=&a=%d\n",p);
  printf("*p=a=%d\n",*p);
  printf("&p=%d\n",&p);
  printf("q=&p=%d\n",q);
  printf("*q=p=%d\n",*q);
  printf("**q=a=%d\n",**q);

}
