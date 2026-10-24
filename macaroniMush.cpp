#include "macaroniMush.h"
#include "gobbleBuzz.h"

extern uLCD_4DGL uLCD;

MacaroniMush::MacaroniMush()
    : Food(11, 8, 2, -1)
{
}

void MacaroniMush::draw()
{
    // yellow macaroni with brown outline
    uLCD.filled_rectangle(x + 1, y + 2,
                          x + width - 1, y + height - 2,
                          getColor(YELLOW));
    uLCD.rectangle(x, y + 1,
                   x + width, y + height - 1,
                   getColor(BROWN));
}

void MacaroniMush::erase()
{
    uLCD.filled_rectangle(oldX, oldY,
                          oldX + width, oldY + height,
                          getColor(BLACK));
}

void MacaroniMush::move()
{
    moveWithBounce(npcSpeedFactor);
}
