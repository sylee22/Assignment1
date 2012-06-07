/* file:       console.c                                          */
/* purpose:    source file for console I/O functions              */
/*             supporting both Windows (using Visual Studio 2008) */
/*             and UNIX using GCC 4 platforms                     */
/* written by: Danny Abesdris, Catherine Leung                    */

#include <string.h>
#include <stdlib.h>
#include "console.h"

void consoleOn(void) {
  #if PLATFORM == WINDOWS
     /* no startup requirements for windows */
  #elif PLATFORM == UNIX || PLATFORM == OSX
     initscr( );
     noecho( );
     cbreak( );
     keypad(stdscr, 1);
  #endif
}
void consoleOff(void) {
  #if PLATFORM == WINDOWS
     consoleClear( );
  #elif PLATFORM == UNIX || PLATFORM == OSX
     refresh( );
     endwin( );
  #endif
}
void consoleMove(int row, int col) {
  #if PLATFORM == WINDOWS  /* windows specific routines for cursor control */
     HANDLE hStdout;
     struct _CONSOLE_SCREEN_BUFFER_INFO x;
     hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
     GetConsoleScreenBufferInfo(hStdout, &x);
     x.dwCursorPosition.X = col;
     x.dwCursorPosition.Y = row;
     SetConsoleCursorPosition(hStdout, x.dwCursorPosition);
  #elif PLATFORM == UNIX || PLATFORM == OSX
     move(row, col);
  #endif
}
int consoleGetKey(void) {
  int key;
  #if PLATFORM == WINDOWS
    key = getch( );
    /* On windows, getch( ) returns 0 for function keys, but
       0xE0 for all other non-ascii (extended) keys */
    key = (key == 0 || key == 0xE0) ? getch( ) + 1000 : key;
  #elif PLATFORM == UNIX || PLATFORM == OSX
    key = getch( );
  #endif
  return key;
}
int consoleGetRows(void) {
  int rows;
  #if PLATFORM == WINDOWS
     HANDLE hStdout;
     struct _CONSOLE_SCREEN_BUFFER_INFO x;
     hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
     GetConsoleScreenBufferInfo(hStdout, &x);
     rows = x.dwSize.Y;
  #elif PLATFORM == UNIX || PLATFORM == OSX
     rows = LINES;
  #endif
  return rows;
}
int consoleGetCols(void) {
  int cols;
  #if PLATFORM == WINDOWS
     HANDLE hStdout;
     struct _CONSOLE_SCREEN_BUFFER_INFO x;
     hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
     GetConsoleScreenBufferInfo(hStdout, &x);
     cols = x.dwSize.X;
  #elif PLATFORM == UNIX || PLATFORM == OSX
    cols = COLS;
  #endif
  return cols;
}
void consoleClear(void) {
  #if PLATFORM == WINDOWS
     DWORD n;                         /* Number of characters written */
     DWORD size;                      /* number of visible characters */
     COORD coord = { 0 };             /* Top left screen position     */
     struct _CONSOLE_SCREEN_BUFFER_INFO csbi;

     /* Get a handle to the console */
     HANDLE h = GetStdHandle (STD_OUTPUT_HANDLE);
     GetConsoleScreenBufferInfo (h, &csbi);

     /* Find the number of characters to overwrite */
     size = csbi.dwSize.X * csbi.dwSize.Y;

     /* Overwrite the screen buffer with whitespace */
     FillConsoleOutputCharacter(h, TEXT(' '), size, coord, &n);
     GetConsoleScreenBufferInfo(h, &csbi);
     FillConsoleOutputAttribute(h, csbi.wAttributes, size, coord, &n);

     /* Reset the cursor to the top left position */
     SetConsoleCursorPosition ( h, coord );
  #elif PLATFORM == UNIX || PLATFORM == OSX
    erase( );
  #endif
}
void consolePutC(int c) {
  #if PLATFORM == WINDOWS
     putch(c);
  #elif PLATFORM == UNIX || PLATFORM == OSX
     addch(c);
  #endif
}
void consolePutS(char *s) {
  #if PLATFORM == WINDOWS
     cputs(s);
  #elif PLATFORM == UNIX || PLATFORM == OSX
     addstr(s);
  #endif
}
void consoleFlush(void) {
  #if PLATFORM == WINDOWS
     /* not required to update the screen on windows */
  #elif PLATFORM == UNIX || PLATFORM == OSX
     refresh( );
  #endif
}
