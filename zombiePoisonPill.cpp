#include "zombiePoisonPill.h"
#include "gobbleBuzz.h"

extern uLCD_4DGL uLCD;

ZombiePoisonPill::ZombiePoisonPill()
    : Poison(11, 8, 2, 2)   // width, height, base dx, base dy
{
}

void ZombiePoisonPill::draw()
{
    // red pill with black stripe
    uLCD.filled_rectangle(x, y, x + width, y + height,
                          getColor(RED));
    uLCD.line(x, y + height / 2, x + width, y + height / 2,
              getColor(BLACK));
}

void ZombiePoisonPill::erase()
{
    uLCD.filled_rectangle(oldX, oldY,
                          oldX + width, oldY + height,
                          getColor(BLACK));
}

void ZombiePoisonPill::move()
{
    moveWithBounce(npcSpeedFactor);
}
