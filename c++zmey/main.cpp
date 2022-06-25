#include <iostream>
#include <windows.h>
#include <cstring>
#include <cstdio>
using namespace std;
void MoveXY(int x,int y)
{
    COORD pos;
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
#define mWidth 80
#define mHeight 25

struct TMap{
    char map1[mHeight][mWidth+1];
    void Clear();
    void Show();
};
enum TDirection{dirLeft,dirRight,dirUp,dirDown};
enum TResult{reOk,reKill};
#define sLen 1000
class TSnake{
    int x,y;
    TMap*mp;
    TDirection dir;
    POINT tail[sLen];
    int len;
    int score;
    POINT OutTextPos;
public:
    void AddTail(int _x,int _y);
    void MoveTail(int _x,int _y);
    void AddTailCnt(int _x,int _y,int cnt);
    TSnake(TMap*_mp,int outX,int outY);
    void Init(int _x,int _y,TDirection _dir);
    void PutOnMap();
    TResult UserControl(char w,char s,char a,char d);
    void IncScore();
};
void TSnake::IncScore()
{
    score++;
}
void TSnake::AddTailCnt(int _x,int _y,int cnt)
{
    for(int i=0;i<cnt;i++)
        AddTail(_x,_y);
}
void TSnake::MoveTail(int _x,int _y)
{
    for(int i=len-1;i>=0;i--)
        tail[i+1]=tail[i];
    tail[0].x=_x;
    tail[0].y=_y;
}
void TSnake::AddTail(int _x,int _y)
{
    MoveTail(_x,_y);
    len++;
    if(len>=sLen)len=sLen-1;
}

TResult TSnake::UserControl(char w,char s,char a,char d)
{
    POINT old;
    old.x=x;
    old.y=y;
    if(GetKeyState(w)<0)dir=dirUp;
    if(GetKeyState(s)<0)dir=dirDown;
    if(GetKeyState(a)<0)dir=dirLeft;
    if(GetKeyState(d)<0)dir=dirRight;
    if(dir==dirLeft)x--;
    if(dir==dirRight)x++;
    if(dir==dirUp)y--;
    if(dir==dirDown)y++;
    if((x<0)||(x>=mWidth)||(y<0)||(y>=mHeight)||(mp->map1[y][x]=='+'))
        return reKill;
        if(mp->map1[y][x]=='*')
            AddTailCnt(old.x,old.y,5);
        else
        MoveTail(old.x,old.y);
    return reOk;
}
void TSnake::Init(int _x,int _y,TDirection _dir)
{
    x=_x;
    y=_y;
    dir=_dir;
    len=0;
}
void TSnake::PutOnMap()
{
    char str[10];
    sprintf(str,"%d",score);
    for(int i=0;i<strlen(str);i++)
        mp->map1[OutTextPos.y][OutTextPos.x+i]=str[i];
    mp->map1[y][x]='@';
    for(int i=0;i<len;i++)
        mp->map1[tail[i].y][tail[i].x]='+';
}
TSnake::TSnake(TMap*_mp,int outX,int outY)
{
    mp=_mp;
    Init(0,0,dirRight);
    score=0;
    OutTextPos.x=outX;
    OutTextPos.y=outY;
}


void TMap::Show()
{
    MoveXY(0,0);
    map1[mHeight-1][mWidth-1]='\0';
    for(int j=0;j<mHeight;j++)
        cout<<map1[j];
}
void TMap::Clear()
{
    for(int i=0;i<mWidth;i++)
        map1[0][i]=' ';
    map1[0][mWidth]='\0';
    for(int j=1;j<mHeight;j++)
        strncpy(map1[j],map1[0],mWidth+1);
    map1[12][20]='*';
    map1[12][60]='*';
    map1[5][40]='*';
    map1[20][40]='*';
}
int main()
{
    int userCnt=2;
    TMap map1;
    TSnake snake1(&map1,3,1);
    TSnake snake2(&map1,77,1);
    snake1.Init(10,5,dirRight);
    snake2.Init(70,5,dirRight);

    do{
            bool kill1=snake1.UserControl('W','S','A','D')==reKill;
       if((kill1)||((userCnt>=2)&&
            (snake2.UserControl(VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT)==reKill)))
       {
           snake1.Init(10,5,dirRight);
           snake2.Init(70,5,dirLeft);
           if(kill1)
                snake2.IncScore();
           else
                snake1.IncScore();
       }

        map1.Clear();
        snake1.PutOnMap();
        if(userCnt>=2)snake2.PutOnMap();
        map1.Show();
        Sleep(80);
    }while(GetKeyState(VK_ESCAPE)>=0);

    return 0;
}
