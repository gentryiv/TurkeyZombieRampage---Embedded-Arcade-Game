#include "gobbleBuzz.h"
#include "uLCD_4DGL.h"
#include "joystick.h"

// turkey sprite arrays & LCD from main.cpp
extern uLCD_4DGL uLCD;
extern int turkeySpriteCurrent[];
extern Nav_Switch myNav;

// constructor – width/height = turkey sprite size, no base velocity
GobbleBuzz::GobbleBuzz()
    : ScreenObject(11, 8, 0, 0) // width, height, dx, dy (dx/dy unused for turkey)
{
    x = 50;
    y = 50;
    oldX = x;
    oldY = y;
}

void GobbleBuzz::keepInsideBounds()
{
    if (x < PLAYFIELD_LEFT) x = PLAYFIELD_LEFT;
    if (x > PLAYFIELD_RIGHT - width) x = PLAYFIELD_RIGHT - width;
    if (y < PLAYFIELD_TOP) y = PLAYFIELD_TOP;
    if (y > PLAYFIELD_BOTTOM - height) y = PLAYFIELD_BOTTOM - height;
}

void GobbleBuzz::draw()
{
    uLCD.BLIT(x, y, TURKEY_WIDTH, TURKEY_HEIGHT, turkeySpriteCurrent);
}

void GobbleBuzz::erase()
{
    uLCD.filled_rectangle(oldX, oldY,
                          oldX + width, oldY + height,
                          getColor(BLACK));
}

void GobbleBuzz::move()
{
    // store old position for erase
    oldX = x;
    oldY = y;

    // joystick control
    if (myNav.up())    y -= Y_DELTA;
    if (myNav.down())  y += Y_DELTA;
    if (myNav.left())  x -= X_DELTA;
    if (myNav.right()) x += X_DELTA;

    keepInsideBounds();
}

//overlap
bool GobbleBuzz::overlap(int upperLX, int upperLY, int lowerRX, int lowerRY)
{
    int lrxpos = x + width;
    int lrypos = y + height;

    if (((x >= upperLX) && (x <= lowerRX)) &&
        ((y >= upperLY) && (y <= lowerRY)))
        return true;
    else if (((lrxpos >= upperLX) && (lrxpos <= lowerRX)) &&
             ((lrypos >= upperLY) && (lrypos <= lowerRY)))
        return true;
    else if (((lrxpos >= upperLX) && (lrxpos <= lowerRX)) &&
             ((y >= upperLY) && (y <= lowerRY)))
        return true;
    else if (((x >= upperLX) && (x <= lowerRX)) &&
             ((lrypos >= upperLY) && (lrypos <= lowerRY)))
        return true;
    else
        return false;
}
