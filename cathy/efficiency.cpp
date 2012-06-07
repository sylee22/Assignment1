#include <iostream>
#include <cstring>
using namespace std;
#include "timer.h"

int count1(char* s){
  int n=0;
  for(int i=0;i<strlen(s);i++){
    n+=s[i];
  }
  return n;
}
int count2(char* s){
  int n=0;
  for(int i=0;s[i]!='\0';i++){
    n+=s[i];
  }
  return n;
}
int count3(char* s){
  int n=0;
  int len=strlen(s);
  for(int i=0;i<len;i++){
    n+=s[i];
  }
  return n;
}
int main(void){
  Timer t1, t2, t3;
  char* s=new char[200001];
  for(int i=0;i<200000;i++){
    s[i]='A';
  }
  s[200000]='\0';
  
  int n;
  t2.start();
  n=count2(s);
  t2.stop();
  cout << t2.currtime() << endl;
  t3.start();
  n=count3(s);
  t3.stop();
  cout << t3.currtime() << endl;
  t1.start();
  n=count1(s);
  t1.stop();
  cout << t1.currtime() << endl;

}
