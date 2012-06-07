#include <iostream>
using namespace std;

int main(void){

  int a=5;
  char b='d';
  double c=6.2;

  void* p=&b;
  
  cout << *((char*)p) << endl;
  cout << *((int*)p) << endl;
 
}
