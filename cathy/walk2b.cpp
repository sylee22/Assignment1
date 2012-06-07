#include <cstring>
#include <iostream>
using namespace std;

#define ABC 0
#define DEF 1
#define CHOICE ABC

int f1(int x){
#if CHOICE==ABC
  x=x+1;
#else
  x=x+2;
#endif
  return x;
}
int f2(char x,char y){
  char retval;
#if CHOICE==ABC
  x>y ? retval=x : retval=y;
#else
  x>y?retval=y:retval=x;
#endif
  return retval;
}

int main(void){
  int a=5,b=9;
  int i;
  char str[20];
  char str2[20];
  char str3[20]; 
#if CHOICE==ABC
  strcpy(str,"Fulmh shd buse");
#else
  strcpy(str,"Piilv eajsqeo");
#endif
  for (i=0;i<strlen(str);i+=2){
    str[i]=str[i]+f1(CHOICE);
  }
  cout << str << endl;
#undef CHOICE
#define CHOICE DEF
  strcpy(str2,"Mopbet");
  strcpy(str3,"Hubpes");
  for (i=0;i<strlen(str2);i++){
    str[i]=f2(str2[i],str3[i]);
  }
  str[i]='\0';
  cout << str << endl;
}

