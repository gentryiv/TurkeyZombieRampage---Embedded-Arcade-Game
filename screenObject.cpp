#include "screenObject.h"

ScreenObject::ScreenObject(int objWidth, int objHeight, int dx, int dy)
{
    width  = objWidth;
    height = objHeight;
    baseDx = dx;
    baseDy = dy;
    x = y = 0;
    oldX = oldY = 0;
    placeRandom();
}

void ScreenObject::placeRandom()
{
    // keep entire object inside border
    x = (rand() % (PLAYFIELD_RIGHT - width)) + PLAYFIELD_LEFT;
    y = (rand() % (PLAYFIELD_BOTTOM - height)) + PLAYFIELD_TOP;
    oldX = x;
    oldY = y;
}

void ScreenObject::moveWithBounce(int speedFactor)
{
    oldX = x;
    oldY = y;

    int dx = baseDx * speedFactor;
    int dy = baseDy * speedFactor;

    x += dx;
    y += dy;

    // left/right
    if (x < PLAYFIELD_LEFT) {
        x = PLAYFIELD_LEFT;
        baseDx = -baseDx;
    }
    if (x > PLAYFIELD_RIGHT - width) {
        x = PLAYFIELD_RIGHT - width;
        baseDx = -baseDx;
    }

    // top/bottom
    if (y < PLAYFIELD_TOP) {
        y = PLAYFIELD_TOP;
        baseDy = -baseDy;
    }
    if (y > PLAYFIELD_BOTTOM - height) {
        y = PLAYFIELD_BOTTOM - height;
        baseDy = -baseDy;
    }
}

//Food Specifics

Food::Food(int objWidth, int objHeight, int dx, int dy)
    : ScreenObject(objWidth, objHeight, dx, dy)
{
    currentValue = 1 + (rand() % 2);   // 1 or 2
}

int Food::getScoreDelta()
{
    int delta = currentValue;
    currentValue = 1 + (rand() % 2);   // re-roll for next time
    return delta;
}

//Poison Specifics

Poison::Poison(int objWidth, int objHeight, int dx, int dy)
    : ScreenObject(objWidth, objHeight, dx, dy)
{
    penalty = -10;
}

int Poison::getScoreDelta()
{
    return penalty;
}
