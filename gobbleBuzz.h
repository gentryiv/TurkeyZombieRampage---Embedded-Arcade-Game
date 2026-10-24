#ifndef GOBBLE_BUZZ_H
#define GOBBLE_BUZZ_H

#include "screenObject.h"

#define TURKEY_WIDTH  11
#define TURKEY_HEIGHT  8

#define WHITE  0xFFFFFF
#define BLACK  0x000000
#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define LGREY  0xBFBFBF
#define DGREY  0x5F5F5F
#define YELLOW 0xFFFF00
#define BROWN  0x964B00

// movement step for the turkey
#define X_DELTA 5
#define Y_DELTA 5

class GobbleBuzz : public ScreenObject
{
public:
    GobbleBuzz();

    // required virtuals
    virtual void draw();
    virtual void erase();
    virtual void move();

    //turkey itself doesn't change score directly, so return 0
    virtual int getScoreDelta() { return 0; }

    // overlap helper
    bool overlap(int upperLX, int upperLY, int lowerRX, int lowerRY);

    // getters for compatibility
    int getXPos() const  { return x; }
    int getYPos() const  { return y; }
    int getOLDXPos() const { return oldX; }
    int getOLDYPos() const { return oldY; }

    void copyX() { oldX = x; }
    void copyY() { oldY = y; }

private:
    void keepInsideBounds();
};

#endif
