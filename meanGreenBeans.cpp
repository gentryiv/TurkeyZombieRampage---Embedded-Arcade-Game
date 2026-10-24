#include "meanGreenBeans.h"
#include "gobbleBuzz.h"

extern uLCD_4DGL uLCD;

MeanGreenBeans::MeanGreenBeans()
    : Food(11, 8, -2, 1)
{
}

void MeanGreenBeans::draw()
{
    // horizontal beans band
    uLCD.filled_rectangle(x, y + 2, x + width, y + height - 2,
                          getColor(GREEN));
    uLCD.line(x, y + 1, x + width, y + 1, getColor(DGREY));
}

void MeanGreenBeans::erase()
{
    uLCD.filled_rectangle(oldX, oldY,
                          oldX + width, oldY + height,
                          getColor(BLACK));
}

void MeanGreenBeans::move()
{
    moveWithBounce(npcSpeedFactor);
}
