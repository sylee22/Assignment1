#include <iostream>
using namespace std;


int main(void){
  char st[6]="hello";
  char* p=st;
  int x=5;
  cout << st << endl;
  cout << p << endl;
  //printing first 2 characters
  cout << st[0] << st[1] << endl;
  cout << p[0] << p[1] << endl;

  cout << *st << *(st+1) << endl;
  cout << *p << endl;
  cout << (char)104 << endl;

  cout << st+3 << endl;
  cout << p+3 << endl;
}
