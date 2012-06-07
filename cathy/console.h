/*hello*/
/* file:       console.h                                             */
/* purpose:    header file for direct terminal I/O functions         */
/*             supporting both Windows and Unix Platforms            */
/* written by: Danny Abesdris, Catherine Leung                       */
/* date:       May 2012                                              */

#ifndef _CONSOLE_H_   /* this conditional statement is used to guard */
                      /* against the possibility of including this   */
                      /* header file more than once                  */
   #define _CONSOLE_H_

   #define WINDOWS 1
   #define UNIX 2
   #define OSX 3

   /* the line below must be changed to reflect the platform */
   /* that these routines will be compiled on */
   #define PLATFORM OSX

   #if PLATFORM == UNIX || PLATFORM == OSX
      #include <ncurses.h>
   #else
      #include <conio.h>
      #include <windows.h>
   #endif


   void consoleOn(void);       /* initialize screen */
   void consoleOff(void);        /* restore/shutdown screen use */
   int  consoleGetRows(void);        /* returns # of rows in screen */
   int  consoleGetCols(void);        /* returns # of columns in screen */
   void consoleClear(void);       /* clears screen */
   void consoleFlush(void);      /* refreshes screen to show changes */
   int  consoleGetKey(void);      /* picks up and returns a single key press */
   void consoleMove(int, int);  /* moves cursor to specific screen position */
   void consolePutC(int);         /* outputs a single character */
   void consolePutS(char *);    /* outputs a string */


   /* some platform-dependent keys (obtained by experimentation) */
   #if PLATFORM == UNIX
      #define UP    1859
      #define DOWN  1858
      #define LEFT  1860
      #define RIGHT 1861
      #define BS 8
   #elif PLATFORM == OSX
   #elif PLATFORM == WINDOWS
   #endif
#endif /* end of file _console_h_ */
