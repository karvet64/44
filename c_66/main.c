#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct {int x,y,z;} point;

point f1(){return (point){22,33,44};}

int main()
{

  point p;
  p=f1();
  printf("%d %d %d\n",p.x,p.y,p.z);


    return 0;
}
