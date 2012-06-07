/* Programed by: Kalid Mahmud
   Description: Windows Testers
*/
#include <stdio.h>
#include <stdlib.h>
#include "console.h"
#include <conio.h>
#define INSERTKEY 1082 // INSERT KEY IN I/O

#define INSERT 1 // DEFINES INSERT MODE OR OVERSTRIKE MODE FOR TESTING
#define UP 1072
#define DOWN 1080
#define LEFT 1075
#define RIGHT 1077
int main ()
{
	int key = 0;
	int insertmode;
	int overstrikemode;
	int flag =0;
	int row = 0;
	int column = 0;
	int maxrows = consoleGetRows();
	int maxcols = consoleGetCols();

	if(INSERT) {insertmode = 1; overstrikemode = 0; } // if insert mode is true than turn on insertmode and turn off overstrikemode
	if(!INSERT) {insertmode = 0; overstrikemode = 1; } // if insert mode is false than turn off insertmode and turn on overstrikemode

    #if PLATFORM == WINDOWS
	system("title C++ Edit Funtion by Kalid M");
	consoleOn();
	#endif

	key = consoleGetKey();

	#if PLATFORM == WINDOWS
	consoleOff();
	#endif
	printf("***Programmed by: Kalid M***\n\n");
	if(key != INSERTKEY)
	{
	printf("Insert has NOT been pressed\nKey that has been pressed is %d\n\nTIP: Rerun this program and press the INSERT KEY to try this program\n", key);
	}
	else { printf("Please stand by, insert key has been pressed....\n");
	if(overstrikemode) { printf("Overstrike mode has been turned on per your request!\n"); }
	if(insertmode)     { printf("Insert mode has been turned on per your request!\n"); }
	printf("\nYou can quit at any time by double pressing enter\n");
	printf("Max Rows is: %d\nMax Cols is: %d\n", maxrows, maxcols);
	printf("Use your keypad to move. (press down first!)\n");
	printf("You can write in the textbox below ONLY upper case, lower case, numbers, space\nand delete/backspace work!\n");

	consoleBox(2, 3, 50, 10, '+', '-', '|');
	while(flag != 13) {
		if(row > maxrows) { row = maxrows; } // if rows exceed maxiumum than set rows back to max so it doesn't go over
		if (column > maxcols) { column = maxcols; } // if column exceed maximum than set cols back to max so it doesn't go over

		// these two statement makes sure that the cursor does not go beyond the screen
		if(row <0)    { row = 0;}
		if(column <0) { column = 0; }
		if(flag == DOWN) { row += 1; consoleMove(row,column);  }
		if(flag == UP) { row -= 1; consoleMove(row,column); }
		if(flag == LEFT) { column -= 1; consoleMove(row,column);  }
		if(flag == RIGHT) { column += 1; consoleMove(row,column);  }
		flag = consoleGetKey();
		if(flag >=65 && flag <=90) {consolePutC(flag); }
		if(flag >= 97 && flag <=122)  {consolePutC(flag); }
		if(flag == 32) { consolePutC(flag); }
		if(flag == 8) { consolePutC(flag); consolePutC(32); consolePutC(flag);}
		if(flag >= 48 && flag <=57)  {consolePutC(flag); }
	}
	}
	#if PLATFORM == WINDOWS
	getch();
	#endif
	return 0;
}

	int consoleBox(int row, int col, int l, int h, char edge, char top_btm, char ls_rs)

	{
		int i=0, j=0, row_max, col_max, row_count, col_count,k,height_count, m;
		row_max =0; // set to zero to prevent error
		col_max =0; // set to zero to prevent error
		row_count =0; // this is used to count the row
		col_count = 0; // counts the columns in numbers (same as above but for col)
		height_count = h - 2; // height count holds the number of characters to type for height subtract the two edge char (count just the char in the middle to print)
		printf(" ");
		for (k = 0; j < col ; j++)
		{
		//      printf("%d", col_count); //this prints the column number counter on the screen
			++col_count; // pre increment on the column counter
		}
			//printf("%d", col_count); // prints out the final column number

			printf("\n");
			for (i = 0; i < row ; i++)
			{
				//printf("%d\n",row_count); // display the row number then a new line
				++row_count; // pre increment the row counter
			}

			printf(" ");

			for (j = 0; j < col ; j++)
			{
			printf(" ");
			++col_count;
			}
				for (j = col; j < col+l ; j++) //top
					{
						if ( j==col || j==col+l-1)
						{
							printf("%c",edge);
						}

			else
				{
					printf("%c",top_btm);
				}
					}
			printf("\n");

		for (i = row+1; i < row+h-1 ; i++) //middle
			{
				for (j = 0; j < col ; j++)
				{
					printf(" ");
				}
					printf(" ");
					printf("%c", ls_rs);
				for(m =0; m<l-2; m++)
				{
					printf(" ");
				}
					printf("%c", ls_rs);
					printf("\n");
			}

				for (j = 0; j < col ; j++)
			{
				printf(" ");
				++col_count;
			}
				printf(" ");

				for (j = col; j < col+l ; j++) //bottom
			{
				if ( j==col || j==col+l-1)
				printf("%c",edge);
				else
				printf("%c",top_btm);
			}

       /* THE FOLLOWING IS NOT NEEDED AND WILL NOT WORK FOR THE TESTING VERSION!!!**/

			row_max = consoleGetRows(); //return if the window is sufficient for drawing the box
			col_max = consoleGetCols();
			if(row+h > row_max || col+l > col_max)
			return 0;
		else
			return 1;
			}
