/*a simple demonstration of console functions
  compile with:
  on matrix:
    in the console.h file switch the #define PLATFORM statement to UNIX
    gcc getkey.c console.c -lncurses 
  on windows:
    in the console.h file switch the #define PLATFORM statement to WINDOWS
    compile with VS

*/
#include "console.h"

int main(void){
  char number[20];  //string holding key value user entered
  int keyCode;      //keycode read from user
  char blank[20]="               ";  
  consoleOn();      //all console programs need this as first line
  consoleMove(10,20);   //move to row 10, column 20
  consolePutS("hit a key, use Q or q to quit");
  keyCode=consoleGetKey();
  while(keyCode!='Q' && keyCode!='q'){ 
    consoleMove(12,20);
    consolePutS(blank);
    sprintf(number, "%d",keyCode);
    consoleMove(12,20);
    consolePutS(number);
    keyCode=consoleGetKey();
  }

  consoleOff();
}
