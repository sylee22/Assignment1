/* file:       console.c                                          */
/* purpose:    source file for console I/O functions              */
/*             supporting both Windows (using Visual Studio 2008) */
/*             and UNIX using GCC 4 platforms                     */
/* written by: Danny Abesdris, Catherine Leung                    */
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "console.h"


void consoleDraw(char *sd, int row, int col, int len)
{
/* This function is used to display a text field containing
the string 'sd' on the screen.*/
  int i;

  if(sd && row>=0 && col>=0){
    consoleMove(row,col); //set position

    if(len<=0){
consolePutS((char*)sd);

    }else{

for(i=0; i<len && sd[i]!='\0'; i++){
consolePutC(sd[i]);
}
for(;i<len;i++){
consolePutC(' ');
}

    }
  }

}

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
  
/*<CXD> version 2.1 updated to work in both Windows and UNIX*/

int consoleBox(int row, int col, int l, int h, char edge, char top_btm, char ls_rs)
{
	int i=0, j=0, row_max, col_max;

	row_max = consoleGetRows();                                     /*return if the window is sufficient for drawing the box*/
	col_max = consoleGetCols();
	if(row+h > row_max || col+l > col_max)                          /*if no sufficient screen space then return 1*/
		return 0;
	else                                                            /*with sufficient screen space*/
	{

		consoleMove(row,col);                                   /*top*/
		consolePutC(edge);
		for(i=col+1;i<col+l-1;i++)
			consolePutC(top_btm);
		consolePutC(edge);

		for(i=row+1;i<row+h-1;i++)                              /*middle*/
		{
			consoleMove(i,col);
			consolePutC(ls_rs);
			consoleMove(i,col+l-1);
			consolePutC(ls_rs);
		}

		consoleMove(row+h-1,col);                               /*bottom*/
		consolePutC(edge);
		for(i=col+1;i<col+l-1;i++)
			consolePutC(top_btm);
		consolePutC(edge);

		return 1;                                               /*return 1 in case of drawing the box successfully*/
	}
}

  /*Kalid, Michael and Min Wok's function*/
int consoleEdit (char *se, int slen, int row, int col, int flen, int *start, int *offset, int *insert, int ctype){
  

  int done = 0;
  int key;
 // char * temp; renamed to seTemp below
  char* seTemp;
  char * seTemp2;
  int startTemp = *start; /* initialized intial value of start */
  int startTemp2;
  int offsetTemp = *offset; /* initialized intial value of offset */
  int offsetTemp2;
  int i; /*<MB>index for loops*/
  int l; /*<MB> String Length*/
  int seCurPos; /*<MB>The index number of the char array pointed to by se
			which contains what the cursor is focused upon */
  int validated;
  validated = validateType(se, slen, ctype);
  if(validated){
    seTemp = (char*) malloc (sizeof(char) * (strlen(se)+1));
    strcpy(seTemp, se); /* copy value of se into seTemp */
	while(!done){
		  /*<Min Wok> display interface*/
		  /*<MB>Must merge with with what i have in MB_Console and Kalid's consolef.c */ 
    seCurPos = *start + *offset;
    l = strlen(se);
    consoleDraw(se + *offset, row, col, flen);
      consoleMove(row, col + *start);
/*    consoleMove(row, col + *start-1);   /*<MB> Min Wok, Are you sure about the minus 1? Cursor     */
/*      (replaced with above line)               location is numbered starting from 0                */
    key = consoleGetKey();
    switch(key){ 
      case HOME:
	   *start = 0;
	   if(*offset)
	   *offset = 0;
	   break;
      case END:
	if((*offset) + flen <= strlen(se)){
	  /*<MB> Is this intentionally blank? */
	  }
	  else{
	    consoleMove(row, col+(strlen(se)-(*offset)));
	  }
	  break;
	
      case LEFT: /*By Michael*/
	if(*start > 0)
	  (*start)--;
	  else if(*offset > 0)
	  (*offset)--;
	break;
      case RIGHT: /*By Michael*/
	if (seCurPos < l){
	  if(*start < flen)
	    (*start)++;
	  else
	    (*offset)++;
	}
	break;
      case INS:
		  if(*insert) { *insert = 0; }
		  else {*insert = 1; }
	break;
      case BS:
		  printf("\n\nBackspace! with securpos as : %d\n", seCurPos);
		  if (seCurPos > 0){
		   for(i = seCurPos-1; i<l; i++){
			se[i] = se[i+1];
	     }
		   if(*start > 0)
				(*start)--;
			else if(*offset > 0)
				(*offset)--;
		  }
	break;
      case DEL: /*<by michael>*/
		  printf("\n\nDELETE! with securpos as : %d\n", seCurPos);
	if (seCurPos < l){
	  for(i = seCurPos; i<l; i++){
	    se[i] = se[i+1];
	  }
	}
		break;
	case ESC:           
		*start = startTemp; 
		*offset = offsetTemp; /* resetting our pointers back to our temp variables */
		strcpy(se, seTemp);                
		
		done++;
		break;
    default: 
		if(key == ENTER || key == TAB || key == UP || key == DOWN || key == PGUP || (key >= F1 && key <= F10 )){
	  done++;
	}else if(key >= 32 && key <= 126) {
	  seTemp2 = (char*) malloc (sizeof(char) * (l + 1));
	  offsetTemp2 = *offset;
	  startTemp2 = *start;
	  if(*insert){                   /*<MB>if insert mode on */
	      for(i=l; i >= seCurPos; i--){    /*<MB> copies each character in se, from the null byte to the cursor postion up a block in the memory*/
		se[i+1] = se[i];
	      }
	      se[seCurPos] = key;       /*<mb>sets the char at the cursor position of se to be equal to the inserted character*/
	      if(*start < flen)         
		(*start)++;
	      else
		(*offset)++;
	  }else{                        /*<MB>if insert mode off */
	    se[seCurPos] = key;
	      if(*start < flen)         
		(*start)++;
	      else
		(*offset)++;        
	  }
	  validated = validateType(se, slen, ctype);   /*<MB> IF NOT VALIDATED, MUST UNDO CHANGES */
	  if(!validated){
	    strcpy(se, seTemp2);
	    *offset = offsetTemp2;
	    *start = startTemp2;
	  }
	  free (seTemp2);
	  seTemp2 = NULL;         
	} /*<mb>end of default cases main if statement*/
      }   /*<mb>end of switch*/
    }     /*<mb>end of whileloop*/
	  free (seTemp);
	  seTemp = NULL;  
    return key;
  } /*<MB>End of if(validated)*/
    
	/* Nearing end of function */
	
	/* release allocated memory then assign them NULL values! */
    //free(startTemp);
      //  free(offseetTemp);
	
	//startTemp = NULL;
	//offsetTemp = NULL;
    
    
/*      if(key <=176 && key >= 32 && strlen(se)<slen){              /* Min Woks work*/ /*
	  if(*insert){             /*<MB> ABOVE CONDITION IS NO GOOD, if in overtype mode,
				    slen doesnt matter until you are at the last char of the string*//*
	    }else
	  {
	  }
	}else{
	}
	break;
	    }
*/          


} /* END of consoleEdit function */ 


int validateType(char *str,int maxstrlen, int type){
  int i, retval;
  int err = 0;
  int len = strlen(str);
  if (len > maxstrlen)
    err++;
  else{
    switch(type){
      case 1:        /*<MB> I Am Assuming Printable characters only */
	for (i=0; i<len; i++){
	  if (str[i] < 32 ||  str[i] > 126)
	    err++; 
	}
	break;
      case 2:       /*<MB>Binary chars only ---But what about white-spaces? */
	for (i=0; i<len; i++){
	  if (str[i] != '0' &&  str[i] != '1')
	    err++; 
	}
	break;
      
      case 4:      /*<MB>Numeric chars only*/
	for (i=0; i<len; i++){
	  if (str[i] < '0' ||  str[i] > '9')
	    err++; 
	}      
	break;
      
      case 8:     /*octal chars only */
	for (i=0; i<len; i++){
	  if (str[i] < '0' ||  str[i] > '7')
	    err++; 
	}      
	break;
      case 16:    /*Hexadecimal chars only*/
	for (i=0; i<len; i++){
	  if (!isxdigit(str[i])) 
	    err++; 
	}      
	break;
      default:
	err++;
      
    }
  } 
/*<MB> Does the IPC 144 Rule of only one return statement still apply? */  
  if(err)
    retval = 0;
  else
    retval = 1;
  return retval;

}
