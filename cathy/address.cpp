#include <iostream>
using namespace std;

int main(void){
  char st[6]="abcd";
  char* p=st;
 
  cout << p << endl;
  cout << *p << endl;

  cout << p+2 << endl;

  cout << st+1 << endl;

  for(char* ptr=st;*ptr!='\0';ptr++){
    cout << ptr << endl;
  }
}
