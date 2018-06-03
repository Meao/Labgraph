#include <stdio.h>
#include <graphics.h>
#include <math.h>

/* Used to determine the step size of x and y axis */
#define SCALEX 16
#define SCALEY 4
/* The independent variable is incremented by this value */
#define STEP 0.1
/* Drawing delay for each step in ms */
#define DELAY 20

/* Global variables declaration */
int X0, Y0, STEPX, STEPY, XLEN, YLEN;

/* Initializes graphics driver and global variables */
void init(void);

/* Draws x and y axis with 0,0 point in the middle of the screen
  xlen, ylen - length (in steps) of x and y axis
  freq - labeling frequency (1 to label all whole points) */
void draw_xy_axis(int freq);

/* Draws a cos*/
void dcos(float xmin, float xmax);

int main(void)
{
    init();

    /* Setting up the graph space */
    setbkcolor(WHITE);
    setcolor(BLUE);
    draw_xy_axis(1);

    /* Drawing cos */
    setcolor(GREEN);
    dcos(-2.5 * M_PI, 2.5 * M_PI);

    getch();
    closegraph();
    return 0;
}

void init(void)
{
    /* Initializing graphics driver */
    int gd = DETECT, gm, errorcode;
    initgraph(&gd, &gm, "");
    /* Initializing global variables */
    X0 = getmaxx() / 2;
    Y0 = getmaxy() / 2;
    STEPX = getmaxx() / SCALEX;
    STEPY = getmaxy() / SCALEY;
    XLEN = SCALEX / 2;
    YLEN = SCALEY / 2;
}

void dcos(float xmin, float xmax)
{
    float x, y;

    for (x = xmin; x <= xmax; x += STEP)
    {
	y = cos(x);
	setcolor(GREEN);
	circle(X0 + x * STEPX, Y0 - y * STEPY, 2);
	delay(DELAY);
	setcolor(WHITE);
	circle(X0+x*STEPX, Y0-y*STEPY,2);
    }
}

void draw_xy_axis(int freq)
{
    int xneg, yneg, xpos, ypos, i;
    char msg[40];

    xneg = X0 - STEPX * XLEN; /* the leftmost point of x axis */
    xpos = X0 + STEPX * XLEN; /* the rightmost point of x axis */
    yneg = Y0 + STEPY * YLEN; /* the lowest point of y axis */
    ypos = Y0 - STEPY * YLEN; /* the highest point of y axis */

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
	if (((Y0 - i) / STEPY) % freq == 0) {
        /* already placed label for 0 while drawing X values */
	if (i != Y0) {
		line(X0 - 2, i, X0 + 2, i);
		sprintf(msg, "%d", (Y0 - i) / STEPY);
		outtextxy(X0 + 5, i - textheight(msg) / 2, msg);}}
    }
}

