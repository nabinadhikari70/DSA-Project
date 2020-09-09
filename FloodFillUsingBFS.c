#include<stdio.h>
#include<windows.h>
#include<stdbool.h>
#include<ctype.h>

#define MM 10                           // limit for matrix
#define NN 10

#define M 1000                         // limit for queueLimit
#define N 2
int q[M][N],front=0,rear=0,flag;        // variable for queue

int row[]={-1,-1,-1,0,0,1,1,1};         //possible combination for movement
int col[]={-1,0,1,-1,1,-1,0,1};


char mat[MM][NN] =                                                      // array defination of image
{
    { 'Y', 'Y', 'Y', 'G', 'G', 'G', 'G', 'G', 'G', 'G' },
    { 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'G', 'X', 'X', 'X' },
    { 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'X', 'X', 'X' },
    { 'W', 'W', 'W', 'W', 'W', 'G', 'G', 'G', 'G', 'X' },
    { 'W', 'R', 'R', 'R', 'R', 'R', 'G', 'X', 'X', 'X' },
    { 'W', 'W', 'W', 'R', 'R', 'G', 'G', 'X', 'X', 'X' },
    { 'W', 'B', 'W', 'R', 'R', 'R', 'R', 'R', 'R', 'X' },
    { 'W', 'B', 'B', 'B', 'B', 'R', 'R', 'X', 'X', 'X' },
    { 'W', 'B', 'B', 'X', 'B', 'B', 'B', 'B', 'X', 'X' },
    { 'W', 'B', 'B', 'X', 'X', 'X', 'X', 'X', 'X', 'X' }
};

void queuePush(int x ,int y)
{
  if(rear-front>=M)
    printf("Queue limit Exceed\n");
  else
    q[rear][0]=x;
    q[rear][1]=y;
    rear++;
}

int * queuePop()
{
  static int temp[]={0};
    temp[0]=q[front][0];
    temp[1]=q[front][1];
    front++;
    return temp;
}
bool checkQueueEmpty()
{
  return (rear==front);
}

void queuedisplay()
{
  int i;
  printf("\n---FRONT---\n");
  for(i=front;i<rear;i++)
  {
    printf("\n(%d,%d)\n",q[i][0],q[i][1]);
  }
  printf("\n---REAR---\n");
}

bool isOkayToUse(int x,int y,char target)                      //checking for the boundary of the color
{
  return (x >= 0 && x < MM && y >= 0 && y < NN) && mat[x][y] == target;
}

void floodfill(int x, int y, char replacement)
{
  int * ret;
  queuePush(x,y);
  char target=mat[x][y];
  while(!checkQueueEmpty())
  {
    ret=queuePop();
    x=*ret;                                                               // getting x and y of the current queue
    y=*(ret+1);
    mat[x][y]=replacement;
    for (int k = 0; k < 8; k++)
    {
        if (isOkayToUse(x + row[k], y + col[k], target))                    // checking for boundary colors
        {
            queuePush(x + row[k], y + col[k]);
        }
    }
  }
}

void display()
{
  HANDLE  hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                                                       // for colors
  int square=219;

  for (int i = 0; i < 10; i++)
  {
    printf("%d",i);
      for (int j = 0; j < 10; j++)
      {
        switch (mat[i][j]) {
          case 'O':
              SetConsoleTextAttribute(hConsole, 14);
              printf("%c",square);
              break;
          case 'X':
              SetConsoleTextAttribute(hConsole, 11);
              printf("%c",square);
              break;
          case 'N':
            SetConsoleTextAttribute(hConsole, 10);
            printf("%c",square);
            break;
          case 'M':
            SetConsoleTextAttribute(hConsole, 15);
            printf("%c",square);
            break;
          case 'B':
            SetConsoleTextAttribute(hConsole, 9);
            printf("%c",square);
            break;
          case 'G':
            SetConsoleTextAttribute(hConsole, 10);
            printf("%c",square);
            break;
          case 'S':
            SetConsoleTextAttribute(hConsole, 11);
            printf("%c",square);
            break;
          case 'R':
            SetConsoleTextAttribute(hConsole, 12);
            printf("%c",square);
            break;
          case 'P':
            SetConsoleTextAttribute(hConsole, 13);
            printf("%c",square);
            break;
          case 'Y':
            SetConsoleTextAttribute(hConsole, 14);
            printf("%c",square);
            break;
          case 'W':
            SetConsoleTextAttribute(hConsole, 15);
            printf("%c",square);
            break;
         default:
            SetConsoleTextAttribute(hConsole, 1);
            printf("%c",square);
            break;
        }
    }
    printf("\n");
    if (i==9)
      printf(" ");
    for(int k=0;i==9 && k<10;k++)
      printf("%d",k);
  }
}

int main()
{

  int x,y;                                                           //intial location
  char replacement;                                                      // replacement

  display();
  while(1)
  {
  printf("\n\n");
  printf("---------Enter block in (x,y) cordinate to change-----------\n");
  scanf("%d%d",&x,&y);

  while(1)
  {
  printf("\n\n");
  printf("--------Enter the Required color from below----------\n1.\tBlue(B)\n2.\tGreen(G)\n3.\tSky Blue(S)\n4.\tRed(R)\n5.\tPink(P)\n6.\tYellow(Y)\n7.\tWhite(W)\n\n");
  fflush(stdin);
  scanf("%c",&replacement);
  if(mat[x][y]==toupper(replacement))
    printf("----Same color!!!!! Enter another color-----\n");
  else
    break;
  }

  floodfill(x, y, toupper(replacement));                                          //filling process

  display();
  }
}
