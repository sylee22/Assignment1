void consoleDraw(char *sd, int row, int col, int len)
{
/* <SY>This function is used to display a text field containing
the string 'sd' on the screen.*/
  int i;

  if(sd && row>=0 && col>=0){
    consoleMove(row,col);               //set position

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
