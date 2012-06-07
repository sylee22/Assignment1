#include <iostream>
using namespace std;

#define OFF 0
#define ON 1
#define DEBUG OFF

int main(void){

#if DEBUG==ON
   cout << "this is a debug statement" << endl;
#endif

  cout << "hello world" << endl;
  cout << "hello world" << endl;
  cout << "hello world" << endl;
  cout << "hello world" << endl;
#if DEBUG==ON
   cout << "this is a debug statement" << endl;
#endif
  cout << "hello world" << endl;
  cout << "hello world" << endl;
  cout << "hello world" << endl;
#if DEBUG==ON
   cout << "this is a debug statement" << endl;
#endif
  cout << "hello world" << endl;
  cout << "hello world" << endl;
  cout << "hello world" << endl;
#if DEBUG==ON
   cout << "this is a debug statement" << endl;
#endif
  cout << "hello world" << endl;
}
