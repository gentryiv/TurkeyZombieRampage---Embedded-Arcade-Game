#ifndef SCREENOBJECT_H
#define SCREENOBJECT_H

#include "mbed.h"
#include "uLCD_4DGL.h"
#include <stdlib.h>


extern uLCD_4DGL uLCD;
extern bool colorsInverted;
int getColor(int baseColor);

// Bounds
#define PLAYFIELD_LEFT   2
#define PLAYFIELD_RIGHT  118   // rightmost x for left edge of an 11-wide sprite is 118 - 11 + 2
#define PLAYFIELD_TOP    2
#define PLAYFIELD_BOTTOM 108

class ScreenObject
{
public:
    ScreenObject(int objWidth, int objHeight, int dx, int dy);

    virtual ~ScreenObject() {}

    virtual void draw() = 0;
    virtual void erase() = 0;
    virtual void move() = 0;

    // score effect when eaten (food: +1 or +2, poison: -10)
    virtual int getScoreDelta() = 0;

    virtual bool isPoison() const { return false; }

    // where am I?
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // common random placement for all edibles
    void placeRandom();

protected:
    // shared “bounce with speed factor” used by Food/Poison
    void moveWithBounce(int speedFactor);

    int x;
    int y;
    int oldX;
    int oldY;

    int width;
    int height;

    int baseDx;
    int baseDy;
};

// Food / Poison intermediate classes

class Food : public ScreenObject
{
public:
    Food(int objWidth, int objHeight, int dx, int dy);

    // default: random 1 or 2 points each time it is eaten
    virtual int getScoreDelta();

protected:
    int currentValue;  // 1 or 2
};

class Poison : public ScreenObject
{
public:
    Poison(int objWidth, int objHeight, int dx, int dy);

    virtual int getScoreDelta();  // always -10

    virtual bool isPoison() const { return true; }

protected:
    int penalty;   // -10
};

#endif
