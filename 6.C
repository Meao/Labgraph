#include <stdio.h>
#include <graphics.h>

int main()
{
    int midx, midy, i, gd = DETECT, gm;

    initgraph(&gd, &gm, "");

    midx = getmaxx() / 2;
    midy = getmaxy() / 2;

    setcolor(BLUE);
    for(i = 0; i < midx + 20; i++)
        rectangle(midx - i, midy - i*0.7, midx + i, midy + i*0.7);

    getch();

    return 0;
}