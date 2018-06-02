/* Graphics in MSDOS Borland Turbo C 2.01
   https://www.cs.colorado.edu/~main/bgi/doc/
   Coordinates start from LEFT UPPER corner
   and are counted in PIXELS.
   These will be referred to as GLOBAL coordinates.
*/

#include <stdio.h>
#include <graphics.h>
#include <math.h>

/* Used to determine the step size of x and y axis */
#define SCALEX 25
#define SCALEY 15
/* The independent variable is incremented by this value */
#define STEP 0.1
/* Drawing delay for each step in ms */
#define DELAY 10

/* Global variables declaration */
int X0, Y0, STEPX, STEPY;

/* Initializes graphics driver and global variables */
void init(void);

/* Draws x and y axis with 0,0 point in the middle of the screen
  xlen, ylen - length (in steps) of x and y axis
  freq - labeling frequency (1 to label all whole points) */
void draw_xy_axis(int xlen, int ylen, int freq);

/* Draws a quadratic function f(x) = ax^2 + bx + c
  xmin, xmax - draws the parabola for values of x from xmin to xmax
  a, b, c - quadratic function parameters */
void draw_parabola(float xmin, float xmax, float a, float b, float c);

/* Draws a cycloid function
  tmin, tmax - parameter t value range
  a, b - cycloid parameters */
void draw_cycloid(float tmin, float tmax, float a, float b);

int main(void)
{
    init();

    /* Setting up the graph space */
    setbkcolor(WHITE);
    setcolor(BLUE);
    draw_xy_axis(12, 9, 1);
    
    /* Drawing x^2 */
    setcolor(RED);
    draw_parabola(-2.5, 2.5, 1.0, 0.0, 0.0);
    
    getch();
    /* Drawing cycloid */
    setcolor(GREEN);
    draw_cycloid(-2.5 * M_PI, 2.5 * M_PI, 1.5, 3.0);
    
    getch();
    closegraph();
    return 0;
}

void init(void)
{
    /* Initializing graphics driver */
    int gd = DETECT, gm, errorcode;
    initgraph(&gd, &gm, "");
    
    errorcode = graphresult();
    if (errorcode != grOk)    /* an error occurred */
    {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to halt:");

        getch();
        exit(1);               /* return with error code */
    }
    
    /* Initializing global variables */
    X0 = getmaxx() / 2;
    Y0 = getmaxy() / 2;
    STEPX = getmaxx() / SCALEX;
    STEPY = getmaxy() / SCALEY;
}

void draw_parabola(float xmin, float xmax, float a, float b, float c)
{
    float x, y;
    
    /* determine the leftmost Y to start drawing from */
    y = a * xmin * xmin + b * xmin + c;
    /* move current position to the starting point
      (x * STEPX) converts x value to global coordinates
      (X0 + x * STEPX) offsets it by where 0,0 point is */
    moveto(X0 + xmin * STEPX, Y0 - y * STEPY);
    
    /* for all values from xmin to xmax, differentiating by STEP */
    for (x = xmin + STEP; x <= xmax; x += STEP)
    {
        /* calculate Y for the point */
        y = a * x * x + b * x + c;
        /* draw a line from current position to new X,Y point */
        lineto(X0 + x * STEPX, Y0 - y * STEPY);
        delay(DELAY);
    }
}

void draw_cycloid(float tmin, float tmax, float a, float b)
{
    float x, y, t;
    
    /* determine the starting drawing point */
    x = a * tmin - b * sin(tmin);
    y = a - b * cos(tmin);
    /* move current position to the starting point */
    moveto(X0 + x * STEPX, Y0 - y * STEPY);
    /* for all values from tmin to tmax, differentiating by STEP */
    for (t = tmin + STEP; t <= tmax; t += STEP)
    {
        x = a * t - b * sin(t);
        y = a - b * cos(t);
        /* draw a line from current position to new X,Y point */
        lineto(X0 + x * STEPX, Y0 - y * STEPY);
        delay(DELAY);
    }
}

void draw_xy_axis(int xlen, int ylen, int freq)
{
    int xneg, yneg, xpos, ypos, i;
    char msg[40];

    xneg = X0 - STEPX * xlen; /* the leftmost point of x axis */
    xpos = X0 + STEPX * xlen; /* the rightmost point of x axis */
    yneg = Y0 + STEPY * ylen; /* the lowest point of y axis */
    ypos = Y0 - STEPY * ylen; /* the highest point of y axis */
    
    line(xneg, Y0, xpos, Y0); /* draw x */
    line(X0, yneg, X0, ypos); /* draw y */

    /* draw arrows and axis labels */
    line(xpos, Y0 + 2, xpos + 5, Y0); /* x */
    line(xpos + 5, Y0, xpos, Y0 - 2);
    outtextxy(xpos - 5, Y0 - textheight("x") - 10, "x");

    line(X0 - 2, ypos, X0, ypos - 5); /* y */
    line(X0, ypos - 5, X0 + 2, ypos);
    outtextxy(X0 - textwidth("y") - 10, ypos - 5, "y");

    /* draw values along the x axis */
    for (i = xneg; i <= xpos; i += STEPX)
    {
        /* draw every 5th value */
        if (((i - X0) / STEPX) % freq != 0)
            continue;
        line(i, Y0 - 2, i, Y0 + 2);
        sprintf(msg, "%d", (i - X0) / STEPX);
        outtextxy(i - textwidth(msg) / 2, Y0 + 5, msg);
    }
    /* draw values along the y axis
       in math Y grows from bottom to top,but in the graphics
       library global Y values increase from top to bottom */
    for (i = yneg; i >= ypos; i -= STEPY)
    {
        if (((Y0 - i) / STEPY) % freq != 0)
            continue;
        /* already placed label for 0 while drawing X values */
        if (i == Y0)
            continue;
        line(X0 - 2, i, X0 + 2, i);
        sprintf(msg, "%d", (Y0 - i) / STEPY);
        outtextxy(X0 + 5, i - textheight(msg) / 2, msg);
    }
}

