#include <stdio.h>
#include "ansi.h"
#include "arithmatic.h"
#include "project_utilities.h"

void exercise3(){
    gotoxy(0,0);
    printf("x   Sin(x)  | x   Cos(x)  | (x,  y)   r   rot(x,y,r)");

    //sin
    gotoxy(0,1);
    printf("%3i ",0);
    printFix(expand(sin512(512*0/360)));
    gotoxy(0, 2);
    printf("%3i ",45);
    printFix(expand(sin512(512*45/360)));
    gotoxy(0,3);
    printf("%3i ",-78);
    printFix(expand(sin512(512*(-78)/360)));
    gotoxy(0,4);
    printf("%3i ",649);
    printFix(expand(sin512(512*649/360)));

    //cos
    gotoxy(14,1);
    printf("%3i ",0);
    printFix(expand(cos512(512*0/360)));
    gotoxy(14, 2);
    printf("%3i ",45);
    printFix(expand(cos512(512*45/360)));
    gotoxy(14,3);
    printf("%3i ",-78);
    printFix(expand(cos512(512*(-78)/360)));
    gotoxy(14,4);
    printf("%3i ",649);
    printFix(expand(cos512(512*649/360)));

    //rotate vec
    vector_t v = {0,0};
    gotoxy(28,1);
    printf("(%3i,%3i) %3i (",1,2,180);
    v.x = 1 << 14;
    v.y = 2 << 14;
    rotateVector(&v,512*180/360);
    printFix(expand(v.x));
    printf(", ");
    printFix(expand(v.y));
    printf(")");

    gotoxy(28,2);
    printf("(%3i,%3i) %3i (",6,4,-10);
    v.x = 6 << 14;
    v.y = 4 << 14;
    rotateVector(&v,512*(-10)/360);
    printFix(expand(v.x));
    printf(", ");
    printFix(expand(v.y));
    printf(")");

    gotoxy(28,3);
    printf("(%3i,%3i) %3i (",-4,-4,900);
    v.x = -4 << 14;
    v.y = -4 << 14;
    rotateVector(&v,512*900/360);
    printFix(expand(v.x));
    printf(", ");
    printFix(expand(v.y));
    printf(")");

    gotoxy(28,4);
    printf("(%3i,%3i) %3i (",-4,2,-35);
    v.x = -4 << 14;
    v.y = 2 << 14;
    rotateVector(&v,512*(-35)/360);
    printFix(expand(v.x));
    printf(", ");
    printFix(expand(v.y));
    printf(")");
}
