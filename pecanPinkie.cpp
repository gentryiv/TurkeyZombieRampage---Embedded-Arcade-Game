#include "pecanPinkie.h"
#include "gobbleBuzz.h"

extern uLCD_4DGL uLCD;

PecanPinkie::PecanPinkie()
    : Food(11, 8, -2, -1)
{
}

void PecanPinkie::draw()
{
    // brown pecan with pink(red) center
    uLCD.filled_rectangle(x, y, x + width, y + height,
                          getColor(BROWN));
    uLCD.filled_rectangle(x + 3, y + 2,
                          x + width - 3, y + height - 2,
                          getColor(RED));   // using red for pink
}

void PecanPinkie::erase()
{
    uLCD.filled_rectangle(oldX, oldY,
                          oldX + width, oldY + height,
                          getColor(BLACK));
}

void PecanPinkie::move()
{
    moveWithBounce(npcSpeedFactor);
}
