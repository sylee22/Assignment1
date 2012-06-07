/***************************************************************/
/*                                                             */
/* file:       a2main.c  version 1.0                           */
/* written by: Danny Abesdris. Catherine Leung                 */
/* date:       June 4, 2012                                    */
/*                                                             */
/* This is the official test main for OOP344 assignment #2     */
/* Summer 2012                                                 */
/* This file may not be modified!                              */
/*                                                             */
/* Compilation instructions (see below)                        */
/* On Windows (Visual Studio 2010 C/C++ Compiler):             */
/* cl a2main.c console.c    (creates: a2main.exe)              */
/*                                                             */
/* On Linux (Matrix) (GNU GCC Compiler):                       */
/* cc a2main.c console.c -lncurses -o a2main (creates: a2main) */
/*                                                             */
/* Note that this program cannot verify that your routines     */
/* are correct, you must run the program and observe whether   */
/* or not it is working correctly.                             */
/* ALSO IMPORTANT: In all your source files                    */
/* (including .h files)                                        */
/* YOU MUST INCLUDE THE FOLLOWING STATEMENT                    */
/* (as part of the header comments):                           */
/*                                                             */
/* "We declare that the attached assignment is wholly our own  */
/* work in accordance with Seneca Academic Policy.  No part    */
/* of this assignment has been copied manually or              */
/* electronically from any other source                        */
/* (including web sites), other than the startup framework     */
/* provided in class and this statement."                      */
/*                                                             */
/*            __________________________________               */
/*            (print student name and ID of all group members  */
/*                                                             */
/* Submissions which do not have this statement will have      */
/* to be resubmitted, even if they have no logic flaws.        */
/*                                                             */
/***************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "console.h"

#define SROWS 5
#define SCOLS 61

typedef struct {
   char *line;
   int key, start, offset, ctype, io, slen, flen;
   int x, y;
} info;

typedef unsigned long ul;

int test1(char [ ][SCOLS]);
int test2(char [ ][SCOLS]);
int test3(char [ ][SCOLS]);
int test4(char [ ][SCOLS]);
int test5(char [ ][SCOLS]);
int test6(char [ ][SCOLS]);

void endkey(int, char *);
char* my_alloc(ul);
void infoscreen(info *);

int main( ) {
   int i, rc, ok=1;
   int (*fp[SROWS+1])(char[ ][SCOLS]) = {
      test1, test2, test3, test4, test5, test6
   };
   char messages[SROWS+1][SROWS][SCOLS] = {
      {
         "",
         "There should be '*' characters surrounding",
         "the entire screen frame, except for the lower",
         "right corner of the screen",
         "Press any key to continue..."
      },
      {
         "Press each of the SPECIAL keys",
         "to test its value!",
         "Press 'Q' or 'q' to proceed",
         "to the next test...",
         ""
      },
      {
         "Try to type in 5 characters. Do not use the",
         "arrow keys or adjust the cursor in any way.",
         "Note: You may not actually insert more than 5",
         "       characters because of size restrictions!",
         "DO NOT end editing with the ESC key."
      },
      {
         "Type in some characters to edit the string.",
         "Press the left arrow key to test scrolling!",
         "When you are finished, end editing with",
         "the ESC key!",
         ""
      },
      {
         "Testing the edit function with a really",
         "long string. Perform some editing, then",
         "terminate WITHOUT hitting the ESC key!",
         "",
         ""
      },
      {
         "Testing the 'ctype' functionality.",
         "Hit any of the extended keys to test the",
         "next 'ctype' value.",
         "To terminate editing hit the F1 key.",
         ""
      }
   }, msg[SCOLS];

   consoleOn( ); /* begin console I/O processing on UNIX */

   if(consoleGetCols( )<80 || consoleGetRows( )<30) {
      consoleMove(1,1);
      sprintf(msg, "screen dimensions are: %d by %d",
              consoleGetCols( ), consoleGetRows( ));
      consolePutS(msg);
      consoleMove(2,1);
      consolePutS("screen dimensions must be at least");
      consoleMove(3,1);
      consolePutS("80 columns by 30 rows!");
      consoleMove(4,1);
      consolePutS("Please resize your screen, and try again.");
      consoleMove(5,1);
      consolePutS("Press any key to quit...");
      consoleGetKey( );
      consoleOff( );
      ok = 0;
   }

   if(ok) {
      for(i=0; i<SROWS+1; i++) {
         consoleClear( );
         fp[i](messages[i]);
      }
      consoleOff( );
   }
   return 0;
}

int test1(char msg[ ][SCOLS]) {
   char msg2[SCOLS];
   int i, j, key, x, y;

   for(i=0; i<consoleGetRows( ); i++) {
      if(i==0 || i==consoleGetRows( ) - 1) {
         for(j=0; j<consoleGetCols( ); j++) {
            if(i!=consoleGetRows( )-1 || j!=consoleGetCols( )-1) {
               consolePutC('*');
            }
         }
      }
      else {
         consolePutC('*');
         for(j=0; j<consoleGetCols( )-2; j++) {
            consolePutC(' ');
         }
         consolePutC('*');
      }
   }

   sprintf(msg2, "rows: %d, cols: %d", consoleGetRows( ), consoleGetCols( ));
   x = (consoleGetRows( )-SROWS)/2;
   y = (consoleGetCols( )-strlen(msg2))/2;
   consoleMove(x, y);
   consolePutS(msg2);

   for(i=0; i<SROWS; i++) {
      y = (consoleGetCols( )-strlen(msg[i]))/2;
      consoleMove(++x, y);
      consolePutS(msg[i]);
   }
   consoleMove(2, 2);
   consolePutS("TEST 1");
   consoleMove(0,0);

   key = consoleGetKey( );
   return key;
}

int test2(char msg[ ][SCOLS]) {
   int i, x, key;
   char msg2[SCOLS];

   consoleMove(2, 2);
   consolePutS("TEST 2");
   consoleMove(0,0);

   x = (consoleGetRows( )-SROWS)/2;
   for(i=0; i<SROWS; i++, x++) {
      consoleMove(x, 10);
      consolePutS(msg[i]);
   }

   key = consoleGetKey( );
   while(key != 'Q' && key != 'q') {
      endkey(key, msg2);
      consoleDraw(msg2, x, 10, 31);
      consoleMove(x, 10 + strlen(msg2));
      key = consoleGetKey( );
  }

  return key;
}

int test3(char msg[ ][SCOLS]) {
   info in;
   int key, i;
   char msg2[SCOLS], end[SCOLS];

   in.x = 2;
   in.y = 10;
   in.offset = 0;
   in.start = 7;
   in.line = my_alloc(SCOLS/2+2);
   strcpy(in.line, "abcdefghijklmnopqrstuvwxyz");
   in.ctype = 1;
   in.io = 1;
   in.flen = 20;
   in.slen = SCOLS/2+1;

   consoleMove(2, 2);
   consolePutS("TEST 3");

   for(i=0; i<SROWS; i++, in.x++) {
      consoleMove(in.x, in.y);
      consolePutS(msg[i]);
   }
   infoscreen(&in);

   key = consoleEdit(in.line, in.slen, in.x+2, in.y+1, in.flen,
                                 &in.start, &in.offset, &in.io, in.ctype);
   while(key == ESC) {
      sprintf(msg2, "string:  '%s'", in.line);
      consoleDraw(msg2, consoleGetRows( )-5, in.y, SCOLS);

      strcpy(msg2, "You ended with ESC.  DO NOT end with ESC!");
      consoleDraw(msg2, consoleGetRows( )-3, in.y, SCOLS);

      strcpy(msg2, "Press any key to run this test again...");
      consoleDraw(msg2, consoleGetRows( )-2, in.y, SCOLS);
      consoleMove(consoleGetRows( )-2, strlen(msg2)+in.y);

      consoleGetKey( );
      consoleClear( );
      strcpy(in.line ,"abcdefghijklmnopqrstuvwxyz");
      in.x = 2;
      in.offset = 0;
      in.start = 7;
      for(i=0; i<SROWS; i++, in.x++) {
         consoleMove(in.x, 10);
         consolePutS(msg[i]);
      }

      consoleMove(2, 2);
      consolePutS("TEST 3");

      infoscreen(&in);

      key = consoleEdit(in.line, in.slen, in.x+2, in.y+1, in.flen,
                                    &in.start, &in.offset, &in.io, in.ctype);
   }
   endkey(key, end);

   sprintf(msg2, "string: '%s'", in.line);
   consoleDraw(msg2, consoleGetRows( )-5, in.y, SCOLS);
   sprintf(msg2, "Test ended with the '%s' key: ", end);
   consoleDraw(msg2, consoleGetRows( )-3, in.y, SCOLS);
   strcpy(msg2, "Press any key to continue...");
   consoleDraw(msg2, consoleGetRows( )-2, in.y, SCOLS);
   consoleMove(consoleGetRows( )-2, strlen(msg2)+in.y);
   consoleGetKey( );
   free(in.line); /* removing allocated memory */
   return key;
}

int test4(char msg[ ][SCOLS]) {
   info in;
   int key, i;
   char msg2[SCOLS], end[SCOLS];

   in.x = 2;
   in.y = 10;
   in.offset = 4;
   in.start = 0;
   in.line = my_alloc(SCOLS/2+2);
   strcpy(in.line, "The Lord Of The Rings");
   in.ctype = 1;
   in.io = 1;
   in.flen = 30;
   in.slen = SCOLS/2+1;

   consoleMove(2, 2);
   consolePutS("TEST 4");

   for(i=0; i<SROWS; i++, in.x++) {
      consoleMove(in.x, in.y);
      consolePutS(msg[i]);
   }
   infoscreen(&in);

   key = consoleEdit(in.line, in.slen, in.x+2, in.y+1, in.flen,
                                 &in.start, &in.offset, &in.io, in.ctype);
   while(key != ESC) {
      sprintf(msg2, "string:  '%s'", in.line);
      consoleDraw(msg2, consoleGetRows( )-5, in.y, SCOLS);

      strcpy(msg2, "You did not end with ESC! Please end with ESC.");
      consoleDraw(msg2, consoleGetRows( )-3, in.y, SCOLS);

      strcpy(msg2, "Press any key to run this test again...");
      consoleDraw(msg2, consoleGetRows( )-2, in.y, SCOLS);
      consoleMove(consoleGetRows( )-2, strlen(msg2)+in.y);

      consoleGetKey( );
      consoleClear( );
      strcpy(in.line ,"The Lord Of The Rings");
      in.x = 2;
      in.offset = 4;
      in.start = 0;
      for(i=0; i<SROWS; i++, in.x++) {
         consoleMove(in.x, in.y);
         consolePutS(msg[i]);
      }
      consoleMove(2, 2);
      consolePutS("TEST 4");

      infoscreen(&in);

      key = consoleEdit(in.line, in.slen, in.x+2, in.y+1, in.flen,
                                    &in.start, &in.offset, &in.io, in.ctype);
   }
   endkey(key, end);

   sprintf(msg2, "string: '%s'", in.line);
   consoleDraw(msg2, consoleGetRows( )-5, in.y, SCOLS);
   sprintf(msg2, "Test ended with the '%s' key: ", end);
   consoleDraw(msg2, consoleGetRows( )-3, in.y, SCOLS);
   strcpy(msg2, "Press any key to continue...");
   consoleDraw(msg2, consoleGetRows( )-2, in.y, SCOLS);
   consoleMove(consoleGetRows( )-2, strlen(msg2)+in.y);
   consoleGetKey( );
   free(in.line); /* removing allocated memory */
   return key;
}

int test5(char msg[ ][SCOLS]) {
   info in;
   int key, i;
   char msg2[SCOLS], end[SCOLS];

   in.line = my_alloc(SCOLS * 50);
   in.x = 2;
   in.y = 10;
   in.offset = 0;
   in.start = 0;
   strcpy(in.line, "There are more things in heaven "
                   "and earth Horatio than are dreamt"
                   " of in your philosophy...");
   in.ctype = 1;
   in.io = 0;
   in.flen = 40;
   in.slen = SCOLS*50-1;

   for(i=0; i<50; i++) {
      strcat(in.line, "Hamlet Act 1, Scene V");
   }

   for(i=0; i<SROWS; i++, in.x++) {
      consoleMove(in.x, in.y);
      consolePutS(msg[i]);
   }

   consoleMove(2, 2);
   consolePutS("TEST 5");
   infoscreen(&in);

   key = consoleEdit(in.line, in.slen, in.x+2, in.y+1, in.flen,
                                 &in.start, &in.offset, &in.io, in.ctype);

   while(key == ESC) {
      sprintf(msg2, "string: '");
      strncat(msg2, in.line, 40);
      msg2[50]='\0';
      strcat(msg2, "'...");
      consoleDraw(msg2, consoleGetRows( )-5, in.y, SCOLS);

      strcpy(msg2, "You ended with ESC.  DO NOT end with ESC!");
      consoleDraw(msg2, consoleGetRows( )-3, in.y, SCOLS);

      strcpy(msg2, "Press any key to run this test again...");
      consoleDraw(msg2, consoleGetRows( )-2, in.y, SCOLS);
      consoleMove(consoleGetRows( )-2, strlen(msg2)+in.y);

      consoleGetKey( );
      consoleClear( );
      strcpy(in.line, "There are more things in heaven "
                      "and earth Horatio than are dreamt"
                      " of in your philosophy... ");

      for(i=0; i<50; i++) {
         strcat(in.line, "Hamlet Act 1, Scene V ");
      }
      in.x = 2;
      in.offset = 0;
      in.start = 0;
      for(i=0; i<SROWS; i++, in.x++) {
         consoleMove(in.x, in.y);
         consolePutS(msg[i]);
      }
      consoleMove(2, 2);
      consolePutS("TEST 5");
      infoscreen(&in);

      key = consoleEdit(in.line, in.slen, in.x+2, in.y+1, in.flen,
                                    &in.start, &in.offset, &in.io, in.ctype);
   }
   endkey(key, end);

   sprintf(msg2, "string: '");
   strncat(msg2, in.line, 40);
   msg2[50]='\0';
   strcat(msg2, "'...");

   consoleDraw(msg2, consoleGetRows( )-5, in.y, SCOLS);
   sprintf(msg2, "Test ended with the '%s' key: ", end);
   consoleDraw(msg2, consoleGetRows( )-3, in.y, SCOLS);
   strcpy(msg2, "Press any key to continue...");
   consoleDraw(msg2, consoleGetRows( )-2, in.y, SCOLS);
   consoleMove(consoleGetRows( )-2, strlen(msg2)+in.y);
   consoleGetKey( );
   free(in.line);
   return key;
}

int test6(char msg[ ][SCOLS]) {
   char llines[SROWS+1][SCOLS] = {
      "The 2008 U.S. Presidential Election...",
      "Obama 290 McCain 248",
      "The Lord of the Rings",
      "OOP344",
      "                    ",
      "This is a line of text..."
   }, msg2[SCOLS], end[SCOLS];
   int i, j, key=0;
   info in;

   in.line = my_alloc(SCOLS+1);
   in.ctype = 0;
   in.io = 0;
   in.y = 10;
   in.flen = 20;
   in.slen = SCOLS+1;

   for(i=0; key != F1 && i<SROWS+1; i++) {
      consoleClear( );
      in.x = 2;
      in.offset = 0;
      in.start = 0;
      strcpy(in.line, llines[i]);
      for(j=0; j<SROWS; j++, in.x++) {
         consoleMove(in.x, in.y);
         consolePutS(msg[j]);
      }
      consoleMove(2, 2);
      consolePutS("TEST 6");

      infoscreen(&in);
      key = consoleEdit(in.line, in.slen, in.x+2, in.y+1, in.flen,
                                    &in.start, &in.offset, &in.io, in.ctype);

      in.ctype = in.ctype ? (in.ctype << 1) : 1;
      in.io = !in.io;

      endkey(key, end);

      sprintf(msg2, "string: '%s'", in.line);
      consoleDraw(msg2, consoleGetRows( )-5, in.y, SCOLS);
      sprintf(msg2, "Test ended with the '%s' key: ", end);
      consoleDraw(msg2, consoleGetRows( )-3, in.y, SCOLS);
      strcpy(msg2, "Press any key to continue...");
      consoleDraw(msg2, consoleGetRows( )-2, in.y, SCOLS);
      consoleMove(consoleGetRows( )-2, strlen(msg2)+in.y);
      consoleGetKey( );
   }
   free(in.line); /* removing allocated memory */
   return key;
}

void infoscreen(info *p) {
   char msg[SCOLS];
   consoleMove(++p->x, p->y);
   if(p->slen < SCOLS) {
      sprintf(msg, "string:  '%s'", p->line);
   }
   else {
      sprintf(msg, "string: '");
      strncat(msg, p->line, 40);
      msg[50]='\0';
      strcat(msg, "'...");
   }
   consolePutS(msg);
   consoleMove(++p->x, p->y);
   sprintf(msg, "slen:    %.2d", p->slen+1);
   consolePutS(msg);
   consoleMove(++p->x, p->y);
   sprintf(msg, "row:     %.2d", p->x+9); /* displayed 9 earlier lines */
   consolePutS(msg);
   consoleMove(++p->x, p->y);
   sprintf(msg, "col:     %.2d", p->y);
   consolePutS(msg);
   consoleMove(++p->x, p->y);
   sprintf(msg, "flen:    %.2d", p->flen);
   consolePutS(msg);
   consoleMove(++p->x, p->y);
   sprintf(msg, "start:   %.2d", p->start);
   consolePutS(msg);
   consoleMove(++p->x, p->y);
   sprintf(msg, "offset:  %.2d", p->offset);
   consolePutS(msg);
   consoleMove(++p->x, p->y);
   sprintf(msg, "mode:    '%s'", p->io ? "insert" : "overstrike");
   consolePutS(msg);
   consoleMove(++p->x, p->y);
   sprintf(msg, "ctype:   %.2d", p->ctype);
   consolePutS(msg);
   consoleBox(++p->x+1, p->y, p->flen+2, 3, '+', '-', '|');
}

void endkey(int k, char *s) {
   switch(k) {
      case F1: strcpy(s,"F1"); break;
      case F2: strcpy(s,"F2"); break;
      case F3: strcpy(s,"F3"); break;
      case F4: strcpy(s,"F4"); break;
      case F5: strcpy(s,"F5"); break;
      case F6: strcpy(s,"F6"); break;
      case F7: strcpy(s,"F7"); break;
      case F8: strcpy(s,"F8"); break;
      case F9: strcpy(s,"F9"); break;
      case F10: strcpy(s,"F10"); break;
      case END:  strcpy(s,"END"); break;
      case HOME: strcpy(s,"HOME"); break;
      case UP: strcpy(s,"UP"); break;
      case DOWN: strcpy(s,"DOWN"); break;
      case LEFT: strcpy(s,"LEFT"); break;
      case RIGHT: strcpy(s,"RIGHT"); break;
      case PGUP: strcpy(s,"PGUP"); break;
      case PGDN: strcpy(s,"PGDN"); break;
      case TAB: strcpy(s,"TAB"); break;
      case BS: strcpy(s,"BS"); break;
      case DEL: strcpy(s,"DEL"); break;
      case ESC: strcpy(s,"ESC"); break;
      case INS: strcpy(s,"INS"); break;
      case ENTER: strcpy(s,"ENTER"); break;
      default:
         if(k >= ' ' && k <= '~') {
            sprintf(s, "%c", k);
         }
         else {
            strcpy(s,"Not a Special Key!");
         }
         break;
   }
}
char* my_alloc(ul size) {
   return (char *) malloc(sizeof(char) * size);
}
