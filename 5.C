/* Graphics in MSDOS Borland Turbo C 2.01
   https://www.cs.colorado.edu/~main/bgi/doc/
   Coordinates start from LEFT UPPER corner
   and are counted in PIXELS.
   These will be referred to as GLOBAL coordinates.
*/

#include <stdio.h>
#include <graphics.h>
#include <math.h>

#define SCALE 50

void dot_cos(float xmin, float xmax);

int main()
{
    int gd = DETECT, gm;
    char msg[40];
    
    initgraph(&gd, &gm, "");
    
    setbkcolor(WHITE);

    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    dot_cos(-2 * M_PI, 2 * M_PI);
    
    getch();
    closegraph();
    return 0;
}

void dot_cos(float xmin, float xmax)
{
    float x, y, step, x0, y0;
    step = 0.1;
    
    /* set 0,0 point to be in the middle of the screen */
    x0 = getmaxx() / 2;    y0 = getmaxy() / 2;
    
    for (x = xmin; x <= xmax; x += step)
    {
        y = cos(x);
        fillellipse(x0 + x * SCALE, y0 - y * SCALE, 3, 3);
        delay(2); /* 30 FPS */
        cleardevice();
    }
}
