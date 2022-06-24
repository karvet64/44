#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include<assert.h>
#define width 65
#define height 25
void setcur(int x, int y);
void moveBall(float x, float y);

typedef struct
{
    int x,y;
    int w;
    int fireMode;
} TRacket;

typedef struct
{
    float x,y;
    int ix,iy;
    float alfa;
    float speed;
    char type;
    char del;
} TBall, TObj;
char Obj_HitBrick(TObj ball);
#define c_border '#'
#define c_racket '@'
#define c_brick (char)176
#define brickWidth 3

char lvlMap[height][width];

boolean run = FALSE;

#define objArrSize 1000
TObj objArr[objArrSize];
int objArrCnt=0;

#define ot_wide 'W'
#define ot_thin 'T'
#define ot_fire 'F'
#define ot_bullet '.'
#define objUpgradeTypesRandMax 7
char objUpgradeTypes[]={ot_wide,ot_thin,ot_fire};
int objUpgradeTypesCnt=sizeof(objUpgradeTypes)/sizeof(objUpgradeTypes[0]);


char mas[height][width+1];
TRacket racket;
TBall ball;
int hitCnt = 0;
int maxHitCnt = 0;
int lvl = 1;
TObj Obj_Create(float x,float y,float a,float spd,char chr)
{
    return (TObj){x,y,(int)x,(int)y,a,spd,chr};
}
void Obj_Put(TObj obj)
{
    if(mas[obj.iy][obj.ix]==' ')
        mas[obj.iy][obj.ix]=obj.type;
}
void CorrectAngle(float *a)
{
    if(*a<0)*a+=M_PI*2;
    if(*a>M_PI*2)*a-=M_PI*2;
}
void Obj_Move(TObj*obj)
{
    CorrectAngle(&obj->alfa);
    obj->x+=cos(obj->alfa)*obj->speed;
    obj->y+=sin(obj->alfa)*obj->speed;
    obj->ix=(int)obj->x;
    obj->iy=(int)obj->y;
}
void Obj_WorkUpgrade(TObj*obj)
{
    if(mas[obj->iy][obj->ix]!=c_racket)return;
    if(obj->type==ot_wide)racket.w=min(racket.w+1,15),obj->del=1;
    if(obj->type==ot_thin)racket.w=max(racket.w-1,5),obj->del=1;
    if(obj->type==ot_fire)
    {
        if(racket.fireMode<1)racket.fireMode=1;
        obj->del=1;
    }
}
void Obj_WorkBullet(TObj*obj)
{
    if(obj->type!=ot_bullet)return;
    if(Obj_HitBrick(*obj)||mas[obj->iy][obj->ix]==c_border)
        obj->del=1;
}
void Obj_Work(TObj*obj)
{
    Obj_Move(obj);
    Obj_WorkUpgrade(obj);
    Obj_WorkBullet(obj);
}
void ObjArr_Add(TObj obj)
{
    assert(objArrCnt+1<objArrSize);
    objArr[objArrCnt]=obj;
    objArrCnt++;
}
void ObjArr_DelPos(int pos)
{
    if(pos<0||pos>=objArrCnt)return;
    objArr[pos]=objArr[objArrCnt-1];
    objArrCnt--;
}
void ObjArr_Work()
{
    int i=0;
    while(i<objArrCnt)
    {
        Obj_Work(objArr+i);
        if(objArr[i].y<0||objArr[i].y>height||objArr[i].del)
            ObjArr_DelPos(i);
        else
            i++;
    }
}
void ObjArr_Put()
{
    for(int i=0;i<objArrCnt;i++)
        Obj_Put(objArr[i]);
}
void ObjArr_Clean(){objArrCnt=0;}
void initBall()
{
    moveBall(2,2);
    ball.alfa=-1;
    ball.speed=0.5;
}


void putBall()
{
    mas[ball.iy][ball.ix] = '*';
}

void moveBall(float x, float y)
{
    ball.x = x;
    ball.y = y;
    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
}

void Obj_ChanceCreateRandomUpgradeObject(float x,float y)
{
    int i=rand()%objUpgradeTypesRandMax;
    if(i<objUpgradeTypesCnt)
        ObjArr_Add(Obj_Create(x,y,M_PI_2,0.2,objUpgradeTypes[i]));
}

char Obj_HitBrick(TObj ball)
{
    if(mas[ball.iy][ball.ix]==c_brick)
        {
            if(lvlMap[ball.iy][ball.ix]==c_brick)
                Obj_ChanceCreateRandomUpgradeObject(ball.x,ball.y);
           int brickNom=(ball.ix-1)/brickWidth;
           int dx=1+brickNom*brickWidth;
           for(int i=0;i<brickWidth;i++)
           {
               static char*c;
               c=&lvlMap[ball.iy][i+dx];
               if(*c==c_brick)*c=' ';
           }
           return 1;
        }
        return 0;
}
void autoMoveBall()
{
    if (ball.alfa < 0) ball.alfa += M_PI*2;
    if (ball.alfa > M_PI*2) ball.alfa -= M_PI*2;

    TBall bl = ball;
    moveBall(ball.x + cos(ball.alfa) * ball.speed
             ,ball.y + sin(ball.alfa) * ball.speed);

    if ((mas[ball.iy][ball.ix] == c_border) || (mas[ball.iy][ball.ix] == c_brick)
        ||(mas[ball.iy][ball.ix])==c_racket)
    {
        Obj_HitBrick(ball);

         if (mas[ball.iy][ball.ix] == c_racket)
         {
            hitCnt++;
            float pos=ball.x-racket.x;
            float psi=pos/racket.w*2;
            psi=(psi-1)*M_PI_2*0.9;
            assert(psi<M_PI_2 && psi>-M_PI_2);
            bl.alfa=-M_PI_2+psi;
         }

        else if ((ball.ix != bl.ix) && (ball.iy != bl.iy))
        {
            if (mas[bl.iy][ball.ix] == mas[ball.iy][bl.ix])
                bl.alfa = bl.alfa + M_PI;
            else
            {
                if (mas[bl.iy][ball.ix] == c_border)
                    bl.alfa = (2*M_PI - bl.alfa) + M_PI;
                else
                    bl.alfa = (2*M_PI - bl.alfa);
            }
        }
        else if (ball.iy == bl.iy)
            bl.alfa = (2*M_PI - bl.alfa) + M_PI;
        else
            bl.alfa = (2*M_PI - bl.alfa);

        ball = bl;

    }
}

void initRacket()
{
    racket.w = 7;
    racket.x = (width - racket.w) / 2;
    racket.y = height - 1;
    racket.fireMode=0;
}

void putRacket()
{
    for (int i=racket.x; i < racket.x + racket.w; i++)
        mas[racket.y][i] = c_racket;
        if(racket.fireMode>0)
            mas[racket.y-1][racket.x+racket.w/2]='|';
}

void lvlMapPuzzile(int lvl)
{
    if(lvl==1)
    {
        for(int i=7;i<width-7;i++)
            lvlMap[5][i]=lvlMap[6][i]=c_brick;
    }

    if (lvl == 2)
       for(int i=19;i<=48;i++)
       {
           lvlMap[1][i]=lvlMap[2][i]=c_brick;
           lvlMap[8][i]=lvlMap[9][i]=c_brick;
           lvlMap[10][i]=c_border;
       }

    if (lvl == 3)
    {
     for(int j=1;j<10;j++)
        for(int i=1;i<62;i+=6)
        lvlMap[j][i]=lvlMap[j][i+1]=lvlMap[j][i+2]=c_brick;
    }

}
void lvlMapInit(int lvl)
{
    memset(lvlMap,' ',sizeof(lvlMap));
    lvlMapPuzzile(lvl);
    for(int i=0;i<width;i++)
        lvlMap[0][i]=c_border;
        for(int j=0;j<height;j++)
            lvlMap[j][0]=lvlMap[j][width-1]=c_border;
}
void lvlMapPut()
{
    memset(mas,0,sizeof(mas));
    for(int j=0;j<height;j++)
        memcpy(mas[j],lvlMap[j],sizeof(**lvlMap)*width);
}
void show()
{
    setcur(0,0);
    for(int i=0; i<height; i++)
    {
        printf("%s", mas[i]);
        if (i == 1)
            printf("   lvl %i   ", lvl);
        if (i == 3)
            printf("   hit %i   ", hitCnt);
        if (i == 4)
            printf("   max %i   ", maxHitCnt);
        if (i < height - 1)
            printf("\n");
    }
}

void moveRacket(int x)
{
    racket.x = x;
    if (racket.x < 1)
        racket.x = 1;
    if (racket.x + racket.w >= width)
        racket.x = width - 1 - racket.w;
}

void setcur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowPreview()
{
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n \t\t\t\t    LEVEL %d", lvl);
    Sleep(1000);
    system("cls");
}
void CheckFaild()
{
    if (ball.iy >=height-1)
    {
        run = FALSE;
        if (hitCnt > maxHitCnt)
            maxHitCnt = hitCnt;
        hitCnt = 0;
    }
}
int lvlMapBrickCount()
{
    int cnt=0;
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++)
        if(lvlMap[j][i]==c_brick)
        cnt++;
    return cnt;
}
void CheckWin()
{
    if (lvlMapBrickCount()==0)
    {
        lvl++;
        if(lvl>3)lvl=1;
        lvlMapInit(lvl);
        run = FALSE;
        maxHitCnt = 0;
        hitCnt = 0;
        initRacket();
        ObjArr_Clean();
        ShowPreview();
    }
}
void BallWork()
{
    if (run)
        autoMoveBall();
    else
    {
           moveBall(racket.x + racket.w / 2, racket.y - 1);
           ball.alfa=-M_PI_2-0.5;
    }

}
void racketShot()
{
    if(racket.fireMode!=1)return;
    ObjArr_Add(Obj_Create(racket.x+racket.w/2,racket.y-2,
                          -M_PI_2,0.5,ot_bullet));
    racket.fireMode+=10;
}
void racketWork()
{
    if(racket.fireMode>1)
        racket.fireMode--;
}
int main()
{



    initRacket();
    initBall();
    lvlMapInit(lvl);
    ShowPreview();



    do
    {

        BallWork();
        ObjArr_Work();
        racketWork();
        CheckFaild();

        CheckWin();
        lvlMapPut();
        putRacket();
        putBall();
        ObjArr_Put();
        show();
        if (GetKeyState('A') < 0) moveRacket(racket.x - 1);
        if (GetKeyState('D') < 0) moveRacket(racket.x + 1);
        if (GetKeyState('W') < 0) run = TRUE;
        if(GetKeyState(VK_SPACE)<0)racketShot();


        Sleep(10);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}
