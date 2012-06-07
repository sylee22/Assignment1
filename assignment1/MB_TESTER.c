/*
Author: Michael Berger
File to test key codes,
*/
int main(void){
    int key;
    consoleOn();
    consolePutS("TESTING...1...2\n");
    consolePutS("TESTING...3\nPress q to exit");
    int i = 4;
    while (key != 'q') {
        consoleMove(i++,0);
        key = consoleGetKey();
  #if PLATFORM == UNIX || PLATFORM == OSX
        printw("{%d} ", key);  
  #elif PLATFORM == WINDOWS
        cprintf("{%d} ", key);  /*UNTESTED*/
  #endif      
        consolePutC(key);
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
