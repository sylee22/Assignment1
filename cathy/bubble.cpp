#include <iostream>
using namespace std;
#include <cstdlib>
struct Info{
  int number1_;
  int number2_;
  Info(){
    number1_=rand()%100;
    number2_=rand()%100;
  }
};
ostream& operator<< (ostream& os, Info& i){
  os << i.number1_ << " " << i.number2_;
  return os;
}

int cmpNumber1(Info a, Info b){
  int rc=0;
  if(a.number1_ > b.number1_)
    rc=1;
  return rc;
}

int cmpNumber2(Info a, Info b){
  int rc=0;
  if(a.number2_ > b.number2_)
    rc=1;
  return rc;
}
void print(Info array[],int sz){
  for(int i=0;i<sz;i++){
    cout << array[i] << endl;
  }
}
int cmpSum(Info a, Info b){
  int rc=0;
  if(a.number1_+a.number2_>b.number1_+b.number2_){
    rc=1;
  }
  return rc;
}

void bubble(Info array[],int sz, int (*wrongOrder)(Info,Info)){
  int i, j;
  Info v;
  for(i=0;i<sz;i++){
    for(j=0;j<sz-1-i;j++){
      if(wrongOrder(array[j],array[j+1])){
        v=array[j];
        array[j]=array[j+1];
        array[j+1]=v;
      }
    }
  }
}

int main(void){
  Info array[6];
  int choice;
  cout << "original: " << endl; 
  print(array,6);
  cout << "choose to sort by number 1 (1) or number 2 (2) or other value to quit: ";
  cin >> choice;   
       
  while(choice == 1 || choice == 2 || choice==3){
    if(choice==1){
      cout << "sort by number1: " << endl;
      bubble(array,6,cmpNumber1);
    }
    else if(choice==2){
      cout << "sort by number2: " << endl;
      bubble(array,6,cmpNumber2);
    }
    else{
      cout << "sort by sum of number1 and number2: " << endl;
      bubble(array,6,cmpSum);
    }
    print(array,6);
    cout << "choose to sort by number 1 (1) or number 2 (2) or other value to quit: ";
    cin >> choice;   
  }    
}
