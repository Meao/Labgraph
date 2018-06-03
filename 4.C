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
    int midx, midy, color, rad, gd = DETECT, gm;
    float halfside;
    
    initgraph(&gd, &gm, "");
    
    midx = getmaxx() / 2;
    midy = getmaxy() / 2;
    
    setbkcolor(WHITE);
    rad = 100;
    halfside = floor(0.5 * sqrt(2 * rad * rad));
    
    setcolor(BLUE);
    rectangle(midx - halfside, midy - halfside, midx + halfside, midy + halfside);
    
    for (color = 1; color < 15; color++)
    {
        setcolor(color);
        circle(midx, midy, rad);
        delay(500);
    }
    
    getch();
    closegraph();
    return 0;
}
