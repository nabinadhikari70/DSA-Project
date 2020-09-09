#include<stdio.h>
#include<windows.h>
#include<stdbool.h>
#include<ctype.h>

#define MM 74                           // limit for matrix
#define NN 252

int row[]={-1,-1,-1,0,0,1,1,1};         //possible combination for movement
int col[]={-1,0,1,-1,1,-1,0,1};


char matTemp[150][252];                                                      // array defination of image
char mat[MM][NN];

void arrayMaker()
{
  int k=0;
  FILE* inp;
  inp = fopen("c.txt","r");		//filename of your data file
  int i = 0,j;
  char r = (char)fgetc(inp);
  while(!feof(inp)){	//read till , or EOF
        if(r=='\n')
        {
            r = (char)fgetc(inp);
            i++;
            k=0;
        }
        matTemp[i][k] = r;
        k++;
        r = (char)fgetc(inp);
    }
  for(i=0;i<74;i++)
  {
    for (size_t j = 0; j < 252; j++)
        mat[i][j]=matTemp[i][j];
  }
}

bool isOkayToUse(int x,int y,char target)                      //checking for the boundary of the color
{
  return (x >= 0 && x < MM && y >= 0 && y < NN) && mat[x][y] == target;
}

void floodfill(int x, int y, char replacement)
{
  char target=mat[x][y];
    mat[x][y]=replacement;
    for (int k = 0; k < 8; k++)
    {
        if (isOkayToUse(x + row[k], y + col[k], target))                    // checking for boundary colors
        {
            floodfill(x + row[k], y + col[k], replacement);
        }
    }
}

void display()
{
  HANDLE  hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                                                       // for colors
  int square=219;

  for (int i = 0; i < 74; i++)
  {
    printf("%3d",i);
      for (int j = 0; j < 252; j++)
      {
        switch (mat[i][j]) {
          case 'O':
              SetConsoleTextAttribute(hConsole, 14);
              printf("%c",square);
              break;
          case 'X':
              SetConsoleTextAttribute(hConsole, 4);
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
    if (i==73)
      printf("   ");
    for(int k=0;i==73 && k<252;k++)
    {
      printf("%d",k%10);
    }
    if (i==73)
    {
      printf("\n");
      printf("   ");
      printf("0");
    }
    for(int k=1;i==73 && k<26;k++)
    {
      printf("%10d",k);
    }
}
}

void arraydisplay()
{
  for (int i = 0; i < 74; i++) {
    for (int j = 0; j < 252; j++) {
      printf("%c",mat[i][j]);
    }
    printf("\n");
  }
}

int main()
{
  arrayMaker();

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
