#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#define sh 20
#define vi 25
#define PI 3.14159265
int sc=0;
int f;
float ug=0;
unsigned iyy=0;
typedef struct tch
{
    int x,y;



} tch;
tch fig[4];
char map[vi+1][sh+1];
char mapc[vi+1][sh+1];
char cop[sh+1];
void setcur(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void init_st()
{
  for(int i=0;i<sh;i++)
        map[vi][i]='#';
        map[vi][sh]='\0';
        strcpy(map[0],map[vi]);
  for(int i=1;i<sh-1;i++)
    map[0][i]='.';
    strcpy(cop,map[0]);
    for(int i=1;i<vi;i++)
        strcpy(map[i],map[0]);
}
void st_show()
{
    setcur(0,0);
    for(int i=0;i<vi+1;i++)
        puts(mapc[i]);
}
void clir_str(int s)
{
for(int i=s;i>0;i--)
strcpy(mapc[i],mapc[i-1]);
strcpy(mapc[0],cop);
sc++;

}

void clir()
{
    Sleep(1000);
    for(int i=vi-1;i>=0;i--)
    {
        if(!strcmp(mapc[vi],mapc[i]))
        {
           strcpy(mapc[i],cop);
           st_show();
           Sleep(1000);
           clir_str(i);
           i++;
            st_show();
             Sleep(1000);
        }
    }

}
void turn();
void init_fig()
{
    f=rand()%6+1;
//f=5;
ug=0;
fig[0].x=sh/2;
fig[0].y=2;
turn();


}
void put_fig()
{
for(int i=0;i<4;i++)
    mapc[fig[i].y][fig[i].x]='#';
}
int coll(int dx,int dy);
void rcopp();
void vert_mov()
{
   if(!coll(0,1))
   {

      for(int i=0;i<4;i++)
        fig[i].y++;
   }
   else
   {
       if(fig[0].y<4)
       {
           sc=0;
            init_st();
            copp();
       }

    clir();
     rcopp();

     init_fig();

   }

}
void hor_mov(int dx)
{
     if(!coll(dx,0))
     {
          for(int i=0;i<4;i++)
        fig[i].x+=dx;
     }

}
int coll(int dx,int dy)
{
    for(int i=0;i<4;i++)
        if(map[fig[i].y+dy][ fig[i].x+dx]!='.')return 1;

    return 0;
}
void copp()
{
    for(int i=0;i<vi+1;i++)
        strcpy(mapc[i],map[i]);
}
void rcopp()
{
     for(int i=0;i<vi+1;i++)
        strcpy(map[i],mapc[i]);
}
void turn()
{
    if(f==1)
    {
        fig[1].x=fig[0].x+(int)round(sin(ug*PI/180));
        fig[1].y=fig[0].y+(int)round(cos(ug*PI/180));
        fig[2].x=fig[0].x+(int)round(sin((ug+180)*PI/180));
        fig[2].y=fig[0].y+(int)round(cos((ug+180)*PI/180));
        fig[3].x=fig[0].x+(int)round(sin((ug+315)*PI/180));
        fig[3].y=fig[0].y+(int)round(cos((ug+315)*PI/180));
    }
    if(f==2)
    {
         fig[1].x=fig[0].x+(int)round(sin(ug*PI/180));
        fig[1].y=fig[0].y+(int)round(cos(ug*PI/180));
        fig[2].x=fig[0].x+(int)round(sin((ug+180)*PI/180));
        fig[2].y=fig[0].y+(int)round(cos((ug+180)*PI/180));
        fig[3].x=fig[0].x+(int)round(sin((ug+45)*PI/180));
        fig[3].y=fig[0].y+(int)round(cos((ug+45)*PI/180));
    }
    if(f==3)
    {
        fig[1].x=fig[0].x+(int)round(sin(ug*PI/180));
        fig[1].y=fig[0].y+(int)round(cos(ug*PI/180));
        fig[2].x=fig[0].x+(int)round(sin((ug+90)*PI/180));
        fig[2].y=fig[0].y+(int)round(cos((ug+90)*PI/180));
        fig[3].x=fig[0].x+(int)round(sin((ug+135)*PI/180));
        fig[3].y=fig[0].y+(int)round(cos((ug+135)*PI/180));

    }
    if(f==4)
    {
        fig[1].x=fig[0].x+(int)round(sin((ug+90)*PI/180));
        fig[1].y=fig[0].y+(int)round(cos((ug+90)*PI/180));
        fig[2].x=fig[0].x+(int)round(sin((ug+180)*PI/180));
        fig[2].y=fig[0].y+(int)round(cos((ug+180)*PI/180));
        fig[3].x=fig[0].x+(int)round(sin((ug+45)*PI/180));
        fig[3].y=fig[0].y+(int)round(cos((ug+45)*PI/180));
    }
    if(f==5)
    {
        fig[1].x=fig[0].x+(int)round(sin((90)*PI/180));
        fig[1].y=fig[0].y+(int)round(cos((90)*PI/180));
        fig[2].x=fig[0].x+(int)round(sin((180)*PI/180));
        fig[2].y=fig[0].y+(int)round(cos((180)*PI/180));
        fig[3].x=fig[0].x+(int)round(sin((135)*PI/180));
        fig[3].y=fig[0].y+(int)round(cos((135)*PI/180));
    }
    if(f==6)
    {
        fig[1].x=fig[0].x+(int)round(sin(ug*PI/180));
        fig[1].y=fig[0].y+(int)round(cos(ug*PI/180));
        fig[2].x=fig[0].x+(int)round(sin((ug+180)*PI/180));
        fig[2].y=fig[0].y+(int)round(cos((ug+180)*PI/180));
        fig[3].x=fig[0].x+(int)round(sin((ug+90)*PI/180));
        fig[3].y=fig[0].y+(int)round(cos((ug+90)*PI/180));
    }
    if(f==7)
    {
        fig[1].x=fig[0].x+(int)round(sin(ug*PI/180));
        fig[1].y=fig[0].y+(int)round(cos(ug*PI/180));
        fig[2].x=fig[0].x+(int)round(sin((ug+180)*PI/180));
        fig[2].y=fig[0].y+(int)round(cos((ug+180)*PI/180));
        fig[3].x=fig[0].x+2*(int)round(sin((ug)*PI/180));
        fig[3].y=fig[0].y+2*(int)round(cos((ug)*PI/180));
    }
    Sleep(100);
}


int main()
{
    srand(time(NULL));
init_st();
copp();
//imit();
init_fig();


do
{
put_fig();
st_show();
if((iyy++)%7==0)vert_mov();
copp();



if(GetKeyState('A')<0)hor_mov(-1);
if(GetKeyState('D') <0)hor_mov(1);
if(GetKeyState('W') <0)
   {
        ug=ug+270;
        if(ug>360)ug=ug-360;
        turn();
   }
 if(GetKeyState(VK_SPACE)<0)iyy=7;

   setcur(40,2);
   printf("score %2d",sc);


Sleep(20);
// clir();
}while(1);

}
