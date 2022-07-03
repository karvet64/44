#include <iostream>
#include <windows.h>
#include <cstdio>
#include <cmath>

using namespace std;
const int scr_width=80;
const int scr_height=25;
const int cell_width=8;
const int cell_height=5;
const int fld_width=4;
const int fld_height=4;

typedef char TScreenMap[scr_height][scr_width];
SetCurPos(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
class TScreen
{
    void SetEnd()
    {
        scr[scr_height-1][scr_width-1]='\0';
    }
public:
    TScreenMap scr;
    TScreen()
    {
        Clear();
    }
    void Clear()
    {
        memset(scr,' ',sizeof(scr));
    }
    void Show()
    {
        SetCurPos(0,0);
        SetEnd();
        cout<<scr[0];
    }
};
class TCell
{
public:
    int value;
    POINT pos;
    TCell()
    {
        Init(0,0,0);
    }
    void Init(int x,int y,int val)
    {
        value=val;
        pos=(POINT)
        {
            x,y
        };
    }
    void Put(TScreenMap scr);
};
class TAnimatedCell:public TCell{
    float ax,ay;
    float dx,dy;
    int aCnt;
    int faceVal;
public:
    TAnimatedCell():TCell(){aCnt=0;}
    void Anim(POINT to);
    bool IsAnim(){return aCnt>0?true:false;}
    bool IsStat(){return(dx==0&&dy==0)?true:false;}
    void Work(){aCnt--;ax+=dx;ay+=dy;}
    void PutAnim(TScreenMap scr);
    void PutStat(TScreenMap scr);
};
class TGame
{
    TScreen screen;
    TAnimatedCell cell[fld_height][fld_width];
    bool MoveValInArray(TAnimatedCell*valArr[],int cnt);
    void Move(int dx,int dy);
    void GenNewRandNum(bool anim=false);
    int GetFreeCellCnt();
    bool CheckEndGame();
public:
    TGame()
    {
        Init();
    }
    void Init();
    void Work();
    void Show();
};
void TAnimatedCell::PutStat(TScreenMap scr)
{
    if(IsAnim())
    {
        TCell cell;
        if(IsStat())
            cell.Init(pos.x,pos.y,faceVal);
        else
            cell.Init(pos.x,pos.y,0);
        cell.Put(scr);
    }
    else
        Put(scr);
}
void TAnimatedCell::PutAnim(TScreenMap scr)
{
    if(IsAnim())
    {
        Work();
        if(IsStat())return;
        TCell cell;
        cell.Init(lround(ax),lround(ay),faceVal);
        cell.Put(scr);
    }
}
void TAnimatedCell::Anim(POINT to)
{
    if(IsAnim())return;
    faceVal=value;
    aCnt=20;
    ax=pos.x;
    ay=pos.y;
    dx=(to.x-ax)/(float)aCnt;
    dy=(to.y-ay)/(float)aCnt;
}
bool TGame::CheckEndGame()
{
    if(GetFreeCellCnt()>0)
        return false;
    for(int i=0;i<fld_width;i++)
        for(int j=0;j<fld_height;j++)
        if((j<fld_height-1&&cell[j][i].value==cell[j+1][i].value)||
           (i<fld_width-1&&cell[j][i].value==cell[j][i+1].value))
           return false;
    return true;
}
void TGame::GenNewRandNum(bool anim)
{
    if(GetFreeCellCnt()==0)return;
    int cnt=1;
    while(cnt>0)
    {
        int x=rand()%fld_width;
        int y=rand()%fld_height;
        if(cell[y][x].value==0)
        {
            if(anim)
                cell[y][x].Anim(cell[y][x].pos);
            cell[y][x].value=(rand()%10==0)?4:2,cnt--;
        }

    }
}
int TGame::GetFreeCellCnt()
{
   int cnt=0;
   for(int i=0;i<fld_width*fld_height;i++)
        if(cell[0][i].value==0)
        cnt++;
   return cnt;
}
bool KeyDownOnce(char c)
{
    if(GetKeyState(c)<0)
    {
        while(GetKeyState(c)<0);
        return true;
    }
    return false;
}
void TGame::Work()
{
    if(KeyDownOnce('W'))Move(0,-1);
    if(KeyDownOnce('S'))Move(0,1);
    if(KeyDownOnce('A'))Move(-1,0);
    if(KeyDownOnce('D'))Move(1,0);
}
void TGame::Move(int dx,int dy)
{
    bool moved=false;
    if(dx!=0)
        for(int j=0; j<fld_height; j++)
        {
            TAnimatedCell*valArr[fld_width];
            for(int i=0; i<fld_width; i++)
            {
                int x=(dx<0)?i:fld_width-i-1;
                valArr[i]=&cell[j][x];
            }
            if(MoveValInArray(valArr,fld_width))moved=true;
        }
    if(dy!=0)
        for(int i=0; i<fld_width; i++)
        {
            TAnimatedCell*valArr[fld_height];
            for(int j=0; j<fld_height; j++)
            {
                int y=(dy<0)?j:fld_height-j-1;
                valArr[j]=&cell[y][i];
            }
            if(MoveValInArray(valArr,fld_height))moved=true;
        }
        if(CheckEndGame())
            Init();
        else
        if(moved)
            GenNewRandNum(true);
}
bool TGame::MoveValInArray(TAnimatedCell*valArr[],int cnt)
{
    bool moved=false;
    int lastX=0;
    for(int i=1; i<cnt; i++)
        if(valArr[i]->value!=0)
        {
            if(valArr[lastX]->value==0)
            {
                valArr[i]->Anim(valArr[lastX]->pos);
                valArr[lastX]->Anim(valArr[lastX]->pos);
                moved=true;
                valArr[lastX]->value=valArr[i]->value;
                valArr[i]->value=0;
            }
            else if(valArr[lastX]->value==valArr[i]->value)
            {
                valArr[i]->Anim(valArr[lastX]->pos);
                valArr[lastX]->Anim(valArr[lastX]->pos);
                moved=true;
                valArr[lastX]->value+=valArr[i]->value;
                valArr[i]->value=0;
                lastX++;
            }
            else if(valArr[lastX]->value!=valArr[i]->value)
            {
                lastX++;
                if(lastX!=i)
                {
                    valArr[i]->Anim(valArr[lastX]->pos);
                    valArr[lastX]->Anim(valArr[lastX]->pos);
                    moved=true;
                    valArr[lastX]->value=valArr[i]->value;
                    valArr[i]->value=0;
                }
            }
        }
    return moved;
}
void TGame::Show()
{
    for(int i=0; i<fld_width*fld_height; i++)
        cell[0][i].PutStat(screen.scr);
        for(int i=0;i<fld_width*fld_height;i++)
        cell[0][i].PutAnim(screen.scr);
    screen.Show();
}

void TGame::Init()
{
    const int dx=2;
    const int dy=2;
    srand(GetTickCount());
    for(int i=0; i<fld_width; i++)
        for(int j=0; j<fld_height; j++)
            cell[j][i].Init(dx+i*(cell_width-1),dy+j*(cell_height-1),0);
   GenNewRandNum();
   GenNewRandNum();
}
void TCell::Put(TScreenMap scr)
{
    for(int i=0; i<cell_width; i++)
        for(int j=0; j<cell_height; j++)
            scr[pos.y+j][pos.x+i]=(i==0||i==cell_width-1||
                                   j==0||j==cell_height-1)?'+':' ';
    if(value==0)return;
    char buf[10];
    sprintf(buf,"%d",value);
    int len=strlen(buf);
    int posX=(cell_width-len)/2;
    int posY=(cell_height-1)/2;
    for(int i=0; i<len; i++)
        scr[pos.y+posY][pos.x+i+posX]=buf[i];
}

int main()
{
    TGame game;
    while(1)
    {
        game.Work();
        game.Show();
        if(GetKeyState(VK_ESCAPE)<0)break;
        Sleep(10);
    }
    return 0;
}
