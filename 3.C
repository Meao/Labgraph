/* Graphics in MSDOS Borland Turbo C 2.01
   https://www.cs.colorado.edu/~main/bgi/doc/
   Coordinates start from LEFT UPPER corner
   and are counted in PIXELS.
   These will be referred to as GLOBAL coordinates.
*/

#include <stdio.h>
#include <graphics.h>
#include <math.h>

/* These will be used to determine the step size of x and y axis */
#define SCALEX 25
#define SCALEY 25

/* Draws x and y axis with 0,0 point in the middle of the screen
  xlen, ylen - length (in steps) of x and y axis
  stepx, stepy - step size in pixels for x and y axis
  freq - labeling frequency (1 to label all whole points) */
void draw_xy_axis(int xlen, int ylen, int stepx, int stepy, int freq);

/* Draws a cycloid function
  Assumes 0,0 is in the middle of the screen
  one - axis step in pixels
  tmin, tmax - parameter t value range
  a, b - cycloid parameters */
void draw_cycloid(int one, float tmin, float tmax, float a, float b);

int main()
{
    int stepx, stepy, one, gd = DETECT, gm;
    char msg[40];
    
    initgraph(&gd, &gm, "");
    stepx = getmaxx() / SCALEX;
    stepy = getmaxy() / SCALEY;
    
    setbkcolor(WHITE);
    
    /* Drawing x and y axis with 0 in the middle */
    setcolor(BLUE);
    draw_xy_axis(12, 12, stepx, stepy, 1);
    
    /* Drawing */
    setcolor(RED);
    draw_cycloid(stepy, -3 * M_PI, 3 * M_PI, 1.5, 3.0);
    
    getch();
    closegraph();
    return 0;
}

void draw_cycloid(int one, float tmin, float tmax, float a, float b)
{
    float x, y, t, step, x0, y0;
    /* t will be increasing by step from tmin to tmax */
    step = 0.1;
    
    /* set 0,0 point to be in the middle of the screen */
    x0 = getmaxx() / 2;    y0 = getmaxy() / 2;
    
    /* determine the starting drawing point */
    x = a * tmin - b * sin(tmin);
    y = a - b * cos(tmin);
    /* move current position to the starting point */
    moveto(x0 + x * one, y0 - y * one);
    /* for all values from tmin to tmax, differentiating by step */
    for (t = tmin + step; t <= tmax; t += step)
    {
        x = a * t - b * sin(t);
        y = a - b * cos(t);
        /* draw a line from current position to new X,Y point */
        lineto(x0 + x * one, y0 - y * one);
    }
}

void draw_xy_axis(int xlen, int ylen, int stepx, int stepy, int freq)
{
    int x0, y0, xneg, yneg, xpos, ypos, i;
    char msg[40];
    
    /* set 0,0 point to be in the middle of the screen */
    x0 = getmaxx() / 2;
    y0 = getmaxy() / 2;

    xneg = x0 - stepx * xlen; /* the leftmost point of x axis */
    xpos = x0 + stepx * xlen; /* the rightmost point of x axis */
    yneg = y0 + stepy * ylen; /* the lowest point of y axis */
    ypos = y0 - stepy * ylen; /* the highest point of y axis */
    
    line(xneg, y0, xpos, y0); /* draw x */
    line(x0, yneg, x0, ypos); /* draw y */

    /* draw arrows and axis labels */
    line(xpos, y0 + 2, xpos + 5, y0); /* x */
    line(xpos + 5, y0, xpos, y0 - 2);
    outtextxy(xpos - 5, y0 - textheight("x") - 10, "x");

    line(x0 - 2, ypos, x0, ypos - 5); /* y */
    line(x0, ypos - 5, x0 + 2, ypos);
    outtextxy(x0 - textwidth("y") - 10, ypos - 5, "y");

    /* draw values along the x axis */
    for (i = xneg; i <= xpos; i += stepx)
    {
        /* draw every 5th value */
        if (((i - x0) / stepx) % freq != 0)
            continue;
        line(i, y0 - 2, i, y0 + 2);
        sprintf(msg, "%d", (i - x0) / stepx);
        outtextxy(i - textwidth(msg) / 2, y0 + 5, msg);
    }
    /* draw values along the y axis
       in math Y grows from bottom to top,but in the graphics
       library global Y values increase from top to bottom */
    for (i = yneg; i >= ypos; i -= stepy)
    {
        if (((y0 - i) / stepy) % freq != 0)
            continue;
        /* already placed label for 0 while drawing X values */
        if (i == y0)
            continue;
        line(x0 - 2, i, x0 + 2, i);
        sprintf(msg, "%d", (y0 - i) / stepy);
        outtextxy(x0 + 5, i - textheight(msg) / 2, msg);
    }
}

