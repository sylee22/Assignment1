/*
/*Author: Michael Berger
/* Working Console with up down and enter keys,
/To compile on OSX or LINUX:
/gcc MBCONSOLE.c console.c -lncurses
*/
#include "console.h"
void printInt(int);
void moveLeft(int, int);
void moveRight(int, int);
void enter(int, int);
void del(void);
void bs(int, int);
/*int consoleEdit(char, int, int, int, int, int, int, int, int); */
/*--------------------------------------------------------------*/

void printInt(int x){
    #if PLATFORM == UNIX || PLATFORM == OSX
        printw("%d",x);  
    #elif PLATFORM == WINDOWS
        cprintf("%d", x);  
    #endif      
}

/*
int consoleEdit(char *se, int slen, int row, int col, int flen, int *start, int *offset, int *insert, int ctype){
    int start_bak = start;
    int offset_bak = offset
    printint(start_bak);
    
}*/

void moveLeft(int strRow, int strCol){    
    if(strCol > 0)
        consoleMove(strRow, strCol - 1);
}
void moveRight(int strRow, int strCol){    
    if(strCol < consoleGetCols())
        consoleMove(strRow, strCol + 1);
}
void del(void){
	int i;
    #if PLATFORM == UNIX || PLATFORM == OSX
        delch();
    #elif PLATFORM == WINDOWS
		/*for(i=wherex();i<consoleGetCols;i++){
			
		}*/
	
	
    #endif
}
void bs(int strRow, int strCol){
    consoleMove(strRow, strCol - 1);
    del();
}
void enter(int strRow, int strCol){
    consoleMove(strRow + 1, 0);
}
/*----------------------------------------------------------------*/
int main(void){
    int posRow=1;
    int posCol=1;
    int key;
    consoleOn();
    consoleClear();
    consolePutS("Press Q to exit\n");
    while (key != 'Q') {
        key = consoleGetKey();
        switch(key){
            case ENTER:
                enter(posRow,posCol);
                posRow++;
                posCol=0;
                /*break;*/
            case DEL:
                del();
                break;
            case BS:
                bs(posRow, posCol);
                posCol--;
                break;
            case LEFT:
                moveLeft(posRow,posCol);
                posCol > 0 ? posCol-- : posCol == 0;
                break;
            case RIGHT:
                moveRight(posRow,posCol);
                posCol++;
                break;    
            default:
              consolePutC(key);
              posCol++;
        }    
    }
    
    consoleOff();
    return 0;
}
/* void consoleOn(void);       /* initialize screen 
   void consoleOff(void);        /* restore/shutdown screen use 
   int  consoleGetRows(void);        /* returns # of rows in screen 
   int  consoleGetCols(void);        /* returns # of columns in screen 
   void consoleClear(void);       /* clears screen 
   void consoleFlush(void);      /* refreshes screen to show changes 
   int  consoleGetKey(void);      /* picks up and returns a single key press 
   void consoleMove(int, int);  /* moves cursor to specific screen position 
   void consolePutC(int);         /* outputs a single character 
   void consolePutS(char *);    /* outputs a string 
*/
