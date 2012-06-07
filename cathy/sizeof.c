#include <stdio.h>
#include <stdlib.h>
void f1(int arr[]);

int main(void){

  printf("int %d\n",sizeof(int));
  printf("double %d\n",sizeof(double));
  printf("float %d\n",sizeof(float));
  printf("char %d\n",sizeof(char));
  printf("short %d\n",sizeof(short));
  printf("long %d\n",sizeof(long));
  printf("unsigned int %d\n",sizeof(unsigned int));

  int* ptr=(int*)malloc(10*sizeof(int));  //10 element array of ints
  char* ptr2 = (char*) malloc(10*sizeof(char)); //10 element array of char

  printf("int* %d\n",sizeof(ptr));
  printf("char* %d\n",sizeof(ptr2));
  

  int array[10];

  printf("int[10] %d\n",sizeof(array));  
  f1(array);
}

void f1(int arr[]){
  printf("f1(int arr[]) %d\n",sizeof(arr));  
}
