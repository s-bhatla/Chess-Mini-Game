x
#include<graphics.h>
#include<stdio.h>
#include<dos.h>
#include<conio.h>
void printBoard();
void welcome();
void printrules();
void setBoard();
int checkCuts(char moved);
int pawnMoves();
void printscreen(int);
void printmatrix();
char rookChar = 'R';   //setting player's piece

int endgame = 0;

char board[8][8];    //matrix representing chess board
int p[5][3] = {{1,0,1}, {1,1,1}, {1,2,1}, {1,3,1}, {1,4,1}};          //The 3rd element is 0 or 1 denoting if the pawn is alive or not
								      // the first two elements represnt pawn's coordinates
int r[2] = {7, 7};
int pawnsDead;

void main()
{   int i,j,result=2,flag=0;
    int rmove[2];              //stores the coordinates entered by the user
    welcome();                 //function to print welcome screen
    printrules();              //functioon to print rules
 for (i = 0; i<8; i++)
 {
	for (j = 0; j<8; j++)
    {
	    board[i][j] = 32;                //setting value to space
	}
 }
    setBoard();
    printBoard();                       //printing the initialised board

    while (1)
    {
	 pawnsDead=0;                     //counter to store the number of dead pawns
	if(pawnsDead == 5)
    {
	    result=1;
	    printscreen(result);         //calling function to print final screen
	    return 0;
	}
	if (endgame == 1)
    {
	    result=0;
	    printscreen(result);
	    return 0;
	}
	printf("\n\n Where do you wish to move the rook ? : ");
	scanf("%d %d",&rmove[0],&rmove[1]);
	if(rmove[0]<1 || rmove[0]>8 || rmove[1]<1 || rmove[1]>8)
       {  printBoard();
	  printf("\n Invalid Input! Try again!");
	  continue;
       }
        rmove[0]--;                                         //decreasing the input coordinates by 1
	rmove[1]--;
	if (rmove[0] != r[0] && rmove[1] != r[1])              //if rook does not move in a line
    {
	    printf("That's not a valid move! Try again.");
	    continue;
	}
	//int flag=0;
	if (rmove[1] == r[1])                                //if rook encounters a pawn while moving across a column
    {   if (rmove[0] < r[0])
        {
            for (i=r[0]; i>rmove[0]; i--)
            {
                for( j=0; j<5;j++)
                {
                    if(p[j][0]==i && p[j][1]==rmove[1] && p[j][2]==1)
                    { rmove[0]=p[j][0];                   //setting the rook's coordnate to first encountered pawn
                      p[j][2]=0;
                      //pawnsDead++;
                      flag=1;
                      break;
                    }
                }
		        if(flag==1)
                {
                    break;
                }
	     }
	    }
	
	     else if(rmove[0] > r[0])
        {
             for(i = r[0]; i < rmove[0]; i++)
             {
                 for(j=0; j<5;j++)
                 {
                     if(p[j][0]==i  &&p[j][1]==rmove[1] && p[j][2]==1)
                     {
                         rmove[0]=p[j][0];
                         p[j][2]=0;
                         //pawnsDead++;
                         flag=1;
                         break;
                    }
		  }
		        if(flag==1)
                {
                    break;
                }
            }
	 }
}

 flag=0;
 if(rmove[0]==r[0])                                   //if rook encounters a pawn while moving across a row
       { if(rmove[1]<r[1])
            {    
                for(i=r[1]; i>=rmove[1] ; i--)
                {
                      for(j=0; j<5;j++)
                      {                                      //at each cell, check if alive pawn is encountered  
                         if(p[j][1]==i && p[j][2]==1 && p[j][0]==rmove[0])
                         {
                            rmove[1]=p[j][1];                                   //change rook's destination to the first pawn encountered
                            p[j][2]=0;
			    //pawnsDead++;
                            flag=1;
                            break;
                         }
                    }
                    if(flag==1)
                    {
                        break;
                    }
                }                     
            }
             
	    else if(rmove[1] > r[1])
	    {
                 for( i = r[1]; i <= rmove[1]; i++)
                 {
                     for(j=0; j<5;j++)
                    {
                         if(p[j][1]==i && p[j][2]==1 && p[j][0]==rmove[0]) 
                        {
                            rmove[1]=p[j][1];
                            p[j][2]=0;
			    //pawnsDead++;
                            flag=1;
                            break;
                         }
                    }
                    if(flag==1)
                    {
                        break;
                    }

                 }
        } 
	} 


        r[0] = rmove[0];                          //setting rook's coordinate
        r[1] = rmove[1];
	for (i = 0; i < 8; i++)
	{
	    for (j = 0; j < 8; j++)
        {
            board[i][j] = 32;                //setting value to space
		}
	}
        endgame = checkCuts('r');          
        setBoard();
        printBoard();
	for (i=0; i<5; i++)
	{
	    if (p[i][2] == 0)
	    {
            pawnsDead++;
	    }                                    //write for checking if all pawns are cut...
	}
    if(pawnsDead == 5)
    {
	    result=1;
	    printscreen(result);         //calling function to print final screen
	    return 0;
	}
	printf("\nComputer is thinking...\n", pawnsDead);
	sleep(1);
	endgame = pawnMoves();
    }
}

void printBoard()                   //function to print the board onto the terminal
{
    int i,k,j;
    clrscr();                     //Just clearing the screen to avoid clutter
    printf("\n\n\n");
    printf(" ");
    for (k = 0; k < 35; k++)
    {
        printf("-");
    }
    printf("\n");
    for (i = 0; i < 8; i++)
    {
        printf("%d |", i + 1);
        for (j = 0; j < 8; j++)
        {
            if(board[i][j]==rookChar)
            {
                textcolor(YELLOW);
                cprintf(" %c ", board[i][j]);
                textcolor(WHITE);
                cprintf("|");
            }
            else if(board[i][j]=='p')
            {
                textcolor(LIGHTMAGENTA);
                cprintf(" %c ", board[i][j]);
                textcolor(WHITE);
                cprintf("|");
            }
            else 
            {
                printf("   |");
            }

        }
    printf("\n ");
    for (k = 0; k < 35; k++)
    {
        printf("-");
    }
    printf("\n");
    }
    printf(" ");
    for (i = 0; i < 8; i++)
    {
        printf("   %d", i+1);
    }
    printf("\n\n");
}

void setBoard()
{
    int i,j;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            board[i][j] = 32;                //first sets the value to space
        }
    }
    for (i = 0; i < 5; i++)
    {                                        //assigns pawn to the coordinate and removes dead pawn
        if (p[i][2] == 0)
        {
            board[p[i][0]][p[i][1]] = 32;
        }
        else
        {
            board[p[i][0]][p[i][1]] = 'p';
        }
    }
    board[r[0]][r[1]] = rookChar;
}

int checkCuts(char moved)
{   int i,j;
    for (i = 0; i < 5; i++)
    {
        if (r[0] == p[i][0] && r[1] == p[i][1])
        {
            if (moved == 'r')
            {                          //if rook is moved to pawn's coordinate, pawn dies, rook takes its place
                p[i][2] = 0;
                sound(400);
                delay(50);
                nosound();
            }
            if (moved == 'p')
            {                           //if pawn is moved and coordinates of pawn and rook are the same, return 1
                if (p[i][2] != 0)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}


int pawnMoves()
{   int i,j,temp,whichP;
    startPawnMoves:
    for (i = 0; i < 5; i++)
    {
        if (p[i][0] + 1 == r[0] && p[i][1] + 1 == r[1])
        {    //checks if there's a rook diagonal to pawn
            p[i][0]++;
            p[i][1]++;
            setBoard();   //updates the board to remove the rook
            printBoard();
            printf("\n\nComputer moves pawn to %d, %d", p[i][0]+1, p[i][1]+1);
            temp = checkCuts('p');
            if (temp == 1)
            {                       //checks if the pawn moved to rook's position is not dead
                rookChar = 'p';    //since rook is dead
                setBoard();
                printBoard();
                
                return 1;       //exit game
            }
        }
        if (p[i][0] + 1 == r[0] && p[i][1] - 1 == r[1])
        {                                        //if rook is diagonally stationed on the other side of the pawn
            p[i][0]++;
            p[i][1]--;
            setBoard();
            printBoard();
            printf("\n\nComputer moves pawn to %d, %d", p[i][0]+1, p[i][1]+1);
            temp = checkCuts('p');
            if (temp == 1)
            {
                rookChar = 'p';
                setBoard();
                printBoard();
                printf("");
                return 1;
            }
        }
    }
   /* Intializes random number generator */
    srand(time(0));
    whichP = (rand() % 5);
    if (p[whichP][0] + 1 == r[0] && p[whichP][1] == r[1])
    {
        if(r[0]!=7)
        {
            goto startPawnMoves;                                 
        }
        else
        {   
            if(pawnsDead == 4){                                           //exiting if rook is at the end of the chesss board
                return 1;
            }
            else{
                goto startPawnMoves;
            }
        }
    }

    if (p[whichP][2] == 0)
    {
        goto startPawnMoves;
    }
    p[whichP][0]++;

    setBoard();
    printBoard();
    printf("\n\nComputer moves pawn to %d, %d", p[whichP][0]+1, p[whichP][1]+1);      //printing the computer's moves
    temp = checkCuts('p');

    if (temp == 1)
    {
        return 1;                      //checking cuts for the pawn's moves
    }
    if (p[whichP][0] == 7)
    {
        return 1;                      //checking if the pawn has won.
    }
    return 0;
}
                                             

void printscreen(int result)
{  int m,k=50;
   int gd=DETECT,gm;
   initgraph(&gd,&gm,"c:\\turboc3\\bgi");
   if(result==1)
   { setcolor(GREEN);
     outtextxy(220,220,"YOU WON!!");
     for(m=200;m<260;m++)
     {setcolor(GREEN);
     outtextxy(220,220,"YOU WON!!");
     sound(m+50*sin(m));
     delay(50);
     setcolor(BLACK);
     outtextxy(220,220,"YOU WON!!");
     nosound();
     }
 nosound();
 }
  if(result==0)
  { setcolor(RED);
    outtextxy(220,220,"YOU LOST");
     for(m=200;m<260;m++)
    {setcolor(RED);
     outtextxy(220,220,"YOU LOST!!");
     sound(m+50*sin(m));
     delay(50);
     setcolor(BLACK);
     outtextxy(220,220,"YOU LOST!!");
     delay(50);
     nosound();
     }
   nosound();     
}
delay(200);
closegraph();
}

void welcome()
{ int m,lx,ly,rx,ry,j,i,i2,j2,k,n;       //welcome screen starts
   int flag=0;
   int gd=DETECT,gm;                      //initialising the grahic driver 
   initgraph(&gd,&gm,"c:\\turboc3\\bgi");
   lx=1; ly=1; rx=639; ry=479;              //the intial coordinates of top left and bottom right 
  while( lx<220 && rx>420 && ly<140 && ry>340)
{  for(j=ly;j<ry;j=j+50)                    //animating the first line
   { sound(320);                            
     setcolor(WHITE);                       //changing the color to white
     line(lx,j,lx,j+50);
     delay(10);
     nosound();
    sound(360);
    delay(10);
    nosound();
	}
    sound(405);
    delay(10);
    nosound();
    sound(432);
    nosound();
for(i=lx;i<rx;i=i+50)                       //animating second line 
    { sound(480);
      setcolor(YELLOW);                     //changing color to yellow
      line(i,ry,i+50,ry);
      delay(10);
       nosound();
      sound(540);
      delay(10);
     nosound();
     }
   sound(640);
   delay(10);
   nosound();
   sound(540);
   delay(10);
   nosound();
  for(j2=ry;j2>ly;j2=j2-50)                //animating the third line
    { sound(480);
      setcolor(WHITE);                     //changing the color to white
      line(rx,j2,rx,j2-50);
      delay(10);
     nosound();
     sound(432);
     delay(10);
     nosound();
    }
  sound(405);
   delay(10);
  nosound();
  sound(360);
   delay(10);
  nosound();
   for(i2=rx;i2>lx;i2=i2-50)            //animating the fourth line
    { sound(320);
      setcolor(YELLOW);                 //changing the color to yellow 
      line(i2,ly,i2-50,ly);
      delay(10);
      nosound();
      sound(288);
      delay(10);
      nosound();
   }
lx=lx+20;                                //updating the four coordinates
 ly=ly+20;
 rx=rx-20;
 ry=ry-20;
}

 for(k=1;k<9;k++)                        //loop to keep changing colors of the text
 { setcolor(k);
   outtextxy(220,220,"Welcome to Chess Mini Game");    //function to print statement at given coordinate

 for(m=0;m<10;m++)                                   //loop for audio
 { sound(360+m*20);
    for(n=0,j=10;n<10,j>0;n++,j--)
     { sound((360+m*20)+n*10);
       delay(2);
       sound((360+m*20)+j*10);
       delay(2);
     }
  nosound();
  }
  setcolor(0);
  if(k==8)
  break;
  outtextxy(220,220,"Welcome to Chess Mini Game");
  delay(2);
  nosound();
  }
 closegraph(); 
 delay(200);
}


void printrules()                                      //function for printing the rules
{   int i;
     textcolor(YELLOW);
    for (i = 0; i < 70; i++)
    {
	cprintf("*");
    }
    textcolor(GREEN);
    cprintf("\r\nROOK vs. 5 PAWNS\r\n");
    textcolor(YELLOW);
    for (i = 0; i < 70; i++)
    {
	cprintf("*");
    }
    cprintf("\r\n\r\n");

    cprintf("Rules of the Game: \r\n");
    cprintf("1) The Player plays as the rook.\r\n");
    cprintf("2) The rook must eliminate all the pawns before they reach the end of the board.\r\n");
    cprintf("3) If the rook gets eliminated or if any one of the pawns reach the end of the board, then the player LOSES.\r\n");
    cprintf("4) If all the pawns are successfully eliminated before reaching the end, the player WINS.\r\n\r\n");

    cprintf("BEST OF LUCK !");
    delay(10000);
    textcolor(WHITE); 
    printmatrix();                                  //to hold the screen
    delay(5000);
    clrscr();
}

void printmatrix()
{   
    
    int i,k,j;
    clrscr();                     //Just clearing the screen to avoid clutter
    printf("\n Layout of the chess board is as follows (Use for providing input):");
    printf("\n\n\n");
    printf(" ");
    for (k = 0; k < 35; k++)
    {
        printf("-");
    }
    printf("\n");
    for (i = 0; i < 8; i++)
    {
        printf("%d |", i + 1);
        for (j = 0; j < 8; j++)
        {
            textcolor(LIGHTCYAN);
            cprintf("%d %d", i + 1, j + 1);
            textcolor(WHITE);
            printf("|");
        }
    printf("\n ");
    for (k = 0; k < 35; k++)
    {
        printf("-");
    }
    printf("\n");
    }
    printf(" ");
    for (i = 0; i < 8; i++)
    {
        printf("   %d", i+1);
    }
    printf("\n\n");

}
