#include "sentientPoisonPill.h"
#include "gobbleBuzz.h"
#include "uLCD_4DGL.h"

extern uLCD_4DGL uLCD;
extern GobbleBuzz turkey;    // player reference

SentientPoisonPill::SentientPoisonPill()
    : Poison(11, 8, 0, 0)     // width, height, dx, dy
{
    // placed randomly by base constructor
}

void SentientPoisonPill::draw()
{
    uLCD.filled_rectangle(x, y, x + width, y + height,
                          getColor(BLUE));
    uLCD.line(x, y + height/2, x + width, y + height/2,
              getColor(YELLOW));
}

void SentientPoisonPill::erase()
{
    uLCD.filled_rectangle(oldX, oldY,
                          oldX + width, oldY + height,
                          getColor(BLACK));
}

void SentientPoisonPill::move()
{
    oldX = x;
    oldY = y;

    // find vector from pill -> turkey
    int tx = turkey.getXPos();
    int ty = turkey.getYPos();

    int dx = (tx > x) ? 1 : (tx < x ? -1 : 0);
    int dy = (ty > y) ? 1 : (ty < y ? -1 : 0);

    x += dx;
    y += dy;

    // keep inside bounds
    if (x < PLAYFIELD_LEFT) x = PLAYFIELD_LEFT;
    if (x > PLAYFIELD_RIGHT - width) x = PLAYFIELD_RIGHT - width;
    if (y < PLAYFIELD_TOP) y = PLAYFIELD_TOP;
    if (y > PLAYFIELD_BOTTOM - height) y = PLAYFIELD_BOTTOM - height;
}
