/* Graphics in MSDOS Borland Turbo C 2.01
   https://www.cs.colorado.edu/~main/bgi/doc/
   Coordinates start from LEFT UPPER corner
   and are counted in PIXELS.
   These will be referred to as GLOBAL coordinates.
*/

#include <stdio.h>
#include <graphics.h>
#include <math.h>

int main()
{
	int midx, midy, x25, y25, gd = DETECT, gm;
	
	initgraph(&gd, &gm, "");
	
	midx = getmaxx() / 2;
	midy = getmaxy() / 2;
	x25 = getmaxx() * 0.25;
	y25 = getmaxy() * 0.25;
	
	setbkcolor(WHITE);
	
	setfillstyle(SOLID_FILL, RED);
	setcolor(BLUE);
	
	bar3d(x25 - 60, y25 - 40, x25 + 60, y25 + 40, 0, 0);
	line(x25 - 60, y25 - 40, x25 + 60, y25 + 40);
	line(x25 - 60, y25 + 40, x25 + 60, y25 - 40);
	
	setfillstyle(SOLID_FILL, YELLOW);
	setcolor(MAGENTA);
	fillellipse(midx, midy, 50, 50);
	
	getch();
	
	return 0;
}