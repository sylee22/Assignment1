/***************************************************************************
*   File: test_ConsoleBox.cpp                                                   *
*   Purpose: This function displays a box that will be used to frame a     *
*       text field on the screen.                                              *
*   Tested and working under Windows visual studio AND Matrix              *
*   written by: Xiaodong Chen, Kalid Mahmud                                *
*   Date: May 22 2012                                                      *
*   Version: Complie and test version (meaning dont stick this into main() *
****************************************************************************/

#include <iostream>

using namespace std;

int consoleBox(int row, int col, int l, int h, char edge, char top_btm, char ls_rs);

int main() {
	consoleBox(2, 3, 10, 3, '+', '-', '|'); // change this to what ever value you would like to draw !
	cin.get();

}
	int consoleBox(int row, int col, int l, int h, char edge, char top_btm, char ls_rs)
		{
			int i=0, j=0, row_max, col_max, row_count, col_count,k,height_count;
			row_max =0; // set to zero to prevent error
			col_max =0; // set to zero to prevent error
			row_count =0; // this is used to count the row
			col_count = 0; // counts the columns in numbers (same as above but for col)
			height_count = h - 2; // height count holds the number of characters to type for height subtract the two edge char (count just the char in the middle to print)
			cout << ' ';
			for (k = 0; j < col ; j++)
			{
				cout << col_count; //this prints the column number counter on the screen
				++col_count; // pre increment on the column counter
			}
			cout << col_count; // prints out the final column number

			cout << endl;
			for (i = 0; i < row ; i++)
			{
				cout << row_count << endl; // display the row number then a new line
				++row_count; // pre increment the row counter
			}

			cout << row_count; // prints out the final row number after the last row space

			for (j = 0; j < col ; j++)
			{
			cout << ' ';
			++col_count;
			}
			for (j = col; j < col+l ; j++) //top
				{
					if ( j==col || j==col+l-1)
						{
							cout<<edge;
						}

					else
						{
						cout<<top_btm;
						}
				}
					cout<<endl;

		     for (i = row+1; i < row+h-1 ; i++) //middle
				{
					for (j = 0; j < col ; j++)
					{
						cout << ' ';
					}
					cout << ' ';
					cout << ls_rs;
					for(int m =0; m<l-2; m++)
					{
						cout << ' ';
					}
					cout << ls_rs;
					cout << endl;
				}
			 for (j = 0; j < col ; j++)
			{
			cout << ' ';
			++col_count;
			}
			 cout << ' ';

			for (j = col; j < col+l ; j++) //bottom
				{
					if ( j==col || j==col+l-1)
				    cout<<edge;
					else
					cout<<top_btm;
				}

       /* THE FOLLOWING IS NOT NEEDED AND WILL NOT WORK FOR THE TESTING VERSION!!!**/

//row_max = consoleGetRows(); //return if the window is sufficient for drawing the box
//col_max = consoleGetCols();
//if(row+h > row_max || col+l > col_max)
//return false;
//else
return true;
}
