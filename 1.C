/* Graphics in MSDOS Borland Turbo C 2.01
   Coordinates start from LEFT UPPER corner
   and are counted in PIXELS.
   These will be referred to as GLOBAL coordinates.
*/

#include <stdio.h>
#include <graphics.h>
#include <math.h>

/* These will be used to determine the step size of x and y axis
   draw_parabola does not yet support different X and Y scaling */
#define SCALEX 50
#define SCALEY 50

/* Draws x and y axis
  x0, y0 - global coordinates for 0,0 point
  xlen, ylen - length (in steps) of x and y axis
  stepx, stepy - step size in pixels for x and y axis */
void draw_xy_axis(int x0, int y0,
                  int xlen, int ylen, int stepx, int stepy);

/* Draws a quadratic function f(x) = ax^2 + bx + c
  Requires SCALEX == SCALEY to draw correctly
  xmin, xmax - draws the parabola for values of x from min to max
  x0, y0 - global coordinates for 0,0
  one - step size of x and y axis
  a, b, c - quadratic function parameters */
void draw_parabola(float xmin, float xmax, int x0, int y0,
                   int one, float a, float b, float c);

int main()
{
    int midx, midy, stepx, stepy, one, gd = DETECT, gm;
    char msg[40];
    
    initgraph(&gd, &gm, "");
    midx = getmaxx() / 2; midy = getmaxy() / 2;
    stepx = getmaxx() / SCALEX;
    stepy = getmaxy() / SCALEY;
    
    setbkcolor(WHITE);
    
    /* Drawing x and y axis with 0 in the middle */
    setcolor(BLUE);
    draw_xy_axis(midx, midy, 23, 23, stepx, stepy);
    
    /* Drawing x^2 */
    setcolor(RED);
    draw_parabola(-4.0, 4.0, midx, midy, stepy, 1.0, 0.0, 0.0);
    
    getch();
    closegraph();
    return 0;
}

void draw_parabola(float xmin, float xmax, int x0, int y0,
                   int one, float a, float b, float c)
{
    float x, y, step;
    /* this is the step of drawing the curve,
       one line is drawn per each step */
    step = one * (0.1 / SCALEY);
    
    /* avoids infinite loop in case step was set incorrectly */
    if (step == 0) return;
    
    /* determine the leftmost Y to start drawing from */
    y = a * xmin * xmin + b * xmin + c;
    /* move current position to the starting point
      (x * one) converts x value to global coordinates
      (x0 + x * one) offsets it by where 0,0 point is */
    moveto(x0 + xmin * one, y0 - y * one);
    
    /* for all values from xmin to xmax, differentiating by step */
    for (x = xmin + step; x <= xmax; x += step)
    {
        /* calculate Y for the point */
        y = a * x * x + b * x + c;
        /* draw a line from current position to new X,Y point */
        lineto(x0 + x * one, y0 - y * one);
    }
}

void draw_xy_axis(int x0, int y0,
                 int xlen, int ylen, int stepx, int stepy)
{
    int xneg, yneg, xpos, ypos, i;
    char msg[40];
    
    /* xneg is the leftmost point of x axis, xpos is the rightmost */
    xneg = x0 - stepx * xlen;
    xpos = x0 + stepx * xlen;
    /* same for y */
    yneg = y0 - stepy * ylen;
    ypos = y0 + stepy * ylen;
    
    line(xneg, y0, xpos, y0); /* draw x */
    line(x0, yneg, x0, ypos); /* draw y */
    
    /* draw values along the x axis */
    for (i = xneg; i <= xpos; i += stepx)
    {
        /* draw every 5th value */
        if (((i - x0) / stepx) % 5 != 0)
            continue;
        line(i, y0 - 2, i, y0 + 2);
        sprintf(msg, "%d", (i - x0) / stepx);
        outtextxy(i - textwidth(msg) / 2, y0 + 5, msg);
    }
    /* draw values along the y axis
       in math Y grows from bottom to top,but in the graphics
       library global Y values increase from top to bottom */
    for (i = yneg; i <= ypos; i += stepy)
    {
        if (((y0 - i) / stepy) % 5 != 0)
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