#include <stdio.h>

int main(void){
  int md[2][3][2]={{{10,20},{30,40},{50,60}},
                   {{1,2},{3,4},{5,6}}
                  };
  printf("size of(md) %d\n",sizeof(md));
  int i,j,k;

  int* p=&(md[0][0][0]); 
  for(i=0;i<12;i++){
    printf("%d\n",*p);
    p++;
  }

 /* for(i=0;i<2;i++){
    for(j=0;j<3;j++){
      for(k=0;k<2;k++){
        printf("%d\n",md[i][j][k]);
      }
    }
  }*/

}
