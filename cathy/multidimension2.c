#include <iostream>
using namespace std;

int main(void){
  char arr[2][3][4]={{"cxt","dog","box"},
                     {"hat","toe","you"}};

  cout << arr[0][1] << endl;
  cout << ***arr << endl;
  cout << ***(arr+1) << endl;
  cout << (char)(***arr+1) << endl;
  cout << *(*(arr+1)+1) << endl;
  cout << *(*(arr+0)+1)+1 << endl;
  cout << arr[0][1] + 1 << endl;
  /*for a given multi dimensional array
    to access arr[x][y][z] with pointer arimetic
    use:
     *(*(*(arr+x)+y)+z)
  */
}
