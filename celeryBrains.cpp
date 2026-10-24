#include "celeryBrains.h"
#include "gobbleBuzz.h"   // for color constants

extern uLCD_4DGL uLCD;

CeleryBrains::CeleryBrains()
    : Food(11, 8, 2, 1)   // width, height, dx, dy
{
}

void CeleryBrains::draw()
{
    //green rectangle
    uLCD.filled_rectangle(x, y, x + width, y + height,
                          getColor(GREEN));
    // light grey “brain” inside
    uLCD.line(x + 2, y + 2, x + width - 2, y + 2, getColor(LGREY));
}

void CeleryBrains::erase()
{
    uLCD.filled_rectangle(oldX, oldY,
                          oldX + width, oldY + height,
                          getColor(BLACK));
}

void CeleryBrains::move()
{
    moveWithBounce(npcSpeedFactor);
}
